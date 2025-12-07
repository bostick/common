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

#pragma once

#include "common/status.h"

#include <jni.h>

#include <limits> // for numeric_limits
#include <cstddef> // for size_t


const jsize JSIZE_MAX = std::numeric_limits<jsize>::max();


//
// Given jvm, call GetEnv and assert if there is an error
//
#define GETENV(env, jvm) \
    do { \
        jint getEnvRet; \
        ASSERT(jvm != nullptr); \
        if (getEnvRet = jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6); getEnvRet != JNI_OK) { \
            ABORT("Error calling GetEnv: %d", getEnvRet); \
        } \
    } while (false)

//
// Given env, call GetJavaVM and assert if there is an error
//
#define GETJAVAVM(env, jvm) \
    do { \
        jint getJavaVMRet; \
        ASSERT(env != nullptr); \
        if ((getJavaVMRet = env->GetJavaVM(&jvm)) != 0) { \
            ABORT("Error calling GetJavaVM: %d", getJavaVMRet); \
        } \
    } while (false)


#define CHECKNULL(code) \
    do { \
        const void *checkNullLocal = (code); \
        ASSERT(checkNullLocal != nullptr); \
    } while (false)

//
// ExceptionDescribe:
// Prints an exception and a backtrace of the stack to a system error-reporting channel, such as stderr. This is a convenience routine provided for debugging.
//

#define ABORT_ON_EXCEPTION(code) \
    do { \
        ASSERT(env != nullptr); \
        (code); \
        if (env->ExceptionCheck()) { \
            env->ExceptionDescribe(); \
            ABORT("Aborting on pending exception. On Android, check \"System.err\" tag in Logcat for description of exception."); \
        } \
    } while (false)

#define ABORT_ON_EXCEPTION_OR_NULL(code) \
    do { \
        ASSERT(env != nullptr); \
        void *checkExceptionAndNullLocal = (code); \
        if (env->ExceptionCheck()) { \
            env->ExceptionDescribe(); \
            ABORT("Aborting on pending exception. On Android, check \"System.err\" tag in Logcat for description of exception."); \
        } \
        ASSERT(checkExceptionAndNullLocal != nullptr); \
    } while (false)


#define CONSUME_EXCEPTION(code) \
    do { \
        ASSERT(env != nullptr); \
        (code); \
        if (env->ExceptionCheck()) { \
            env->ExceptionClear(); \
        } \
    } while (false)


#define SETCLASS(classVar, classNameString) \
    do { \
        jclass setClassLocal = env->FindClass(classNameString); \
        ABORT_ON_EXCEPTION_OR_NULL(setClassLocal); \
        classVar = reinterpret_cast<jclass>(env->NewGlobalRef(setClassLocal)); \
        ABORT_ON_EXCEPTION_OR_NULL(classVar); \
        env->DeleteLocalRef(setClassLocal); \
    } while (false)

#define INSERTINTOMAP(map, e, code) \
    do { \
        jobject insertIntoMapLocal = (code); \
        ABORT_ON_EXCEPTION_OR_NULL(insertIntoMapLocal); \
        jobject objectVar = env->NewGlobalRef(insertIntoMapLocal); \
        ABORT_ON_EXCEPTION_OR_NULL(objectVar); \
        map[e] = objectVar; \
        env->DeleteLocalRef(insertIntoMapLocal); \
    } while (false)


jobject createStatusObject(JNIEnv *env, Status status);


//
// log functions only for newArrayObject below
//
void newArrayObject_logCount(size_t count);

void newArrayObject_log(const char *msg);

//
// function template for creating array objects
//
// Example:
// const sockaddr_storage *addresses;
// size_t count;
// newArrayObject<sockaddr_storage, newInetSocketAddress>(env, addresses, count, InetSocketAddress_class)
//
template <typename T, jobject (*F)(JNIEnv *, const T &)>
jobjectArray newArrayObject(JNIEnv *env, const T *buffer, size_t count, jclass clazz) {

    if (count > JSIZE_MAX) {
        newArrayObject_logCount(count);
        return nullptr;
    }

    auto jCount = static_cast<jsize>(count);

    jobjectArray arrayObj = env->NewObjectArray(jCount, clazz, nullptr);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        return nullptr;
    }
    if (arrayObj == nullptr) {
        newArrayObject_log("Error creating array object");
        return nullptr;
    }

    for (jsize i = 0; i < jCount; i++) {

        jobject obj = F(env, buffer[i]);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            return nullptr;
        }
        if (obj == nullptr) {
            newArrayObject_log("Error assigning object to array");
            return nullptr;
        }

        env->SetObjectArrayElement(arrayObj, i, obj);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            return nullptr;
        }

        env->DeleteLocalRef(obj);
    }

    return arrayObj;
}


class ScopedJniString {
private:

    JNIEnv *env;
    jstring jstr;
    const char *str;

public:
    ScopedJniString(JNIEnv *env, jstring jstr);

    ~ScopedJniString();

    const char *get();
};


class ScopedJniEnv {
private:

    JavaVM *jvm;
    JNIEnv *env;
    jint getEnvRet;

public:

    explicit ScopedJniEnv(JavaVM *jvm);

    ~ScopedJniEnv();

    JNIEnv *get();
};


class ScopedJniPrimitiveArrayCritical {
private:

    JNIEnv *env;
    jarray jarr;
    void *data;

public:
    ScopedJniPrimitiveArrayCritical(JNIEnv *env, jarray jarr);

    ~ScopedJniPrimitiveArrayCritical();

    void *get();
};


class ScopedJniByteArray {
private:

    JNIEnv *env;
    jbyteArray jarr;
    jbyte *data;

public:
    ScopedJniByteArray(JNIEnv *env, jbyteArray jarr);

    ~ScopedJniByteArray();

    const jbyte *get();
};
















