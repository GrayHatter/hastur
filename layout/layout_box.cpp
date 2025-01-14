// SPDX-FileCopyrightText: 2021-2023 Robin Lindén <dev@robinlinden.eu>
// SPDX-FileCopyrightText: 2022 Mikael Larsson <c.mikael.larsson@gmail.com>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "layout/layout_box.h"

#include "util/from_chars.h"

#include <spdlog/spdlog.h>

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include <sstream>
#include <string_view>
#include <utility>
#include <variant>

using namespace std::literals;

namespace layout {
namespace {

std::string_view to_str(LayoutType type) {
    switch (type) {
        case LayoutType::Inline:
            return "inline";
        case LayoutType::Block:
            return "block";
        case LayoutType::AnonymousBlock:
            return "ablock";
    }
    assert(false);
    std::abort();
}

std::string to_str(geom::Rect const &rect) {
    std::stringstream ss;
    ss << "{" << rect.x << "," << rect.y << "," << rect.width << "," << rect.height << "}";
    return std::move(ss).str();
}

std::string to_str(geom::EdgeSize const &edge) {
    std::stringstream ss;
    ss << "{" << edge.top << "," << edge.right << "," << edge.bottom << "," << edge.left << "}";
    return std::move(ss).str();
}

void print_box(LayoutBox const &box, std::ostream &os, std::uint8_t depth = 0) {
    for (std::uint8_t i = 0; i < depth; ++i) {
        os << "  ";
    }

    if (box.node != nullptr) {
        if (auto const *element = std::get_if<dom::Element>(&box.node->node)) {
            os << element->name << '\n';
        } else {
            os << box.text().value() << '\n';
        }

        for (std::uint8_t i = 0; i < depth; ++i) {
            os << "  ";
        }
    }

    auto const &d = box.dimensions;
    os << to_str(box.type) << " " << to_str(d.content) << " " << to_str(d.padding) << " " << to_str(d.margin) << '\n';
    for (auto const &child : box.children) {
        print_box(child, os, depth + 1);
    }
}

int get_root_font_size(style::StyledNode const &node) {
    auto const *n = &node;
    while (n->parent) {
        n = n->parent;
    }
    return n->get_property<css::PropertyId::FontSize>();
}

} // namespace

std::optional<std::string_view> LayoutBox::text() const {
    struct Visitor {
        std::optional<std::string_view> operator()(std::monostate) { return std::nullopt; }
        std::optional<std::string_view> operator()(std::string const &s) { return s; }
        std::optional<std::string_view> operator()(std::string_view const &s) { return s; }
    };
    return std::visit(Visitor{}, layout_text);
}

std::pair<int, int> LayoutBox::get_border_radius_property(css::PropertyId id) const {
    auto raw = node->get_raw_property(id);
    auto [horizontal, vertical] = raw.contains('/') ? util::split_once(raw, "/") : std::pair{raw, raw};

    int font_size = node->get_property<css::PropertyId::FontSize>();
    int root_font_size = get_root_font_size(*node);
    return {to_px(horizontal, font_size, root_font_size), to_px(vertical, font_size, root_font_size)};
}

std::optional<int> LayoutBox::get_min_width_property() const {
    auto raw = node->get_raw_property(css::PropertyId::MinWidth);
    if (raw == "auto") {
        return std::nullopt;
    }

    int font_size = node->get_property<css::PropertyId::FontSize>();
    int root_font_size = get_root_font_size(*node);
    return to_px(raw, font_size, root_font_size);
}

std::optional<int> LayoutBox::get_width_property() const {
    auto raw = node->get_raw_property(css::PropertyId::Width);
    if (raw == "auto") {
        return std::nullopt;
    }

    int font_size = node->get_property<css::PropertyId::FontSize>();
    int root_font_size = get_root_font_size(*node);
    return to_px(raw, font_size, root_font_size);
}

std::optional<int> LayoutBox::get_max_width_property() const {
    auto raw = node->get_raw_property(css::PropertyId::MaxWidth);
    if (raw == "none") {
        return std::nullopt;
    }

    int font_size = node->get_property<css::PropertyId::FontSize>();
    int root_font_size = get_root_font_size(*node);
    return to_px(raw, font_size, root_font_size);
}

LayoutBox const *box_at_position(LayoutBox const &box, geom::Position p) {
    if (!box.dimensions.contains(p)) {
        return nullptr;
    }

    for (auto const &child : box.children) {
        if (auto const *maybe = box_at_position(child, p)) {
            return maybe;
        }
    }

    if (box.type == LayoutType::AnonymousBlock) {
        return nullptr;
    }

    return &box;
}

std::string to_string(LayoutBox const &box) {
    std::stringstream ss;
    print_box(box, ss);
    return std::move(ss).str();
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
int to_px(std::string_view property, int const font_size, int const root_font_size) {
    // Special case for 0 since it won't ever have a unit that needs to be handled.
    if (property == "0") {
        return 0;
    }

    float res{};
    auto parse_result = util::from_chars(property.data(), property.data() + property.size(), res);
    if (parse_result.ec != std::errc{}) {
        spdlog::warn("Unable to parse property '{}' in to_px", property);
        return 0;
    }

    auto const parsed_length = std::distance(property.data(), parse_result.ptr);
    auto const unit = property.substr(parsed_length);

    if (unit == "px") {
        return static_cast<int>(res);
    }

    if (unit == "em") {
        res *= static_cast<float>(font_size);
        return static_cast<int>(res);
    }

    if (unit == "rem") {
        res *= static_cast<float>(root_font_size);
        return static_cast<int>(res);
    }

    spdlog::warn("Bad property '{}' w/ unit '{}' in to_px", property, unit);
    return static_cast<int>(res);
}

} // namespace layout
