// SPDX-FileCopyrightText: 2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "archive/zlib.h"

#include "etest/etest.h"

#include <string_view>

using namespace archive;
using namespace etest;
using namespace std::literals;

namespace {

constexpr auto expected = "p { font-size: 123em; }\n"sv;

// p { font-size: 123em; }, gzipped.
constexpr auto gzipped_css =
        "\x1f\x8b\x08\x00\x00\x00\x00\x00\x00\x03\x2b\x50\xa8\x56\x48\xcb\xcf\x2b\xd1\x2d\xce\xac\x4a\xb5\x52\x30\x34\x32\x4e\xcd\xb5\x56\xa8\xe5\x02\x00\x0c\x97\x72\x35\x18\x00\x00\x00"sv;

// p { font-size: 123em; }, zlibbed.
constexpr auto zlibbed_css =
        "\x78\x5e\x2b\x50\xa8\x56\x48\xcb\xcf\x2b\xd1\x2d\xce\xac\x4a\xb5\x52\x30\x34\x32\x4e\xcd\xb5\x56\xa8\xe5\x02\x00\x63\xc3\x07\x6f"sv;

} // namespace

int main() {
    etest::test("zlib", [] {
        expect_eq(zlib_decode(zlibbed_css, ZlibMode::Zlib), expected);
        expect(!zlib_decode(gzipped_css, ZlibMode::Zlib).has_value());
    });

    etest::test("gzip", [] {
        expect(!zlib_decode(zlibbed_css, ZlibMode::Gzip), std::nullopt);
        expect_eq(zlib_decode(gzipped_css, ZlibMode::Gzip), expected);
    });

    etest::test("zlib and gzip", [] {
        expect_eq(zlib_decode(zlibbed_css, ZlibMode::GzipAndZlib), expected);
        expect_eq(zlib_decode(gzipped_css, ZlibMode::GzipAndZlib), expected);
    });

    return etest::run_all_tests();
}