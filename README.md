# common

Common utilities used in different projects.

This is a C++ source library and the source files are intended to be used in other projects.


## Overview

* abort: ABORT macro
* assert: ASSERT macro
* check: CHECK macros
* clock: clock functions
* file: functions for opening and saving files
* jnicache: cache various classes, methods, and fields for JNI
* jniutils: utility macros and functions for JNI
* logging: functions for logging
* platform: platform macros
* status: Status enum for return types



## Usage

Functions in common may be compiled as C or C++.

If compiling as C++, then common requires a C++20 compiler because of features such as `__VA_OPT__`.

If compiling as C, then common requires a C compiler that supports `__VA_OPT__`. This can be a compiler that may not completely support C23 yet, as long as `__VA_OPT__` is supported.



## JniCache

Caching jclass, jmethodID, and jfieldID objects speeds up performance.



## Logging

Calling the logging functions with no arguments
```
LOGI();
```
is completely fine and is equivalent to `LOGI("")`, which logs an empty newline.

Arguments for SetLogLevel are:
```
LOGLEVEL_FATAL
LOGLEVEL_ERROR
LOGLEVEL_WARN
LOGLEVEL_INFO
LOGLEVEL_DEBUG
LOGLEVEL_TRACE
```





