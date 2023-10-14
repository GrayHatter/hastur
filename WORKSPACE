load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Bazel
# =========================================================

http_archive(
    name = "platforms",  # Apache-2.0
    sha256 = "3a561c99e7bdbe9173aa653fd579fe849f1d8d67395780ab4770b1f381431d51",
    url = "https://github.com/bazelbuild/platforms/releases/download/0.0.7/platforms-0.0.7.tar.gz",
)

# https://github.com/bazelbuild/rules_fuzzing
http_archive(
    name = "rules_fuzzing",
    sha256 = "61e246849f77571f79a2bd6899b81636aac68334386a86ff925769f14ee203a5",
    strip_prefix = "rules_fuzzing-0.4.0",
    url = "https://github.com/bazelbuild/rules_fuzzing/archive/v0.4.0.tar.gz",
)

# https://github.com/bazelbuild/rules_python
http_archive(
    name = "rules_python",  # Apache-2.0
    sha256 = "5868e73107a8e85d8f323806e60cad7283f34b32163ea6ff1020cf27abef6036",
    strip_prefix = "rules_python-0.25.0",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.25.0/rules_python-0.25.0.tar.gz",
)

# Third-party Bazel
# =========================================================

# https://github.com/uber/hermetic_cc_toolchain
http_archive(
    name = "hermetic_cc_toolchain",
    sha256 = "28fc71b9b3191c312ee83faa1dc65b38eb70c3a57740368f7e7c7a49bedf3106",
    url = "https://github.com/uber/hermetic_cc_toolchain/releases/download/v2.1.2/hermetic_cc_toolchain-v2.1.2.tar.gz",
)

# Misc tools
# =========================================================

# HEAD as of 2022-12-17.
http_archive(
    name = "hedron_compile_commands",
    sha256 = "9b5683e6e0d764585f41639076f0be421a4c495c8f993c186e4449977ce03e5e",
    strip_prefix = "bazel-compile-commands-extractor-c6cd079bef5836293ca18e55aac6ef05134c3a9d",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/c6cd079bef5836293ca18e55aac6ef05134c3a9d.tar.gz",
)

# HEAD as of 2023-07-16.
http_archive(
    name = "bazel_clang_tidy",
    # Hack to have every .h-header treated as C++.
    patch_cmds = ["""sed -i '47i \\    args.add("-xc++")' clang_tidy/clang_tidy.bzl"""],
    sha256 = "e2721c47f4215ac36ad1da55ebdb968a094125dbc397aa7733f067001600b2ee",
    strip_prefix = "bazel_clang_tidy-133d89a6069ce253a92d32a93fdb7db9ef100e9d",
    url = "https://github.com/erenon/bazel_clang_tidy/archive/133d89a6069ce253a92d32a93fdb7db9ef100e9d.tar.gz",
)

# Third-party
# =========================================================

# We don't use this, but rules_fuzzing does, and the version they depend on
# doesn't work with Clang 16 due to undeclared inclusions.
http_archive(
    name = "com_google_absl",  # Apache-2.0
    sha256 = "987ce98f02eefbaf930d6e38ab16aa05737234d7afbab2d5c4ea7adbe50c28ed",
    strip_prefix = "abseil-cpp-20230802.1",
    url = "https://github.com/abseil/abseil-cpp/archive/20230802.1.tar.gz",
)

http_archive(
    name = "asio",  # BSL-1.0
    build_file = "//third_party:asio.BUILD",
    sha256 = "5ff6111ec8cbe73a168d997c547f562713aa7bd004c5c02326f0e9d579a5f2ce",
    strip_prefix = "asio-asio-1-28-1",
    url = "https://github.com/chriskohlhoff/asio/archive/asio-1-28-1.tar.gz",
)

# https://github.com/google/boringssl
# boringssl//:ssl cheats and pulls in private includes from boringssl//:crypto.
http_archive(
    name = "boringssl",  # OpenSSL + ISC
    patch_cmds = ["""sed -i '33i package(features=["-layering_check"])' BUILD"""],
    sha256 = "e3f0fc8856e5469a3398ade487b8a119a31bd858eb492fa150e4bb95815e49c7",
    strip_prefix = "boringssl-99f652dbeda9640e70fb7e1a8f70c27103c621b7",
    url = "https://github.com/google/boringssl/archive/99f652dbeda9640e70fb7e1a8f70c27103c621b7.tar.gz",
)

