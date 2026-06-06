#ifndef __GST_ARDUCAM_SRC_H__
#define __GST_ARDUCAM_SRC_H__

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>
#include <gst/video/video.h>

#include "common/frame_types.h"

/* Package and library details required for plugin_init */
#define PACKAGE        "arducamsrc"
#define VERSION        "1.0"
#define LICENSE        "Proprietary"
#define DESCRIPTION    "Arducam source plugin with internal frame generator"
#define BINARY_PACKAGE "Custom Arducam source plugin"
#define URL            "http://example.com/"

G_BEGIN_DECLS

typedef struct _GstArducamSrc      GstArducamSrc;
typedef struct _GstArducamSrcClass GstArducamSrcClass;

#define GST_TYPE_ARDUCAMSRC (gst_arducamsrc_get_type())
#define GST_ARDUCAM_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_ARDUCAMSRC, GstArducamSrc))
#define GST_ARDUCAM_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_ARDUCAMSRC, GstArducamSrcClass))
#define GST_IS_ARDUCAM_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_ARDUCAMSRC))
#define GST_IS_ARDUCAM_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_ARDUCAMSRC))

struct _GstArducamSrc {
  GstPushSrc parent;

  guint width;
  guint height;
  guint fps_num;
  guint fps_den;
  guint64 frame_count;
  gboolean is_live;

  FramePixelFormat format;
  GstVideoInfo video_info;
};

struct _GstArducamSrcClass {
  GstPushSrcClass parent_class;
};

GType gst_arducamsrc_get_type(void);

G_END_DECLS

#endif