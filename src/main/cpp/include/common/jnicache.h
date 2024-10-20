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

#include "common/platform.h"
#include "common/status.h"

#include <jni.h>

#include <map>


#define EXCEPTIONANDNULLCHECK(var) \
  do { \
    if (env->ExceptionCheck()) { \
      ASSERT(false && "Exception"); \
    } \
    if ((var) == NULL) { \
      ASSERT(false && #var " is NULL"); \
    } \
  } while (false)

#define SETCLASS(classVar, classNameString) \
  do { \
    jclass classVar ## _local = env->FindClass(classNameString); \
    EXCEPTIONANDNULLCHECK(classVar ## _local); \
    classVar = reinterpret_cast<jclass>(env->NewGlobalRef(classVar ## _local)); \
    EXCEPTIONANDNULLCHECK(classVar); \
    env->DeleteLocalRef(classVar ## _local); \
  } while (false)

#define INSERTINTOMAP(map, e, code) \
  do { \
    jobject local = code; \
    EXCEPTIONANDNULLCHECK(local); \
    jobject objectVar = env->NewGlobalRef(local); \
    EXCEPTIONANDNULLCHECK(objectVar); \
    map[e] = objectVar; \
    env->DeleteLocalRef(local); \
  } while (false)


//
// Classes
//

extern jclass File_class;
extern jclass Status_class;
#if IS_PLATFORM_ANDROID
extern jclass Build_class;
extern jclass JSONArray_class;
extern jclass JSONObject_class;
#endif // IS_PLATFORM_ANDROID

//
// Instance fields
//

//
// Static fields
//
#if IS_PLATFORM_ANDROID
extern jfieldID Build_MODEL_field;
#endif // IS_PLATFORM_ANDROID

//
// Instance methods
//
extern jmethodID File_getAbsolutePath_method;
extern jmethodID JSONArray_getDouble_method;
extern jmethodID JSONArray_getJSONArray_method;
extern jmethodID JSONArray_length_method;
extern jmethodID JSONObject_has_method;
extern jmethodID JSONObject_getJSONArray_method;

//
// Static methods
//

extern jmethodID Status_fromInt_method;

//
// Enums
//

extern std::map<Status, jobject> statusEnumMap;
