http_archive(
    name = "expected",  # CC0-1.0
    build_file = "//third_party:expected.BUILD",
    sha256 = "1db357f46dd2b24447156aaf970c4c40a793ef12a8a9c2ad9e096d9801368df6",
    strip_prefix = "expected-1.1.0",
    url = "https://github.com/tartanllama/expected/archive/v1.1.0.tar.gz",
)

# https://github.com/fmtlib/fmt
http_archive(
    name = "fmt",  # MIT
    build_file = "//third_party:fmt.BUILD",
    sha256 = "78b8c0a72b1c35e4443a7e308df52498252d1cefc2b08c9a97bc9ee6cfe61f8b",
    strip_prefix = "fmt-10.1.1",
    url = "https://github.com/fmtlib/fmt/archive/10.1.1.tar.gz",
)

# https://github.com/freetype/freetype
http_archive(
    name = "freetype2",  # FTL
    build_file = "//third_party:freetype2.BUILD",
    sha256 = "427201f5d5151670d05c1f5b45bef5dda1f2e7dd971ef54f0feaaa7ffd2ab90c",
    strip_prefix = "freetype-VER-2-13-2",
    url = "https://github.com/freetype/freetype/archive/VER-2-13-2.tar.gz",
)

# https://github.com/ArthurSonzogni/FTXUI
http_archive(
    name = "ftxui",  # MIT
    build_file = "//third_party:ftxui.BUILD",
    sha256 = "a2991cb222c944aee14397965d9f6b050245da849d8c5da7c72d112de2786b5b",
    strip_prefix = "FTXUI-5.0.0",
    url = "https://github.com/ArthurSonzogni/FTXUI/archive/v5.0.0.tar.gz",
)

# https://github.com/Dav1dde/glad/
local_repository(
    name = "glad",  # MIT
    path = "third_party/glad",
)

# https://github.com/unicode-org/icu
http_archive(
    name = "icu",  # Unicode-DFS-2016
    build_file = "//third_party:icu.BUILD",
    patch_cmds = [
        "rm source/common/BUILD.bazel",
        "rm source/stubdata/BUILD.bazel",
    ],
    sha256 = "818a80712ed3caacd9b652305e01afc7fa167e6f2e94996da44b90c2ab604ce1",
    strip_prefix = "icu",
    url = "https://github.com/unicode-org/icu/releases/download/release-73-2/icu4c-73_2-src.tgz",
)

# https://github.com/unicode-org/icu
http_archive(
    name = "icu-data",  # Unicode-DFS-2016
    build_file_content = """exports_files(["icudt73l.dat"])""",
    sha256 = "2657bd18c23b930ddf63f466192832cc083256515e07b5a5e7d79c5c1db058a1",
    url = "https://github.com/unicode-org/icu/releases/download/release-73-2/icu4c-73_2-data-bin-l.zip",
)

# https://github.com/ocornut/imgui
http_archive(
    name = "imgui",  # MIT
    build_file = "//third_party:imgui.BUILD",
    sha256 = "1acc27a778b71d859878121a3f7b287cd81c29d720893d2b2bf74455bf9d52d6",
    strip_prefix = "imgui-1.89.9",
    url = "https://github.com/ocornut/imgui/archive/v1.89.9.tar.gz",
)

# https://github.com/SFML/imgui-sfml
http_archive(
    name = "imgui-sfml",  # MIT
    build_file = "//third_party:imgui-sfml.BUILD",
    sha256 = "b1195ca1210dd46c8049cfc8cae7f31cd34f1591da7de1c56297b277ac9c5cc0",
    strip_prefix = "imgui-sfml-2.6",
    url = "https://github.com/eliasdaler/imgui-sfml/archive/v2.6.tar.gz",
)

# https://github.com/simdjson/simdjson
http_archive(
    name = "simdjson",  # Apache-2.0
    build_file = "//third_party:simdjson.BUILD",
    sha256 = "a8c9feff2f19c3ff281d42f0b6b4b18f02236513b99229756fa9a1b14787a58a",
    strip_prefix = "simdjson-3.3.0",
    url = "https://github.com/simdjson/simdjson/archive/refs/tags/v3.3.0.tar.gz",
)

