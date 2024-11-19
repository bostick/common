# Copyright (C) 2024 by Brenton Bostick
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all copies or substantial
# portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
# OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


set(SOURCES_LIB
    abort.cpp
    clock.cpp
    file.cpp
    logging.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")

list(APPEND SOURCES_LIB
    jnicache.cpp
    jniutils.cpp
)

endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "iOS" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

list(APPEND SOURCES_LIB
    clock.mm
)

endif()

add_library(common-lib STATIC
    ${SOURCES_LIB}
)

target_include_directories(common-lib
    PUBLIC
        ../include
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")

target_link_libraries(common-lib
    PRIVATE
        log
)

endif()


#
# Set up warnings
#
# https://www.foonathan.net/2018/10/cmake-warnings/
#
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
target_compile_options(common-lib PRIVATE
    -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion -Wno-unknown-pragmas -Wno-unused-const-variable
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
target_compile_options(common-lib PRIVATE
    -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion -Wno-unknown-pragmas -Wno-unused-const-variable
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
target_compile_options(common-lib PRIVATE
    -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion -Wno-unknown-pragmas -Wno-unused-const-variable
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
target_compile_options(common-lib PRIVATE
    #
    # /Zc:preprocessor is needed for handling __VA_OPT__(,)
    #
    # /wd4068 disables "unknown pragma" warnings
    #
    /Zc:preprocessor /WX /W4 /wd4068
)
else()
message(FATAL_ERROR "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

set_target_properties(common-lib
    PROPERTIES
        OUTPUT_NAME common
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE ON
)
















