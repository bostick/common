# Copyright (C) 2026 by Brenton Bostick
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

include(FetchContent)


FetchContent_Declare(googletest
    # GIT_REPOSITORY
    #     https://github.com/google/googletest.git
    # GIT_TAG
    #     v1.17.0
    # GIT_SHALLOW 1
    # GIT_PROGRESS 1
    SOURCE_DIR
        /Users/brenton/development/github/googletest
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


set(CPP_TEST_SOURCES
    TestClock.cpp
    TestMathUtils.cpp
    TestStringUtils.cpp
)

add_executable(common-test-exe
    ${CPP_TEST_SOURCES}
)

target_link_libraries(common-test-exe
    PRIVATE
        GTest::gmock_main
        common-lib
)


gtest_discover_tests(common-test-exe)


#
# Set up warnings
#
# https://www.foonathan.net/2018/10/cmake-warnings/
#
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
target_compile_options(common-test-exe
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
target_compile_options(common-test-exe
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
target_compile_options(common-test-exe
    PRIVATE
        -Wall -Wextra -pedantic -Werror -Wconversion -Wsign-conversion
)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
target_compile_options(common-test-exe
    PRIVATE
        #
        # /Zc:preprocessor is needed for handling __VA_OPT__(,)
        #
        /Zc:preprocessor /WX /W4
)
else()
message(FATAL_ERROR "Unrecognized compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

set_target_properties(common-test-exe
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS NO
)


if(SANITIZE)
    if(${SANITIZE} STREQUAL "ubsan")
        target_compile_options(common-test-exe
            PRIVATE
                -fsanitize=undefined -fno-sanitize-recover=undefined
        )
        target_link_options(common-test-exe
            PRIVATE
                -fsanitize=undefined -fno-sanitize-recover=undefined
        )
    elseif(${SANITIZE} STREQUAL "asan")
        target_compile_options(common-test-exe
            PRIVATE
                -fsanitize=address -fno-omit-frame-pointer
        )
        target_link_options(common-test-exe
            PRIVATE
                -fsanitize=address -fno-omit-frame-pointer
        )
    endif()
endif()
















