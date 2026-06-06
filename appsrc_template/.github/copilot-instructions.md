# Copilot Instructions for appsrc_template

## Purpose

This repository builds a GStreamer source plugin shared library: `libgstarducamsrc.so`.

It is a plugin project, not an application. The source element is implemented in `gstarducamsrc.cpp` and uses an internal frame generator to populate raw video frames.

## Current Project Files

- `gstarducamsrc.h`
- `gstarducamsrc.cpp`
- `Makefile`
- `common/frame_types.h`
- `common/source_common.h`
- `common/source_common.cpp`

## Plugin Architecture

### Source Element Model

- `gstarducamsrc.cpp` implements a `GstPushSrc`-based GStreamer source element.
- The element class is declared in `gstarducamsrc.h`.
- The plugin is registered with GStreamer through `GST_PLUGIN_DEFINE()`.
- `gst_arducamsrc_create()` is the key callback that produces `GstBuffer` frames.

### GObject Properties

The element exposes these properties in `gstarducamsrc.cpp`:
- `width`
- `height`
- `fps-num`
- `fps-den`

These properties are configured via GStreamer and used by the source element when generating caps and timestamps.

### Internal Frame Generator

The plugin uses an internal `fill_arducam_frame()` helper to build raw frames in `gstarducamsrc.cpp`.

`RawFrame` is defined in `common/frame_types.h` and contains raw image bytes, dimensions, stride, format, timestamp, and EOS signal.

## Data Flow

1. GStreamer calls `gst_arducamsrc_create()` repeatedly
2. Plugin calls `fill_arducam_frame()` to generate a `RawFrame`
3. Plugin allocates a `GstBuffer`, copies frame data, and sets PTS/DTS/duration
4. Plugin releases internal frame memory and returns the buffer to GStreamer

## Build Workflow

Build the shared library from the repo root:

```bash
cd ~/shuyang/appsrc_template
make
```

Expected artifact:
- `libgstarducamsrc.so`

Clean build artifacts with:

```bash
make clean
```

Dependencies:
- `g++` with C++17 support
- `pkg-config`
- GStreamer development packages: `gstreamer-1.0`, `gstreamer-base-1.0`, `gstreamer-video-1.0`

## Plugin Validation

Register the built plugin for GStreamer:

```bash
export GST_PLUGIN_PATH=~/shuyang/appsrc_template:$GST_PLUGIN_PATH
gst-inspect-1.0 arducamsrc
```

Example element use:

```bash
gst-launch-1.0 arducamsrc width=640 height=480 fps-num=30 fps-den=1 ! videoconvert ! autovideosink
```

## Implementation Notes

### Implementation Notes

- `gstarducamsrc.cpp` generates raw frames internally via `fill_arducam_frame()`.
- Internal frame generation currently produces RGB frames and populates `RawFrame` fields.
- Plugin code converts `RawFrame` payloads into `GstBuffer` objects and handles timestamps/duration.

### Supported Formats

The plugin supports frame formats defined in `common/frame_types.h`:
- `FRAME_FMT_RGB`
- `FRAME_FMT_BGR`
- `FRAME_FMT_GRAY8`

Downstream format conversion should be performed by GStreamer (`videoconvert`, etc.).

### Timestamp Handling

- If `RawFrame.timestamp_ns` is non-zero, the plugin uses it for `GST_BUFFER_PTS`.
- Otherwise, it computes PTS from `frame_count * duration`.

## Testing & Debugging

Inspect the plugin:

```bash
GST_PLUGIN_PATH=. gst-inspect-1.0 arducamsrc
```

Run a simple pipeline:

```bash
GST_DEBUG=3 gst-launch-1.0 arducamsrc ! fakesink
```

Verify property behavior:

```bash
gst-launch-1.0 arducamsrc width=1280 height=720 fps-num=24 fps-den=1 ! fakesink
```

Troubleshooting:
- Plugin not found: confirm `GST_PLUGIN_PATH` includes the repo directory.
- Instantiation fails: confirm the plugin library is built and `gst-inspect-1.0 arducamsrc` succeeds.
- No frames delivered: confirm the internal frame generator returns valid data and `GST_BUFFER_PTS` is being assigned correctly.

## File Reference

| File | Purpose |
|------|---------|
| `gstarducamsrc.h` | GStreamer element type and class declarations |
| `gstarducamsrc.cpp` | Plugin implementation, lifecycle, caps, buffer generation |
| `common/frame_types.h` | Shared frame format and raw frame definitions |
| `common/source_common.h` | Shared helper declarations for the source plugin |
| `common/source_common.cpp` | Shared helper implementations |
| `Makefile` | Builds `libgstarducamsrc.so` using GStreamer pkg-config |
