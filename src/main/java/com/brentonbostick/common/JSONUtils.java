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

import static com.brentonbostick.common.Status.ERR;
import static com.brentonbostick.common.Status.OK;
import static java.nio.charset.StandardCharsets.US_ASCII;
import static java.util.Locale.US;

import android.util.Log;

import androidx.annotation.Nullable;
import androidx.annotation.NonNull;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class JSONUtils {

    private static final String TAG = "JSONUtils";

    @Nullable
    public static JSONObject readInputStream(@NonNull InputStream is) {

        String s;
        try {

            byte[] buf = InputStreamUtils.readInputStream(is);

            s = new String(buf, US_ASCII);

        } catch (IOException e) {

            Log.e(TAG, e.getMessage(), e);

            return null;
        }

        try {

            return new JSONObject(s);

        } catch (JSONException e) {

            String msg = String.format(US,
                    "parsing JSON object failed. input length: %d input: \n%s", s.length(), s);

            Log.e(TAG, msg);
            UnusualMessage.captureUnusualMessage(msg);

            return null;
        }
    }

    public static boolean parseable(@NonNull InputStream is) {

        try {

            byte[] buf = InputStreamUtils.readInputStream(is);

            String s = new String(buf, US_ASCII);

            new JSONObject(s);

            return true;

        } catch (JSONException | IOException e) {

            return false;
        }
    }

    @NonNull
    public static Status writeOutputStream(@NonNull JSONObject j, @NonNull OutputStream os) {

        String s = j.toString();

        byte[] buf = s.getBytes(US_ASCII);

        try {

            os.write(buf);

            return OK;

        } catch (IOException e) {

            Log.e(TAG, e.getMessage(), e);

            return ERR;
        }
    }
}
















