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

//
// do this:
//
// #include "common/memory_utils.inl"
//
// to include this file
//
// no other headers will be included here
//

namespace {

//
// calls memcpy after checking that src span is large enough
//
template<typename T>
Status memcpy_from_span(void *dst, std::span<const T> src, size_t count) {

    if (src.size() < count) {
        LOGE("memcpy_from_span: count is larger than src: count: %zu span: %zu", count, src.size());
        return Status::ERR;
    }

    std::memcpy(dst, src.data(), count * sizeof(T));

    return Status::OK;
}


//
// calls memcpy after checking that dst span is large enough
//
template<typename T>
Status memcpy_to_span(std::span <T> dst, const void *src, size_t count) {

    if (dst.size() < count) {
        LOGE("memcpy_to_span: count is larger than dst: count: %zu span: %zu", count, dst.size());
        return Status::ERR;
    }

    std::memcpy(dst.data(), src, count * sizeof(T));

    return Status::OK;
}


//
// calls memcpy after checking that dst span is large enough and src span is large enough
//
template<typename T>
Status memcpy_spans(std::span <T> dst, std::span<const T> src, size_t count) {

    if (dst.size() < count) {
        LOGE("memcpy_spans: count is larger than dst: count: %zu span: %zu", count, dst.size());
        return Status::ERR;
    }

    if (src.size() < count) {
        LOGE("memcpy_spans: count is larger than src: count: %zu span: %zu", count, src.size());
        return Status::ERR;
    }

    std::memcpy(dst.data(), src.data(), count * sizeof(T));

    return Status::OK;
}

} // namespace
















