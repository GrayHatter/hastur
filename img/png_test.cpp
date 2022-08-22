// SPDX-FileCopyrightText: 2022 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "img/png.h"

#include "etest/etest.h"

#include <array>
#include <cstddef>
#include <sstream>
#include <utility>
#include <vector>

using etest::expect_eq;

namespace {
#include "img/tiny_png.h"
std::string const png_bytes(reinterpret_cast<char const *>(img_tiny_png), img_tiny_png_len);
} // namespace

int main() {
    etest::test("it works", [] {
        auto expected_pixels = [] {
            std::array<unsigned char, 3> pixel_pattern{181, 208, 208};
            std::vector<unsigned char> expected;
            expected.resize(256 * 256 * 3);

            for (std::size_t i = 0; i < expected.size(); ++i) {
                expected[i] = pixel_pattern[i % pixel_pattern.size()];
            }

            return expected;
        }();

        auto ss = std::stringstream(png_bytes);
        auto png = img::Png::from(ss).value();
        expect_eq(png, img::Png{.width = 256, .height = 256, .bytes = std::move(expected_pixels)});
    });

    etest::test("invalid signatures are rejected", [] {
        auto invalid_signature_bytes = png_bytes;
        invalid_signature_bytes[7] = 'b';
        auto ss = std::stringstream(std::move(invalid_signature_bytes));
        expect_eq(img::Png::from(ss), std::nullopt);
    });

    etest::test("it handles truncated files", [] {
        auto truncated_bytes = png_bytes.substr(0, 30);
        auto ss = std::stringstream(std::move(truncated_bytes));
        expect_eq(img::Png::from(ss), std::nullopt);
    });

    return etest::run_all_tests();
}