
include(FetchContent)


FetchContent_Declare(googletest
    GIT_REPOSITORY
        https://github.com/google/googletest.git
    GIT_TAG
        v1.15.2
    GIT_SHALLOW 1
    GIT_PROGRESS 1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


set(CPP_TEST_SOURCES
    TestClock.cpp
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
















