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

#include "common/common_jniutils.h"

#undef NDEBUG

#include "common/abort.h"
#include "common/assert.h"
#include "common/common_jnicache.h"
#include "common/logging.h"
#include "common/status.h"


#define TAG "common_jniutils"


jobject createStatusObject(JNIEnv *env, Status status) {

    jobject jstatus; // NOLINT(*-init-variables)
    CHECKEXCEPTIONANDNULL(jstatus = env->CallStaticObjectMethod(Status_class, Status_fromByte_method, static_cast<jbyte>(status)));

    return jstatus;
}


ScopedJniString::ScopedJniString(JNIEnv *env, jstring jstr) :
    env(env),
    jstr(jstr) {

    CHECKNULL(str = env->GetStringUTFChars(jstr, NULL));
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
    getEnvRet() {

    getEnvRet = jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);

    ASSERT(getEnvRet != JNI_EVERSION);

    if (getEnvRet == JNI_OK) {
        return;
    }

    ASSERT(getEnvRet == JNI_EDETACHED);

    jint res;
    if (res = jvm->AttachCurrentThread(&env, NULL); res != JNI_OK) {
        ABORT("Error calling AttachCurrentThread: %d", res);
    }
}

ScopedJniEnv::~ScopedJniEnv() {

    if (getEnvRet != JNI_EDETACHED) {
        return;
    }

    jint res;
    if (res = jvm->DetachCurrentThread(); res != JNI_OK) {
        ABORT("Error calling DetachCurrentThread: %d", res);
    }
}

JNIEnv *ScopedJniEnv::get() {
    return env;
}


ScopedJniPrimitiveArrayCritical::ScopedJniPrimitiveArrayCritical(JNIEnv *env, jarray jarr) :
    env(env),
    jarr(jarr) {

    CHECKNULL(data = env->GetPrimitiveArrayCritical(jarr, NULL));
}

ScopedJniPrimitiveArrayCritical::~ScopedJniPrimitiveArrayCritical() {
    env->ReleasePrimitiveArrayCritical(jarr, data, 0);
}

void *ScopedJniPrimitiveArrayCritical::get() {
    return data;
}
















