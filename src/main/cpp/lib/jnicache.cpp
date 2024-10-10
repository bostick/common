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

#include "common/jnicache.h"

#include "common/assert.h"
#include "common/jniutils.h"
#include "common/platform.h"
#include "common/status.h"


#define TAG "jnicache"


//
// Classes
//

jclass Status_class;
#if IS_PLATFORM_ANDROID
jclass DisplayMetrics_class;
jclass Build_class;
#endif // IS_PLATFORM_ANDROID

//
// Instance fields
//
#if IS_PLATFORM_ANDROID
jfieldID DisplayMetrics_widthPixels_field;
jfieldID DisplayMetrics_heightPixels_field;
jfieldID DisplayMetrics_xdpi_field;
jfieldID DisplayMetrics_ydpi_field;
#endif // IS_PLATFORM_ANDROID

//
// Static fields
//
#if IS_PLATFORM_ANDROID
jfieldID Build_MODEL_field;
#endif // IS_PLATFORM_ANDROID

//
// Instance methods
//

//
// Static methods
//

jmethodID Status_fromInt_method;

//
// Enums
//

std::map<Status, jobject> statusEnumMap;


void setupJNICache(JavaVM *vm) {

  JNIEnv *env;
  GETENV(env, vm);

  //
  // Classes
  //

  SETCLASS(Status_class, "com/brentonbostick/common/Status");
#if IS_PLATFORM_ANDROID
  SETCLASS(DisplayMetrics_class, "android/util/DisplayMetrics");
  SETCLASS(Build_class, "android/os/Build");
#endif // IS_PLATFORM_ANDROID

  //
  // Instance fields
  //
#if IS_PLATFORM_ANDROID
  EXCEPTIONANDNULLCHECK(DisplayMetrics_widthPixels_field = env->GetFieldID(DisplayMetrics_class, "widthPixels", "I"));
  EXCEPTIONANDNULLCHECK(DisplayMetrics_heightPixels_field = env->GetFieldID(DisplayMetrics_class, "widthPixels", "I"));
  EXCEPTIONANDNULLCHECK(DisplayMetrics_xdpi_field = env->GetFieldID(DisplayMetrics_class, "xdpi", "F"));
  EXCEPTIONANDNULLCHECK(DisplayMetrics_ydpi_field = env->GetFieldID(DisplayMetrics_class, "ydpi", "F"));
#endif // IS_PLATFORM_ANDROID

  //
  // Static fields
  //
#if IS_PLATFORM_ANDROID
  EXCEPTIONANDNULLCHECK(Build_MODEL_field = env->GetStaticFieldID(Build_class, "MODEL", "Ljava/lang/String;"));
#endif // IS_PLATFORM_ANDROID

  //
  // Instance methods
  //

  //
  // Static methods
  //

  EXCEPTIONANDNULLCHECK(Status_fromInt_method = env->GetStaticMethodID(Status_class, "fromInt", "(I)Lcom/brentonbostick/common/Status;"));

  //
  // Enums
  //

  INSERTINTOMAP(statusEnumMap, Status::OK, createStatusObject(env, Status::OK));
  INSERTINTOMAP(statusEnumMap, Status::ERR, createStatusObject(env, Status::ERR));
  INSERTINTOMAP(statusEnumMap, Status::CONTINUE, createStatusObject(env, Status::CONTINUE));
}

void teardownJNICache(JavaVM *vm) {

  JNIEnv *env;
  GETENV(env, vm);

  env->DeleteGlobalRef(Status_class);

#if IS_PLATFORM_ANDROID
  env->DeleteGlobalRef(DisplayMetrics_class);
  env->DeleteGlobalRef(Build_class);
#endif // IS_PLATFORM_ANDROID
}













