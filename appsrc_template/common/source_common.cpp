#include "source_common.h"

const char* format_to_string(FramePixelFormat fmt) {
    switch (fmt) {
        case FRAME_FMT_RGB: return "RGB";
        case FRAME_FMT_BGR: return "BGR";
        case FRAME_FMT_GRAY8: return "GRAY8";
        default: return "RGB";
    }
}
