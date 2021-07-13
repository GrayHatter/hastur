load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Bazel
# =========================================================

http_archive(
    name = "platforms",  # Apache-2.0
    sha256 = "460caee0fa583b908c622913334ec3c1b842572b9c23cf0d3da0c2543a1a157d",
    url = "https://github.com/bazelbuild/platforms/releases/download/0.0.3/platforms-0.0.3.tar.gz",
)

# Third-party
# =========================================================

http_archive(
    name = "asio",  # BSL-1.0
    build_file = "//third_party:asio.BUILD",
    sha256 = "4af9875df5497fdd507231f4b7346e17d96fc06fe10fd30e2b3750715a329113",
    strip_prefix = "asio-1.18.1",
    urls = ["https://downloads.sourceforge.net/project/asio/asio/1.18.1%20(Stable)/asio-1.18.1.tar.bz2"],
)

http_archive(
    name = "boringssl",  # OpenSSL + ISC
    sha256 = "af0e0b561629029332d832fd4a2f2fbed14206eb2f538037a746d82e5281ace8",
    strip_prefix = "boringssl-b92ed690b31bc2df9197dca73b38aaa1a9225a40",
    urls = ["https://github.com/google/boringssl/archive/b92ed690b31bc2df9197dca73b38aaa1a9225a40.tar.gz"],
)

http_archive(
    name = "fmt",  # MIT
    build_file = "//third_party:fmt.BUILD",
    sha256 = "5cae7072042b3043e12d53d50ef404bbb76949dad1de368d7f993a15c8c05ecc",
    strip_prefix = "fmt-7.1.3",
    url = "https://github.com/fmtlib/fmt/archive/7.1.3.tar.gz",
)

http_archive(
    name = "freetype2",  # FTL
    build_file = "//third_party:freetype2.BUILD",
    sha256 = "33a28fabac471891d0523033e99c0005b95e5618dc8ffa7fa47f9dadcacb1c9b",
    strip_prefix = "freetype-2.8",
    urls = [
        "https://mirror.bazel.build/download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz",
        "http://download.savannah.gnu.org/releases/freetype/freetype-2.8.tar.gz",
    ],
)

http_archive(
    name = "ftxui",  # MIT
    build_file = "//third_party:ftxui.BUILD",
    sha256 = "dbf94ebc683e7e68d60fc3a30629b72207b0de3b875f31935bd3c941b427d917",
    strip_prefix = "FTXUI-84debba10cec8e077fd890cf5f61a45af3e3b6d4",
    urls = ["https://github.com/ArthurSonzogni/FTXUI/archive/84debba10cec8e077fd890cf5f61a45af3e3b6d4.tar.gz"],
)

http_archive(
    name = "imgui",  # MIT
    build_file = "//third_party:imgui.BUILD",
    sha256 = "f7c619e03a06c0f25e8f47262dbc32d61fd033d2c91796812bf0f8c94fca78fb",
    strip_prefix = "imgui-1.81",
    url = "https://github.com/ocornut/imgui/archive/v1.81.tar.gz",
)

http_archive(
    name = "imgui-sfml",  # MIT
    build_file = "//third_party:imgui-sfml.BUILD",
    sha256 = "843536a6c558579ab57f749c4c6e1e67e0f7b033ab434e0f9cf1ad38726ac51e",
    strip_prefix = "imgui-sfml-2.2",
    url = "https://github.com/eliasdaler/imgui-sfml/archive/v2.2.tar.gz",
)

http_archive(
    name = "libpng",  # Libpng
    build_file = "//third_party:libpng.BUILD",
    sha256 = "ca74a0dace179a8422187671aee97dd3892b53e168627145271cad5b5ac81307",
    strip_prefix = "libpng-1.6.37",
    url = "https://github.com/glennrp/libpng/archive/v1.6.37.tar.gz",
)

http_archive(
    name = "sfml",  # Zlib
    build_file = "//third_party:sfml.BUILD",
    sha256 = "6124b5fe3d96e7f681f587e2d5b456cd0ec460393dfe46691f1933d6bde0640b",
    strip_prefix = "SFML-2.5.1",
    url = "https://github.com/SFML/SFML/archive/2.5.1.zip",
)

http_archive(
    name = "spdlog",  # MIT
    build_file = "//third_party:spdlog.BUILD",
    sha256 = "e20e6bd8f57e866eaf25a5417f0a38a116e537f1a77ac7b5409ca2b180cec0d5",
    strip_prefix = "spdlog-1.8.2",
    urls = ["https://github.com/gabime/spdlog/archive/v1.8.2.tar.gz"],
)

http_archive(
    name = "stb",  # MIT/Unlicense
    build_file = "//third_party:stb.BUILD",
    sha256 = "13a99ad430e930907f5611325ec384168a958bf7610e63e60e2fd8e7b7379610",
    strip_prefix = "stb-b42009b3b9d4ca35bc703f5310eedc74f584be58",
    url = "https://github.com/nothings/stb/archive/b42009b3b9d4ca35bc703f5310eedc74f584be58.tar.gz",
)

http_archive(
    name = "udev-zero",  # ISC
    build_file = "//third_party:udev-zero.BUILD",
    sha256 = "23f1046f13403ec217665193e78dad6cdb0af54e105a9aaf8440a846e66a1d62",
    strip_prefix = "libudev-zero-0.5.2",
    url = "https://github.com/illiliti/libudev-zero/archive/0.5.2.tar.gz",
)

http_archive(
    name = "zlib",  # Zlib
    build_file = "//third_party:zlib.BUILD",
    sha256 = "629380c90a77b964d896ed37163f5c3a34f6e6d897311f1df2a7016355c45eff",
    strip_prefix = "zlib-1.2.11",
    url = "https://github.com/madler/zlib/archive/v1.2.11.tar.gz",
)
