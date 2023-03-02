// SPDX-FileCopyrightText: 2021 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef ETEST_CXX_COMPAT_H_
#define ETEST_CXX_COMPAT_H_

// Clang has the header, but it doesn't yet contain std::source_location.
#if __has_include(<source_location>) && !defined(__clang__)

#include <source_location>
namespace etest {
using source_location = std::source_location;
} // namespace etest

#else

#include <cstdint>
namespace etest {
// https://en.cppreference.com/w/cpp/utility/source_location
// NOLINTNEXTLINE(readability-identifier-naming)
struct source_location {
    static constexpr source_location current() noexcept { return source_location{}; }
    constexpr std::uint_least32_t line() const noexcept { return 0; }
    constexpr std::uint_least32_t column() const noexcept { return 0; }
    constexpr char const *file_name() const noexcept { return ""; }
    constexpr char const *function_name() const noexcept { return ""; }
};
} // namespace etest

#endif

#endif
