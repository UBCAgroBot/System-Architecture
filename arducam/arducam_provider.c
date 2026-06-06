#include <arducam/arducam_evk_sdk.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// camera state
typedef struct {
    ArducamCameraHandle camera;
    ArducamImageFrame image;
    bool has_image;            // for future to make the code more robust (preventing double freeing)
} ArducamProvider;

ArducamProvider* arducam_provider_create(const char* config_path) {
    ArducamProvider* provider = malloc(sizeof(ArducamProvider));
    ArducamCameraOpenParam param;              // struct with parameters used to open arducam
    ArducamDefaultParam(&param);               // initialize default values for ArducamCameraOpenParam struct 
    param.config_file_name = config_path;
    ArducamOpenCamera(&provider->camera, &param);
    ArducamInitCamera(provider->camera);
    ArducamStartCamera(provider->camera);
    return provider;
}

bool getFrame(void* user_data, RawFrame* frame) {
    ArducamProvider* provider = (ArducamProvider*) user_data;
    if (ArducamCaptureImage(provider->camera, &provider->image, 1000) == Success) {  // read frame from arducam
        frame->data = provider->image.data;
        frame->size_bytes = provider->image.format.width * provider->image.format.height * 3; // 3 bytes per pixel (RGB)
        frame->end_of_stream = false;
        return true;
    }
    return false;
}

void releaseFrame(void* user_data, RawFrame* frame) {
    ArducamProvider* provider = (ArducamProvider*) user_data;
    ArducamFreeImage(provider->camera, provider->image);
}

// cleanup
void arducam_provider_destroyer(ArducamProvider* provider) {
    ArducamStopCamera(provider->camera);
    ArducamCloseCamera(provider->camera);
    free(provider);
}