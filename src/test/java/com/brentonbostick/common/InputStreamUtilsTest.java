package com.brentonbostick.common;

import static com.google.common.truth.Truth.assertThat;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

@RunWith(JUnit4.class)
public class InputStreamUtilsTest {

    public InputStreamUtilsTest() {
    }

    @Test
    public void testLongToBytes() {

        InputStream is = new ByteArrayInputStream("123".getBytes(StandardCharsets.UTF_8));

        byte[] buf = new byte[3];

        try {

            int read = InputStreamUtils.readInputStreamIntoBuffer(is, buf);

            assertThat(read).isEqualTo(3);

            assertThat(buf).isEqualTo(new byte[]{ '1', '2', '3' });

        } catch (IOException e) {
            assertThat(true).isFalse();
        }
    }
}
