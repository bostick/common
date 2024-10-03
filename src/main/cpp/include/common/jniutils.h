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

#include <jni.h>

#include <limits> // for numeric_limits

const jsize JSIZE_MAX = std::numeric_limits<jsize>::max();


//
// Call GetEnv and assert if there is an error
//
#define GETENV(env, vm) \
  do { \
    jint getEnvRet; \
    ASSERT(vm); \
    if ((getEnvRet = vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6)) != JNI_OK) { \
      LOGE("Error calling GetEnv: %d", getEnvRet); \
      ASSERT(false && "Error calling GetEnv"); \
    } \
  } while (false)

//
// Call GetJavaVM and assert if there is an error
//
#define GETJAVAVM(env, vm) \
  do { \
    jint getJavaVMRet; \
    if ((getJavaVMRet = env->GetJavaVM(&vm)) != 0) { \
      LOGE("Error calling GetJavaVM: %d", getJavaVMRet); \
      ASSERT(false && "Error calling GetJavaVM"); \
    } \
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
template <typename T, jobject (*F)(JNIEnv *, const T &)>
jobjectArray newArrayObject(JNIEnv *env, const T *buffer, size_t count, jclass clazz) {

  if (count > JSIZE_MAX) {
    newArrayObject_logCount(count);
    return NULL;
  }

  auto jCount = static_cast<jsize>(count);

  jobjectArray arrayObj = env->NewObjectArray(jCount, clazz, NULL);
  if (env->ExceptionCheck() || arrayObj == NULL) {
    newArrayObject_log("Error creating array object");
    return NULL;
  }

  for (jsize i = 0; i < jCount; i++) {

    jobject obj = F(env, buffer[i]);
    if (env->ExceptionCheck() || obj == NULL) {
      return NULL;
    }

    env->SetObjectArrayElement(arrayObj, i, obj);
    if (env->ExceptionCheck()) {
      newArrayObject_log("Error assigning object to array");
      return NULL;
    }

    env->DeleteLocalRef(obj);
  }

  return arrayObj;
}
















