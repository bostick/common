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

//
// Classes
//

extern jclass Status_class;

#if IS_PLATFORM_ANDROID
extern jclass DisplayMetrics_class;
extern jclass Build_class;
#endif // IS_PLATFORM_ANDROID

//
// Instance fields
//
#if IS_PLATFORM_ANDROID
extern jfieldID DisplayMetrics_widthPixels_field;
extern jfieldID DisplayMetrics_heightPixels_field;
extern jfieldID DisplayMetrics_xdpi_field;
extern jfieldID DisplayMetrics_ydpi_field;
#endif // IS_PLATFORM_ANDROID

//
// Static fields
//
#if IS_PLATFORM_ANDROID
extern jfieldID Build_MODEL_field;
#endif // IS_PLATFORM_ANDROID

//
// Instance methods
//

//
// Static methods
//

extern jmethodID Status_fromInt_method;

//
// Enums
//

extern std::map<Status, jobject> statusEnumMap;

void setupJNICache(JavaVM *vm);
void teardownJNICache(JavaVM *vm);
