# https://github.com/glennrp/libpng
http_archive(
    name = "libpng",  # Libpng
    build_file = "//third_party:libpng.BUILD",
    sha256 = "62d25af25e636454b005c93cae51ddcd5383c40fa14aa3dae8f6576feb5692c2",
    strip_prefix = "libpng-1.6.40",
    url = "https://github.com/glennrp/libpng/archive/v1.6.40.tar.gz",
)

http_archive(
    name = "sfml",  # Zlib
    build_file = "//third_party:sfml.BUILD",
    # Work around SFML check for enough bytes for a given UTF-8 character crashing
    # in MSVC debug builds with "cannot seek string_view iterator after end".
    # See: https://github.com/SFML/SFML/issues/2113
    patch_cmds = [
        "sed -i 's/if (begin + trailingBytes < end)/if (trailingBytes < std::distance(begin, end))/' include/SFML/System/Utf.inl",
    ],
    sha256 = "6124b5fe3d96e7f681f587e2d5b456cd0ec460393dfe46691f1933d6bde0640b",
    strip_prefix = "SFML-2.5.1",
    url = "https://github.com/SFML/SFML/archive/2.5.1.zip",
)

# https://github.com/gabime/spdlog
http_archive(
    name = "spdlog",  # MIT
    build_file = "//third_party:spdlog.BUILD",
    sha256 = "4dccf2d10f410c1e2feaff89966bfc49a1abb29ef6f08246335b110e001e09a9",
    strip_prefix = "spdlog-1.12.0",
    url = "https://github.com/gabime/spdlog/archive/v1.12.0.tar.gz",
)

http_archive(
    name = "stb",  # MIT/Unlicense
    build_file = "//third_party:stb.BUILD",
    sha256 = "d00921d49b06af62aa6bfb97c1b136bec661dd11dd4eecbcb0da1f6da7cedb4c",
    strip_prefix = "stb-5736b15f7ea0ffb08dd38af21067c314d6a3aae9",
    url = "https://github.com/nothings/stb/archive/5736b15f7ea0ffb08dd38af21067c314d6a3aae9.tar.gz",
)

# https://github.com/illiliti/libudev-zero
http_archive(
    name = "udev-zero",  # ISC
    build_file = "//third_party:udev-zero.BUILD",
    sha256 = "0bd89b657d62d019598e6c7ed726ff8fed80e8ba092a83b484d66afb80b77da5",
    strip_prefix = "libudev-zero-1.0.3",
    url = "https://github.com/illiliti/libudev-zero/archive/1.0.3.tar.gz",
)

# https://github.com/facebookexperimental/libunifex
http_archive(
    name = "unifex",  # Apache-2.0 WITH LLVM-exception
    build_file = "//third_party:unifex.BUILD",
    sha256 = "da6b65227adcf1ce3e3410865cc2974b1aacaa20d0f03905bd3bd4fb4e6e4d44",
    strip_prefix = "libunifex-0.3.0",
    url = "https://github.com/facebookexperimental/libunifex/archive/v0.3.0.tar.gz",
)

VULKAN_TAG = "1.3.267"

# https://github.com/KhronosGroup/Vulkan-Headers
http_archive(
    name = "vulkan",  # Apache-2.0
    build_file = "//third_party:vulkan.BUILD",
    sha256 = "72120553215bb631275a38a5359ad812837165ab8ddd8e33597dd52c7d80d627",
    strip_prefix = "Vulkan-Headers-%s" % VULKAN_TAG,
    url = "https://github.com/KhronosGroup/Vulkan-Headers/archive/v%s.tar.gz" % VULKAN_TAG,
)

# https://github.com/KhronosGroup/Vulkan-Hpp
http_archive(
    name = "vulkan_hpp",  # Apache-2.0
    build_file = "//third_party:vulkan_hpp.BUILD",
    sha256 = "c763d8a7af8e30c40a087c00b58cb6ab4853ab47a60a1a5f3ab658d0c269ff10",
    strip_prefix = "Vulkan-Hpp-%s" % VULKAN_TAG,
    url = "https://github.com/KhronosGroup/Vulkan-Hpp/archive/v%s.tar.gz" % VULKAN_TAG,
)

