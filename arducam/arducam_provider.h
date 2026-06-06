#ifndef ARDUCAM_PROVIDER_H
#define ARDUCAM_PROVIDER_H

#include <stdbool.h>

typedef struct ArducamProvider ArducamProvider;

ArducamProvider* arducam_provider_create(const char* config_path);
bool getFrame(void* user_data, RawFrame* frame);
void releaseFrame(void* user_data, RawFrame* frame);
void arducam_provider_destroyer(ArducamProvider* provider);

#endif