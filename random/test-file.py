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

def on_pad_added(src, new_pad, target_element):
    name = new_pad.query_caps(None).get_structure(0).get_name()
    if name.startswith("video"):
        sink_pad = target_element.get_static_pad("sink")
        if not sink_pad.is_linked():
            new_pad.link(sink_pad)
            logger.info(f"Linked video pad to converter.")

# --- 1. Create Jetson-Specific Elements ---
# Source
source = Gst.ElementFactory.make("uridecodebin", "source")

# Converter: 'nvvidconv' is the NVIDIA specific converter. 
# It moves memory to the GPU/NVMM for the encoder.
convert = Gst.ElementFactory.make("nvvidconv", "convert")

# Encoder: The Hardware Encoder (GPU based)
encoder = Gst.ElementFactory.make("nvv4l2h264enc", "encoder")

# Parser: Critical for MP4 muxing when using HW encoders
parser = Gst.ElementFactory.make("h264parse", "parser")

# Muxer & Sink
mux = Gst.ElementFactory.make("mp4mux", "mux")
sink = Gst.ElementFactory.make("filesink", "sink")

# --- Debugging: Check exactly what is missing ---
elements = {
    "uridecodebin": source,
    "nvvidconv": convert,
    "nvv4l2h264enc": encoder,
    "h264parse": parser,
    "mp4mux": mux,
    "filesink": sink
}

for name, element in elements.items():
    if element is None:
        logger.error(f"CRITICAL ERROR: Could not create element '{name}'.")
        logger.error("Please verify your GStreamer installation.")
        sys.exit(1)

# --- 2. Configure ---
source.set_property("uri", "https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm")
sink.set_property("location", "jetson_video.mp4")

# --- 3. Build & Link ---
pipeline = Gst.Pipeline.new("jetson-pipeline")
pipeline.add(source)
pipeline.add(convert)
pipeline.add(encoder)
pipeline.add(parser) # Added parser
pipeline.add(mux)
pipeline.add(sink)

# Link the chain (excluding source)
# Chain: convert -> encoder -> parser -> mux -> sink
convert.link(encoder)
encoder.link(parser)
parser.link(mux)
mux.link(sink)

# Dynamic link for source
source.connect("pad-added", on_pad_added, convert)

# --- 4. Run ---
logger.info("Starting hardware accelerated download...")
pipeline.set_state(Gst.State.PLAYING)

bus = pipeline.get_bus()
msg = bus.timed_pop_filtered(Gst.CLOCK_TIME_NONE, Gst.MessageType.ERROR | Gst.MessageType.EOS)

if msg:
    if msg.type == Gst.MessageType.EOS:
        logger.info("Done. Saved to 'jetson_video.mp4'")
    elif msg.type == Gst.MessageType.ERROR:
        err, debug = msg.parse_error()
        logger.error(f"Error: {err.message}")

pipeline.set_state(Gst.State.NULL)