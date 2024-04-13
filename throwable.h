//
// Created by DELL on 24-4-13.
//

#ifndef THROWABLE_H
#define THROWABLE_H

#include "libfhraisepy_api.h"

typedef struct {
    char *type;
    libfhraisepy_KNativePtr ref;
    char *message;
    char **stacktrace;
    int stacktraceSize;
} Throwable;

#endif //THROWABLE_H
