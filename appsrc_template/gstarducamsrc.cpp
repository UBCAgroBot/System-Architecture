#include "gstarducamsrc.h"
#include "common/source_common.h"

#include <string.h>

GST_DEBUG_CATEGORY_STATIC(gst_arducamsrc_debug);
#define GST_CAT_DEFAULT gst_arducamsrc_debug

enum {
  PROP_0,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_FPS_NUM,
  PROP_FPS_DEN
};

static GstStaticPadTemplate gst_arducamsrc_src_template =
    GST_STATIC_PAD_TEMPLATE(
        "src",
        GST_PAD_SRC,
        GST_PAD_ALWAYS,
        GST_STATIC_CAPS(
            "video/x-raw, "
            "format=(string){ RGB, BGR, GRAY8 }, "
            "width=(int)[1,MAX], "
            "height=(int)[1,MAX], "
            "framerate=(fraction)[1/1,120/1]"
        ));

#define gst_arducamsrc_parent_class parent_class
G_DEFINE_TYPE(GstArducamSrc, gst_arducamsrc, GST_TYPE_PUSH_SRC);

static void gst_arducamsrc_set_property(GObject* object, guint prop_id,
                                        const GValue* value, GParamSpec* pspec);
static void gst_arducamsrc_get_property(GObject* object, guint prop_id,
                                        GValue* value, GParamSpec* pspec);

static gboolean gst_arducamsrc_start(GstBaseSrc* basesrc);
static gboolean gst_arducamsrc_stop(GstBaseSrc* basesrc);
static GstCaps* gst_arducamsrc_get_caps(GstBaseSrc* basesrc, GstCaps* filter);
static GstFlowReturn gst_arducamsrc_create(GstPushSrc* pushsrc, GstBuffer** outbuf);

static bool fill_arducam_frame(RawFrame* frame) {
  const int width = 640;
  const int height = 480;
  const int channels = 3;
  const size_t size = (size_t)width * height * channels;

  uint8_t* data = static_cast<uint8_t*>(g_malloc(size));
  if (!data) {
    return false;
  }

  for (size_t i = 0; i < size; ++i) {
    data[i] = static_cast<uint8_t>(i & 0xFF);
  }

  frame->data = data;
  frame->size_bytes = size;
  frame->width = width;
  frame->height = height;
  frame->stride = width * channels;
  frame->format = FRAME_FMT_RGB;
  frame->timestamp_ns = 0;
  frame->end_of_stream = false;
  return true;
}

static void release_arducam_frame(RawFrame* frame) {
  if (frame && frame->data) {
    g_free(frame->data);
    frame->data = nullptr;
  }
}

