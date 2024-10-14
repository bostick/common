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

#include "common/clock.h"

#include "common/platform.h"

#if IS_PLATFORM_IOS
#import <Foundation/Foundation.h>
#elif IS_PLATFORM_MACOS
#import <mach/mach_time.h> // for mach_absolute_time
#else
#error
#endif // IS_PLATFORM_IOS

#if IS_PLATFORM_IOS

int64_t uptimeMillis() {

    NSTimeInterval systemUptime = [[NSProcessInfo processInfo] systemUptime];
    
    return static_cast<int64_t>(1000.0 * systemUptime);
}

#elif IS_PLATFORM_MACOS

int64_t uptimeMillis() {

   auto t = mach_absolute_time();

   static mach_timebase_info_data_t timebase;
   if (timebase.denom == 0) {
       static_cast<void>(mach_timebase_info(&timebase));
   }

   return static_cast<int64_t>(t * timebase.numer / timebase.denom / 1000000);
}

#else
#error
#endif // IS_PLATFORM_IOS