# https://github.com/web-platform-tests/wpt
http_archive(
    name = "wpt",  # BSD-3-Clause
    build_file_content = """exports_files(["url/resources/urltestdata.json"])""",
    sha256 = "a841acfb7560ec262d7781ab639bc71539b0d00eb38230aeb119f837d2072115",
    strip_prefix = "wpt-merge_pr_42460",
    url = "https://github.com/web-platform-tests/wpt/archive/refs/tags/merge_pr_42460.tar.gz",
)

# The freedesktop GitLab goes down too often to be trusted.
http_archive(
    name = "xext",  # MIT
    build_file = "//third_party:xext.BUILD",
    sha256 = "dcf5fd6defbe474912fb6c617f8b926e53f828698c8491a8abab955ab071fc3f",
    strip_prefix = "libxext-libXext-1.3.5",
    urls = [
        "https://gitlab.freedesktop.org/xorg/lib/libxext/-/archive/libXext-1.3.5/libxext-libXext-1.3.5.tar.gz",
        "https://github.com/gitlab-freedesktop-mirrors/libxext/archive/refs/tags/libXext-1.3.5.tar.gz",
    ],
)

# https://gitlab.freedesktop.org/xorg/lib/libxrandr
http_archive(
    name = "xrandr",  # MIT
    build_file = "//third_party:xrandr.BUILD",
    sha256 = "a1909cbe9ded94187b6420ae8c347153f8278955265cb80a64cdae5501433396",
    strip_prefix = "libxrandr-libXrandr-1.5.4",
    urls = [
        "https://gitlab.freedesktop.org/xorg/lib/libxrandr/-/archive/libXrandr-1.5.4/libxrandr-libXrandr-1.5.4.tar.gz",
        "https://github.com/gitlab-freedesktop-mirrors/libxrandr/archive/libXrandr-1.5.4.tar.gz",
    ],
)

http_archive(
    name = "xrender",  # MIT
    build_file = "//third_party:xrender.BUILD",
    sha256 = "4cd5aca5b948a80bb7c3d5060eb97b8a8199234c0c19fe34d35c5c838923230b",
    strip_prefix = "libxrender-libXrender-0.9.11",
    urls = [
        "https://gitlab.freedesktop.org/xorg/lib/libxrender/-/archive/libXrender-0.9.11/libxrender-libXrender-0.9.11.tar.gz",
        "https://github.com/gitlab-freedesktop-mirrors/libxrender/archive/refs/tags/libXrender-0.9.11.tar.gz",
    ],
)

http_archive(
    name = "zlib",  # Zlib
    build_file = "//third_party:zlib.BUILD",
    sha256 = "b5b06d60ce49c8ba700e0ba517fa07de80b5d4628a037f4be8ad16955be7a7c0",
    strip_prefix = "zlib-1.3",
    url = "https://github.com/madler/zlib/archive/v1.3.tar.gz",
)

# Third-party setup
# =========================================================

# This needs to go last so that we can override any dependencies these calls may
# pull in.

load("@rules_fuzzing//fuzzing:repositories.bzl", "rules_fuzzing_dependencies")

rules_fuzzing_dependencies()

load("@rules_fuzzing//fuzzing:init.bzl", "rules_fuzzing_init")

rules_fuzzing_init()

load("@fuzzing_py_deps//:requirements.bzl", fuzzing_py_deps_install_deps = "install_deps")

fuzzing_py_deps_install_deps()

load("@rules_python//python:repositories.bzl", "py_repositories", "python_register_toolchains")

py_repositories()

python_register_toolchains(
    name = "python_3_11",
    # Running the build as root works, but leads to cache-misses for .pyc files.
    ignore_root_user_error = True,
    python_version = "3.11.4",
)

load("@python_3_11//:defs.bzl", "interpreter")
load("@rules_python//python:pip.bzl", "pip_parse")

pip_parse(
    name = "pypi",
    python_interpreter_target = interpreter,
    requirements_lock = "//third_party:requirements.txt",
)

load("@pypi//:requirements.bzl", pypi_install_deps = "install_deps")

pypi_install_deps()

load("@hermetic_cc_toolchain//toolchain:defs.bzl", zig_toolchains = "toolchains")

zig_toolchains()

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()
