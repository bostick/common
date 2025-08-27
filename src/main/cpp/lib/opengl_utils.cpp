
#include "common/opengl_utils.h"

#include "common/abort.h"


#define TAG "opengl_utils"


const char *GLErrorName(GLenum e) {

    switch(e) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
        default:
            ABORT("GLErrorName: unhandled error: %d", e);
    }
}
















