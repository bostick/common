// Copyright (C) 2025 by Brenton Bostick
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
// OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "common/transient_message.h"

#undef NDEBUG

#include "common/assert.h"
#include "common/platform.h"

#if IS_PLATFORM_ANDROID
#include "common/common_jniutils.h"
#endif // IS_PLATFORM_ANDROID

#if IS_PLATFORM_ANDROID
#include <jni.h>
#endif // IS_PLATFORM_ANDROID

#include <string>


#define TAG "transient_message"


transientMessageCapturer_decl transientMessageCapturer = nullptr;


void captureTransientMessage(const char *message) {

    ASSERT(transientMessageCapturer != nullptr);

    transientMessageCapturer(message);
}


//
// JNI functions
//

#if IS_PLATFORM_ANDROID

extern "C"
JNIEXPORT void JNICALL
Java_com_brentonbostick_common_TransientMessage_captureTransientMessageNative(JNIEnv *env, jclass clazz, jstring jmsg) {

    (void)clazz;

    ScopedJniString x{env, jmsg};

    const char *tmpMsg = x.get();

    captureTransientMessage(tmpMsg);
}

#endif // IS_PLATFORM_ANDROID
















