// Copyright (C) 2024 by Brenton Bostick
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

#include "common/jniutils.h"

#include "common/jnicache.h"
#include "common/logging.h"
#include "common/status.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nullptr"


#define TAG "jniutils"


jobject createStatusObject(JNIEnv *env, Status status) {

    jobject resultObject = env->CallStaticObjectMethod(Status_class, Status_fromInt_method, static_cast<jint>(status));
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        return NULL;
    }
    if (resultObject == NULL) {
        LOGE("Status_fromInt_method failed");
        return NULL;
    }

    return resultObject;
}


ScopedJniString::ScopedJniString(JNIEnv *env, jstring jstr) :
    env(env),
    jstr(jstr) {

    str = env->GetStringUTFChars(jstr, NULL);
}

ScopedJniString::~ScopedJniString() {

    if (str == NULL) {
        return;
    }

    env->ReleaseStringUTFChars(jstr, str);
}

const char *ScopedJniString::get() {
    return str;
}


ScopedJniEnv::ScopedJniEnv(JavaVM *jvm) :
    jvm(jvm),
    env(),
    attached(false) {

    jint res;
    if ((res = jvm->AttachCurrentThread(&env, NULL)) != JNI_OK) {
        LOGE("Error calling AttachCurrentThread: %d", res);
        return;
    }

    attached = true;
}

ScopedJniEnv::~ScopedJniEnv() {

    if (!attached) {
        return;
    }

    jint res;
    if ((res = jvm->DetachCurrentThread()) != JNI_OK) {
        LOGE("Error calling DetachCurrentThread: %d", res);
        return;
    }
}

JNIEnv *ScopedJniEnv::get() {
    return env;
}



#pragma clang diagnostic pop








