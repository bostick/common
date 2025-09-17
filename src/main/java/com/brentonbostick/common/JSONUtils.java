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

import static java.nio.charset.StandardCharsets.US_ASCII;

import androidx.annotation.Keep;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

@Keep
public class JSONUtils {

    private static final String TAG = "JSONUtils";

    public static JSONObject readInputStream(InputStream is) throws IOException, JSONException {

        byte[] buf = InputStreamUtils.readInputStream(is);

        String s = new String(buf, US_ASCII);

        return new JSONObject(s);
    }

    public static void writeOutputStream(JSONObject j, OutputStream os) throws IOException {

        String s = j.toString();

        byte[] buf = s.getBytes(US_ASCII);

        os.write(buf);
    }
}
















