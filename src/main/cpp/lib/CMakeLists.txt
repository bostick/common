# Copyright (C) 2025 by Brenton Bostick
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
    error.cpp
    file.cpp
    logging.cpp
    math_utils.cpp
    string_utils.cpp
    unusual_message.cpp
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Android")

list(APPEND SOURCES_LIB
    common_jnicache.cpp
    common_jniutils.cpp
    opengl_utils.cpp
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
# 
# 
target_link_options(common-lib
    PRIVATE
        -u Java_com_brentonbostick_common_Clock_timeSinceEpochMillisNative
)


#
# Set up warnings
#
# https://www.foonathan.net/2018/10/cmake-warnings/
#
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
target_compile_options(common-lib
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
target_compile_options(common-lib
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
target_compile_options(common-lib
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
target_compile_options(common-lib
    PRIVATE
        #
        # /Zc:preprocessor is needed for handling __VA_OPT__(,)
        #
        /Zc:preprocessor /WX /W4
)
else()
message(FATAL_ERROR "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

set_target_properties(common-lib
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO
        POSITION_INDEPENDENT_CODE ON
        C_STANDARD 23
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS NO
)


if(SANITIZE)
    if(${SANITIZE} STREQUAL "ubsan")
        target_compile_options(common-lib
            PRIVATE
                -fsanitize=undefined -fno-sanitize-recover=undefined
        )
        target_link_options(common-lib
            PRIVATE
                -fsanitize=undefined -fno-sanitize-recover=undefined
        )
    elseif(${SANITIZE} STREQUAL "asan")
        target_compile_options(common-lib
            PRIVATE
                -fsanitize=address -fno-omit-frame-pointer
        )
        target_link_options(common-lib
            PRIVATE
                -fsanitize=address -fno-omit-frame-pointer
        )
    endif()
endif()
















