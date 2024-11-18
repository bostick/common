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

#include "common/common_jnicache.h"

#include "common/assert.h"
#include "common/common_jniutils.h"
#include "common/platform.h"
#include "common/status.h"


#define TAG "common_jnicache"


//
// Classes
//
// jclass AtomicBoolean_class;
jclass File_class;
jclass Status_class;
#if IS_PLATFORM_ANDROID
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
jmethodID Status_toInt_method;
#if IS_PLATFORM_ANDROID
jmethodID JSONArray_getDouble_method;
jmethodID JSONArray_getInt_method;
jmethodID JSONArray_getJSONArray_method;
jmethodID JSONArray_length_method;
jmethodID JSONObject_getJSONArray_method;
jmethodID JSONObject_has_method;
#endif // IS_PLATFORM_ANDROID

//
// Static methods
//

jmethodID Status_fromInt_method;

//
// Enums
//

std::map<Status, jobject> statusEnumMap;


void setupCommonJniCache(JavaVM *vm) {

    JNIEnv *env;
    GETENV(env, vm);

    //
    // Classes
    //
    // SETCLASS(AtomicBoolean_class, "java/util/concurrent/atomic/AtomicBoolean");
    SETCLASS(File_class, "java/io/File");
    SETCLASS(Status_class, "com/brentonbostick/common/Status");
#if IS_PLATFORM_ANDROID
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
    CHECKEXCEPTIONANDNULL(Build_MODEL_field = env->GetStaticFieldID(Build_class, "MODEL", "Ljava/lang/String;"));
#endif // IS_PLATFORM_ANDROID

    //
    // Instance methods
    //
    // EXCEPTIONANDNULLCHECK(AtomicBoolean_set_method = env->GetMethodID(AtomicBoolean_class, "set", "(Z)V"));
    CHECKEXCEPTIONANDNULL(File_getAbsolutePath_method = env->GetMethodID(File_class, "getAbsolutePath", "()Ljava/lang/String;"));
    CHECKEXCEPTIONANDNULL(Status_toInt_method = env->GetMethodID(Status_class, "toInt", "()I"));
#if IS_PLATFORM_ANDROID
    CHECKEXCEPTIONANDNULL(JSONArray_getDouble_method = env->GetMethodID(JSONArray_class, "getDouble", "(I)D"));
    CHECKEXCEPTIONANDNULL(JSONArray_getInt_method = env->GetMethodID(JSONArray_class, "getInt", "(I)I"));
    CHECKEXCEPTIONANDNULL(JSONArray_getJSONArray_method = env->GetMethodID(JSONArray_class, "getJSONArray", "(I)Lorg/json/JSONArray;"));
    CHECKEXCEPTIONANDNULL(JSONArray_length_method = env->GetMethodID(JSONArray_class, "length", "()I"));
    CHECKEXCEPTIONANDNULL(JSONObject_getJSONArray_method = env->GetMethodID(JSONObject_class, "getJSONArray", "(Ljava/lang/String;)Lorg/json/JSONArray;"));
    CHECKEXCEPTIONANDNULL(JSONObject_has_method = env->GetMethodID(JSONObject_class, "has", "(Ljava/lang/String;)Z"));
#endif // IS_PLATFORM_ANDROID

    //
    // Static methods
    //

    CHECKEXCEPTIONANDNULL(Status_fromInt_method = env->GetStaticMethodID(Status_class, "fromInt", "(I)Lcom/brentonbostick/common/Status;"));

    //
    // Enums
    //

    INSERTINTOMAP(statusEnumMap, OK, createStatusObject(env, OK));
    INSERTINTOMAP(statusEnumMap, ERR, createStatusObject(env, ERR));
}

void teardownCommonJniCache(JavaVM *vm) {

    JNIEnv *env;
    GETENV(env, vm);

    env->DeleteGlobalRef(statusEnumMap[OK]);
    env->DeleteGlobalRef(statusEnumMap[ERR]);
    statusEnumMap.clear();

    // env->DeleteGlobalRef(AtomicBoolean_class);
    env->DeleteGlobalRef(File_class);
    env->DeleteGlobalRef(Status_class);
#if IS_PLATFORM_ANDROID
    env->DeleteGlobalRef(Build_class);
    env->DeleteGlobalRef(JSONArray_class);
    env->DeleteGlobalRef(JSONObject_class);
#endif // IS_PLATFORM_ANDROID
}

















