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

package com.brentonbostick.common;

import static android.os.Build.VERSION.SDK_INT;
import static android.os.Build.VERSION_CODES.TIRAMISU;

import android.os.Build;

import java.io.IOException;
import java.io.InputStream;

public class InputStreamUtils {

    /// Read all bytes from is into a new array of bytes.
    ///
    /// Stop-gap until is.readAllBytes() can be used everywhere (added in TIRAMISU, API 33, Android 13)
    ///
    /// @return array of all bytes from is
    ///
    /// @throws IOException on error
    ///
    public static byte[] readInputStream(InputStream is) throws IOException {

        //
        // read all bytes from is
        //
        if (SDK_INT >= TIRAMISU) { // TIRAMISU, API 33, Android 13 and higher

            return is.readAllBytes();

        } else { // S_V2, API 32, Android 12 and lower

            byte[] buf = new byte[5000];

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

            byte[] buf2 = new byte[offset];

            System.arraycopy(buf, 0, buf2, 0, offset);

            return buf2;
        }
    }
}
















