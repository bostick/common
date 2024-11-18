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

#pragma once

#include "common/status.h"

#include "common/abort.h"
#include "common/assert.h"

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
        ASSERT(jvm != NULL); \
        if ((getEnvRet = jvm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6)) != JNI_OK) { \
            ABORT("Error calling GetEnv: %d", getEnvRet); \
        } \
    } while (false)

//
// Given env, call GetJavaVM and assert if there is an error
//
#define GETJAVAVM(env, jvm) \
    do { \
        jint getJavaVMRet; \
        ASSERT(env != NULL); \
        if ((getJavaVMRet = env->GetJavaVM(&jvm)) != 0) { \
            ABORT("Error calling GetJavaVM: %d", getJavaVMRet); \
        } \
    } while (false)


#define CHECKNULL(code) \
    do { \
        const void *checkNullLocal = (code); \
        ASSERT(checkNullLocal != NULL); \
    } while (false)

#define CHECKEXCEPTION(code) \
    do { \
        ASSERT(env != NULL); \
        (code); \
        ASSERT(!env->ExceptionCheck() || (env->ExceptionDescribe(), "Aborting on pending exception. On Android, check \"System.err\" tag in Logcat for description of exception.")); \
    } while (false)

#define CHECKEXCEPTIONANDNULL(code) \
    do { \
        ASSERT(env != NULL); \
        void *checkExceptionAndNullLocal = (code); \
        ASSERT(!env->ExceptionCheck() || (env->ExceptionDescribe(), "Aborting on pending exception. On Android, check \"System.err\" tag in Logcat for description of exception.")); \
        ASSERT(checkExceptionAndNullLocal != NULL); \
    } while (false)


#define SETCLASS(classVar, classNameString) \
    do { \
        jclass setClassLocal = env->FindClass(classNameString); \
        CHECKEXCEPTIONANDNULL(setClassLocal); \
        classVar = reinterpret_cast<jclass>(env->NewGlobalRef(setClassLocal)); \
        CHECKEXCEPTIONANDNULL(classVar); \
        env->DeleteLocalRef(setClassLocal); \
    } while (false)

#define INSERTINTOMAP(map, e, code) \
    do { \
        jobject insertIntoMapLocal = (code); \
        CHECKEXCEPTIONANDNULL(insertIntoMapLocal); \
        jobject objectVar = env->NewGlobalRef(insertIntoMapLocal); \
        CHECKEXCEPTIONANDNULL(objectVar); \
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
        return NULL;
    }

    auto jCount = static_cast<jsize>(count);

    jobjectArray arrayObj = env->NewObjectArray(jCount, clazz, NULL);
    if (env->ExceptionCheck()) {
        env->ExceptionDescribe();
        return NULL;
    }
    if (arrayObj == NULL) {
        newArrayObject_log("Error creating array object");
        return NULL;
    }

    for (jsize i = 0; i < jCount; i++) {

        jobject obj = F(env, buffer[i]);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            return NULL;
        }
        if (obj == NULL) {
            newArrayObject_log("Error assigning object to array");
            return NULL;
        }

        env->SetObjectArrayElement(arrayObj, i, obj);
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            return NULL;
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
















