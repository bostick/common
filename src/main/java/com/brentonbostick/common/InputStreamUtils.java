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

package com.brentonbostick.common;

import java.io.IOException;
import java.io.InputStream;

public class InputStreamUtils {

    /// Read all bytes from is into buf.
    ///
    /// Stop-gap until is.readAllBytes() can be used everywhere (added in TIRAMISU, API 33, Android 13)
    ///
    /// @return number of bytes read
    ///
    /// @throws IOException on error
    ///
    public static int readInputStreamIntoBuffer(InputStream is, byte[] buf) throws IOException {

        int read;
        int offset = 0;

        int len = buf.length;

        while (true) {

            read = is.read(buf, offset, len - offset);

            if (read == -1) {
                //
                // reached end of stream
                //
                break;
            }

            offset += read;

            if (offset > len) {
                throw new IOException("offset > len");
            }
        }

        return offset;
    }
}








