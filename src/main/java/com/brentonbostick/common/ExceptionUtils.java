// Copyright (C) 2026 by Brenton Bostick
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

import androidx.annotation.Keep;

@Keep
public class ExceptionUtils {

    public static String toNiceString(Throwable t) {

        String msg = "";

        String title = t.getClass().getName();

        msg += title;

        String message = t.getMessage();

        if (message != null) {
            msg += "\n" + message;
        }

        Throwable cause = t.getCause();

        if (cause != null) {

            msg += "\nCause:\n";

            String title2 = cause.getClass().getName();

            msg += title2;

            String message2 = cause.getMessage();

            if (message2 != null) {
                msg += "\n" + message2;
            }
        }

        return msg;
    }
}
















