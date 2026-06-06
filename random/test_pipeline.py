#!/usr/bin/env python3
import sys
import gi
import logging

gi.require_version("GLib", "2.0")
gi.require_version("GObject", "2.0")
gi.require_version("Gst", "1.0")
from gi.repository import Gst, GLib, GObject

logging.basicConfig(level=logging.INFO, format="[%(levelname)s] - %(message)s")
logger = logging.getLogger(__name__)

Gst.init(sys.argv[1:])

# --- Callback ---
def on_pad_added(src, new_pad, target_element):
    # This connects DECODEBIN -> INPUT_CONVERT
    name = new_pad.query_caps(None).get_structure(0).get_name()
    if name.startswith("video"):
        sink_pad = target_element.get_static_pad("sink")
        if not sink_pad.is_linked():
            new_pad.link(sink_pad)
            logger.info(f"Linked decodebin -> input_convert")

# --- 1. Create Elements ---
source = Gst.ElementFactory.make("filesrc", "source")
decoder = Gst.ElementFactory.make("decodebin", "decoder")

# CONVERTER 1: The "Input Bridge"
# Ensures whatever decodebin outputs (CPU or GPU) gets converted to NVMM for the muxer
input_convert = Gst.ElementFactory.make("nvvideoconvert", "input_convert")

# NEW: The CapsFilter
# Enforces that data entering the muxer is strictly NVMM (GPU Memory)
caps = Gst.ElementFactory.make("capsfilter", "caps")

# THE MUXER
streammux = Gst.ElementFactory.make("nvstreammux", "streammux")

# CONVERTER 2: The "Output Un-batcher"
# Takes the Batched structure from muxer and prepares it for the Encoder
output_convert = Gst.ElementFactory.make("nvvideoconvert", "output_convert")

encoder = Gst.ElementFactory.make("nvv4l2h264enc", "encoder")
parser = Gst.ElementFactory.make("h264parse", "parser")
mux = Gst.ElementFactory.make("mp4mux", "mux")
sink = Gst.ElementFactory.make("filesink", "sink")

# Check creation
elements = {
    "filesrc": source, 
    "decodebin": decoder, 
    "input_convert": input_convert, 
    "capsfilter": caps,
    "streammux": streammux, 
    "output_convert": output_convert, 
    "encoder": encoder,
    "h264parse": parser, 
    "mp4mux": mux, 
    "filesink": sink
}

for name, element in elements.items():
    if element is None:
        logger.error(f"Error creating {name}")
        sys.exit(1)

# --- 2. Configure ---
# UPDATE THIS PATH to a real file!
source.set_property("location", "/opt/nvidia/deepstream/deepstream/samples/streams/sample_720p.mp4")
sink.set_property("location", "sandwich_output.mp4")

# Configure Caps: Enforce NVMM memory
caps.set_property("caps", Gst.Caps.from_string("video/x-raw(memory:NVMM)"))

streammux.set_property("width", 640)
streammux.set_property("height", 640)
streammux.set_property("batch-size", 1)
streammux.set_property("batched-push-timeout", 4000000)

# --- 3. Build Pipeline ---
pipeline = Gst.Pipeline.new("jetson-pipeline")
pipeline.add(source)
pipeline.add(decoder)
pipeline.add(input_convert)
pipeline.add(caps)
pipeline.add(streammux)
pipeline.add(output_convert)
pipeline.add(encoder)
pipeline.add(parser)
pipeline.add(mux)
pipeline.add(sink)

# --- 4. Linking ---

# A. Source -> Decoder (Static)
source.link(decoder)

# B. Decoder -> Input Convert (Dynamic via Callback)
decoder.connect("pad-added", on_pad_added, input_convert)

# C. Input Convert -> CapsFilter (Static)
if not input_convert.link(caps):
    logger.error("Failed to link input_convert -> caps")
    sys.exit(1)

# D. CapsFilter -> Streammux (Static, Request Pad)
# We link the CAPS output to the MUX input
caps_src_pad = caps.get_static_pad("src")
mux_sink_pad = streammux.request_pad_simple("sink_0")

if caps_src_pad.link(mux_sink_pad) != Gst.PadLinkReturn.OK:
    logger.error("Failed to link caps -> nvstreammux")
    sys.exit(1)

# E. Streammux -> Output Convert -> Encoder -> Parser -> Mux -> Sink (Static)
if not streammux.link(output_convert):
    logger.error("Failed to link streammux -> output_convert")
if not output_convert.link(encoder):
    logger.error("Failed to link output_convert -> encoder")
if not encoder.link(parser):
    logger.error("Failed to link encoder -> parser")
if not parser.link(mux):
    logger.error("Failed to link parser -> mux")
if not mux.link(sink):
    logger.error("Failed to link mux -> sink")

# --- 5. Run ---
logger.info("Starting pipeline...")
pipeline.set_state(Gst.State.PLAYING)

bus = pipeline.get_bus()
msg = bus.timed_pop_filtered(Gst.CLOCK_TIME_NONE, Gst.MessageType.ERROR | Gst.MessageType.EOS)

if msg:
    if msg.type == Gst.MessageType.EOS:
        logger.info("Done. File saved.")
    elif msg.type == Gst.MessageType.ERROR:
        err, debug = msg.parse_error()
        logger.error(f"Error: {err.message}")

pipeline.set_state(Gst.State.NULL)