static void gst_arducamsrc_class_init(GstArducamSrcClass* klass) {
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);
  GstElementClass* element_class = GST_ELEMENT_CLASS(klass);
  GstBaseSrcClass* basesrc_class = GST_BASE_SRC_CLASS(klass);
  GstPushSrcClass* pushsrc_class = GST_PUSH_SRC_CLASS(klass);

  gobject_class->set_property = gst_arducamsrc_set_property;
  gobject_class->get_property = gst_arducamsrc_get_property;

  g_object_class_install_property(
      gobject_class, PROP_WIDTH,
      g_param_spec_uint("width", "Width", "Frame width",
                        1, G_MAXUINT, 640,
                        (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property(
      gobject_class, PROP_HEIGHT,
      g_param_spec_uint("height", "Height", "Frame height",
                        1, G_MAXUINT, 480,
                        (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property(
      gobject_class, PROP_FPS_NUM,
      g_param_spec_uint("fps-num", "FPS numerator", "Framerate numerator",
                        1, G_MAXUINT, 30,
                        (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  g_object_class_install_property(
      gobject_class, PROP_FPS_DEN,
      g_param_spec_uint("fps-den", "FPS denominator", "Framerate denominator",
                        1, G_MAXUINT, 1,
                        (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

  gst_element_class_add_pad_template(
      element_class,
      gst_static_pad_template_get(&gst_arducamsrc_src_template));

  gst_element_class_set_details_simple(
      element_class,
      "Arducam source plugin",
      "Source/Video",
      "Arducam source plugin with internal frame generator",
      "Your Name");

  basesrc_class->start = GST_DEBUG_FUNCPTR(gst_arducamsrc_start);
  basesrc_class->stop = GST_DEBUG_FUNCPTR(gst_arducamsrc_stop);
  basesrc_class->get_caps = GST_DEBUG_FUNCPTR(gst_arducamsrc_get_caps);

  pushsrc_class->create = GST_DEBUG_FUNCPTR(gst_arducamsrc_create);
}

static void gst_arducamsrc_init(GstArducamSrc* src) {
  src->width = 640;
  src->height = 480;
  src->fps_num = 30;
  src->fps_den = 1;
  src->frame_count = 0;
  src->is_live = TRUE;
  src->format = FRAME_FMT_RGB;

  gst_base_src_set_live(GST_BASE_SRC(src), TRUE);
  gst_base_src_set_format(GST_BASE_SRC(src), GST_FORMAT_TIME);
}

static void gst_arducamsrc_set_property(GObject* object, guint prop_id,
                                        const GValue* value, GParamSpec* pspec) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(object);

  switch (prop_id) {
    case PROP_WIDTH:
      src->width = g_value_get_uint(value);
      break;
    case PROP_HEIGHT:
      src->height = g_value_get_uint(value);
      break;
    case PROP_FPS_NUM:
      src->fps_num = g_value_get_uint(value);
      break;
    case PROP_FPS_DEN:
      src->fps_den = g_value_get_uint(value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void gst_arducamsrc_get_property(GObject* object, guint prop_id,
                                        GValue* value, GParamSpec* pspec) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(object);

  switch (prop_id) {
    case PROP_WIDTH:
      g_value_set_uint(value, src->width);
      break;
    case PROP_HEIGHT:
      g_value_set_uint(value, src->height);
      break;
    case PROP_FPS_NUM:
      g_value_set_uint(value, src->fps_num);
      break;
    case PROP_FPS_DEN:
      g_value_set_uint(value, src->fps_den);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static gboolean gst_arducamsrc_start(GstBaseSrc* basesrc) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(basesrc);
  src->frame_count = 0;
  return TRUE;
}

static gboolean gst_arducamsrc_stop(GstBaseSrc* basesrc) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(basesrc);
  src->frame_count = 0;
  return TRUE;
}

static GstCaps* gst_arducamsrc_get_caps(GstBaseSrc* basesrc, GstCaps* filter) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(basesrc);

  GstCaps* caps = gst_caps_new_simple(
      "video/x-raw",
      "format", G_TYPE_STRING, format_to_string(src->format),
      "width", G_TYPE_INT, (int)src->width,
      "height", G_TYPE_INT, (int)src->height,
      "framerate", GST_TYPE_FRACTION, (int)src->fps_num, (int)src->fps_den,
      NULL);

  if (filter) {
    GstCaps* intersection = gst_caps_intersect_full(filter, caps, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref(caps);
    return intersection;
  }

  return caps;
}

static GstFlowReturn gst_arducamsrc_create(GstPushSrc* pushsrc, GstBuffer** outbuf) {
  GstArducamSrc* src = GST_ARDUCAM_SRC(pushsrc);

  RawFrame frame = {};
  if (!fill_arducam_frame(&frame)) {
    GST_ERROR_OBJECT(src, "Arducam frame generation failed");
    return GST_FLOW_ERROR;
  }

  if (frame.end_of_stream) {
    release_arducam_frame(&frame);
    return GST_FLOW_EOS;
  }

  GstBuffer* buffer = gst_buffer_new_allocate(NULL, frame.size_bytes, NULL);
  if (!buffer) {
    release_arducam_frame(&frame);
    return GST_FLOW_ERROR;
  }

  gst_buffer_fill(buffer, 0, frame.data, frame.size_bytes);

  GstClockTime duration =
      gst_util_uint64_scale_int(1, GST_SECOND * src->fps_den, src->fps_num);

  if (frame.timestamp_ns != 0) {
    GST_BUFFER_PTS(buffer) = frame.timestamp_ns;
  } else {
    GST_BUFFER_PTS(buffer) = src->frame_count * duration;
  }

  GST_BUFFER_DURATION(buffer) = duration;
  GST_BUFFER_DTS(buffer) = GST_BUFFER_PTS(buffer);

  src->frame_count++;
  release_arducam_frame(&frame);

  *outbuf = buffer;
  return GST_FLOW_OK;
}

static gboolean arducamsrc_plugin_init(GstPlugin* plugin) {
  GST_DEBUG_CATEGORY_INIT(gst_arducamsrc_debug, "arducamsrc", 0, "arducamsrc plugin");

  return gst_element_register(plugin, "arducamsrc", GST_RANK_NONE, GST_TYPE_ARDUCAMSRC);
}

extern "C" {
GST_PLUGIN_DEFINE(
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    arducamsrc,
    DESCRIPTION,
    arducamsrc_plugin_init,
    VERSION,
    LICENSE,
    BINARY_PACKAGE,
    URL)
}