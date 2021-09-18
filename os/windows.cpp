// SPDX-FileCopyrightText: 2021 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "os/os.h"

// Must be included first because Windows headers don't include what they use.
#include <Windows.h>

#include <Knownfolders.h>
#include <Objbase.h>
#include <Shlobj.h>

#include <cwchar>

namespace os {

std::vector<std::string> font_paths() {
    PWSTR bad_font_path{nullptr};
    SHGetKnownFolderPath(FOLDERID_Fonts, 0, NULL, &bad_font_path);
    auto bad_font_path_len = static_cast<int>(std::wcslen(bad_font_path));
    auto chars_needed = WideCharToMultiByte(CP_UTF8, 0, bad_font_path, bad_font_path_len, nullptr, 0, NULL, NULL);
    std::string font_path;
    font_path.resize(chars_needed);
    WideCharToMultiByte(CP_UTF8, 0, bad_font_path, bad_font_path_len, font_path.data(), chars_needed, NULL, NULL);
    CoTaskMemFree(bad_font_path);
    return {font_path};
}

} // namespace os