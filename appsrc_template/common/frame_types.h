#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum FramePixelFormat {
    FRAME_FMT_RGB = 0,
    FRAME_FMT_BGR = 1,
    FRAME_FMT_GRAY8 = 2
} FramePixelFormat;

typedef struct RawFrame {
    uint8_t* data;
    size_t size_bytes;
    int width;
    int height;
    int stride;
    FramePixelFormat format;
    uint64_t timestamp_ns;   // 0 if provider does not supply one
    bool end_of_stream;
} RawFrame;

#ifdef __cplusplus
}
#endif
