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

#include "common/common_jnicache.h"

#undef NDEBUG

#include "common/abort.h"
#include "common/assert.h"
#include "common/common_jniutils.h"
#include "common/logging.h"
#include "common/platform.h"
#include "common/status.h"


#define TAG "common_jnicache"


using enum Status;


//
// Classes
//

// jclass AtomicBoolean_class;
jclass File_class;
jclass Status_class;
#if IS_PLATFORM_ANDROID
jclass Activity_class;
jclass Build_class;
jclass JSONArray_class;
jclass JSONObject_class;
#endif // IS_PLATFORM_ANDROID

//
// Instance fields
//

//
// Static fields
//

#if IS_PLATFORM_ANDROID
jfieldID Build_MODEL_field;
#endif // IS_PLATFORM_ANDROID

//
// Instance methods
//

// jmethodID AtomicBoolean_set_method;
jmethodID File_getAbsolutePath_method;
//jmethodID Status_toByte_method;
#if IS_PLATFORM_ANDROID
jmethodID Activity_getPackageName_method;
jmethodID JSONArray_getDouble_method;
jmethodID JSONArray_getInt_method;
jmethodID JSONArray_getJSONArray_method;
jmethodID JSONArray_length_method;
jmethodID JSONObject_getDouble_method;
jmethodID JSONObject_getJSONArray_method;
jmethodID JSONObject_has_method;
#endif // IS_PLATFORM_ANDROID

//
// Static methods
//

jmethodID Status_fromByte_method;

//
// Enums
//

std::map<Status, jobject> statusEnumMap;


void setupCommonJniCache(JavaVM *jvm) {

    JNIEnv *env; // NOLINT(*-init-variables)
    GETENV(env, jvm);

    //
    // Classes
    //

//    SETCLASS(AtomicBoolean_class, "java/util/concurrent/atomic/AtomicBoolean");
    SETCLASS(File_class, "java/io/File");
    SETCLASS(Status_class, "com/brentonbostick/common/Status");
#if IS_PLATFORM_ANDROID
    SETCLASS(Activity_class, "android/app/Activity");
    SETCLASS(Build_class, "android/os/Build");
    SETCLASS(JSONArray_class, "org/json/JSONArray");
    SETCLASS(JSONObject_class, "org/json/JSONObject");
#endif // IS_PLATFORM_ANDROID

    //
    // Instance fields
    //

    //
    // Static fields
    //

#if IS_PLATFORM_ANDROID
    ABORT_ON_EXCEPTION_OR_NULL(Build_MODEL_field = env->GetStaticFieldID(Build_class, "MODEL", "Ljava/lang/String;"));
#endif // IS_PLATFORM_ANDROID

    //
    // Instance methods
    //

//    ABORT_ON_EXCEPTION_OR_NULL(AtomicBoolean_set_method = env->GetMethodID(AtomicBoolean_class, "set", "(Z)V"));
    ABORT_ON_EXCEPTION_OR_NULL(File_getAbsolutePath_method = env->GetMethodID(File_class, "getAbsolutePath", "()Ljava/lang/String;"));
//    ABORT_ON_EXCEPTION_OR_NULL(Status_toByte_method = env->GetMethodID(Status_class, "toByte", "()B"));
#if IS_PLATFORM_ANDROID
    ABORT_ON_EXCEPTION_OR_NULL(Activity_getPackageName_method = env->GetMethodID(Activity_class, "getPackageName", "()Ljava/lang/String;"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONArray_getDouble_method = env->GetMethodID(JSONArray_class, "getDouble", "(I)D"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONArray_getInt_method = env->GetMethodID(JSONArray_class, "getInt", "(I)I"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONArray_getJSONArray_method = env->GetMethodID(JSONArray_class, "getJSONArray", "(I)Lorg/json/JSONArray;"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONArray_length_method = env->GetMethodID(JSONArray_class, "length", "()I"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONObject_getDouble_method = env->GetMethodID(JSONObject_class, "getDouble", "(Ljava/lang/String;)D"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONObject_getJSONArray_method = env->GetMethodID(JSONObject_class, "getJSONArray", "(Ljava/lang/String;)Lorg/json/JSONArray;"));
    ABORT_ON_EXCEPTION_OR_NULL(JSONObject_has_method = env->GetMethodID(JSONObject_class, "has", "(Ljava/lang/String;)Z"));
#endif // IS_PLATFORM_ANDROID

    //
    // Static methods
    //

    ABORT_ON_EXCEPTION_OR_NULL(Status_fromByte_method = env->GetStaticMethodID(Status_class, "fromByte", "(B)Lcom/brentonbostick/common/Status;"));

    //
    // Enums
    //

    INSERTINTOMAP(statusEnumMap, OK, createStatusObject(env, OK));
    INSERTINTOMAP(statusEnumMap, ERR, createStatusObject(env, ERR));
}

void teardownCommonJniCache(JavaVM *jvm) {

    JNIEnv *env; // NOLINT(*-init-variables)
    GETENV(env, jvm);

    env->DeleteGlobalRef(statusEnumMap[OK]);
    //
    // incorrect warning "Index may have a value of '-1' which is out of bounds"
    //
    env->DeleteGlobalRef(statusEnumMap[ERR]);
    statusEnumMap.clear();

//    env->DeleteGlobalRef(AtomicBoolean_class);
    env->DeleteGlobalRef(File_class);
    env->DeleteGlobalRef(Status_class);
#if IS_PLATFORM_ANDROID
    env->DeleteGlobalRef(Activity_class);
    env->DeleteGlobalRef(Build_class);
    env->DeleteGlobalRef(JSONArray_class);
    env->DeleteGlobalRef(JSONObject_class);
#endif // IS_PLATFORM_ANDROID
}
















