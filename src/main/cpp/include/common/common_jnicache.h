// Copyright (C) 2026 by Brenton Bostick
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


//
// Classes
//

// extern jclass AtomicBoolean_class;
extern jclass File_class;
extern jclass IOException_class;
extern jclass Status_class;
extern jclass Throwable_class;
extern jclass ExceptionUtils_class;
#if IS_PLATFORM_ANDROID
extern jclass Activity_class;
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

// extern jmethodID AtomicBoolean_set_method;
extern jmethodID File_getAbsolutePath_method;
//extern jmethodID Status_toByte_method;
extern jmethodID Throwable_getMessage_method;
#if IS_PLATFORM_ANDROID
extern jmethodID Activity_getPackageName_method;
extern jmethodID JSONArray_getDouble_method;
extern jmethodID JSONArray_getInt_method;
extern jmethodID JSONArray_getJSONArray_method;
extern jmethodID JSONArray_length_method;
extern jmethodID JSONObject_has_method;
extern jmethodID JSONObject_getDouble_method;
extern jmethodID JSONObject_getJSONArray_method;
#endif // IS_PLATFORM_ANDROID

//
// Static methods
//

extern jmethodID Status_fromByte_method;
extern jmethodID ExceptionUtils_toNiceString_method;

//
// Enums
//

extern std::map<Status, jobject> statusEnumMap;


void setupCommonJniCache(JavaVM *jvm);
void teardownCommonJniCache(JavaVM *jvm);
















