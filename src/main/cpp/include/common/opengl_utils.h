
#pragma once

#include <GLES3/gl3.h>


#define CHECKGLERROR(code) \
    do { \
        (code); \
        const GLenum checkGLErrorLocal = glGetError();   \
        if (checkGLErrorLocal != GL_NO_ERROR) {          \
            ABORT("GL error: %s", GLErrorName(checkGLErrorLocal)); \
        }                   \
    } while (false)


const char *GLErrorName(GLenum e);
















