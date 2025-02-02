// SPDX-FileCopyrightText: 2021-2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "style/styled_node.h"

#include "etest/etest.h"

#include <string>
#include <tuple>
#include <utility>

using namespace std::literals;
using etest::expect;
using etest::expect_eq;

namespace {
template<css::PropertyId IdT>
void expect_property_eq(
        std::string value, auto expected, etest::source_location const &loc = etest::source_location::current()) {
    dom::Node dom_node = dom::Element{"dummy"s};
    style::StyledNode styled_node{
            .node = dom_node,
            .properties = {{IdT, std::move(value)}},
            .children = {},
    };

    etest::expect_eq(styled_node.get_property<IdT>(), expected, std::nullopt, loc);
};
} // namespace

int main() {
    etest::test("get_property", [] { expect_property_eq<css::PropertyId::Width>("15px", "15px"); });

    etest::test("property inheritance", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::FontSize, "15px"s}, {css::PropertyId::Width, "0px"s}},
                .children = {},
        };

        auto &child = root.children.emplace_back(style::StyledNode{dom_node, {}, {}, &root});

        // Not inherited, returns the initial value.
        expect_eq(child.get_property<css::PropertyId::Width>(), "auto"sv);

        // Inherited, returns the parent's value.
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 15);
    });

    etest::test("initial css keyword", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::Color, "blue"s}},
                .children{
                        style::StyledNode{
                                .node{dom_node},
                                .properties{{css::PropertyId::Color, "initial"s}},
                        },
                },
        };

        auto &child = root.children[0];
        child.parent = &root;

        expect_eq(child.get_property<css::PropertyId::Color>(), gfx::Color::from_css_name("canvastext"));
    });

    etest::test("inherit css keyword", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::BackgroundColor, "blue"s}},
                .children{
                        style::StyledNode{
                                .node{dom_node},
                                .properties{
                                        {css::PropertyId::BackgroundColor, "inherit"s},
                                        {css::PropertyId::Width, "inherit"s},
                                },
                        },
                },
        };

        auto &child = root.children[0];
        child.parent = &root;

        // inherit, but not in parent, so receives initial value for property.
        expect_eq(child.get_property<css::PropertyId::Width>(), "auto"sv);

        // inherit, value in parent.
        expect_eq(child.get_property<css::PropertyId::BackgroundColor>(), gfx::Color::from_css_name("blue"));

        // inherit, no parent node.
        child.parent = nullptr;
        expect_eq(child.get_property<css::PropertyId::BackgroundColor>(), gfx::Color::from_css_name("transparent"));
    });

    etest::test("unset css keyword", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::Color, "blue"s}},
                .children{
                        style::StyledNode{
                                .node{dom_node},
                                .properties{
                                        {css::PropertyId::Color, "unset"s},
                                        {css::PropertyId::Width, "unset"s},
                                },
                        },
                },
        };

        auto &child = root.children[0];
        child.parent = &root;

        // unset, not inherited, so receives initial value for property.
        expect_eq(child.get_property<css::PropertyId::Width>(), "auto"sv);

        // unset, inherited, value in parent.
        expect_eq(child.get_property<css::PropertyId::Color>(), gfx::Color::from_css_name("blue"));

        // unset, inherited, no parent node.
        child.parent = nullptr;
        expect_eq(child.get_property<css::PropertyId::Color>(), gfx::Color::from_css_name("canvastext"));
    });

    etest::test("currentcolor css keyword", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::Color, "blue"s}},
                .children{
                        style::StyledNode{
                                .node{dom_node},
                                .properties{
                                        {css::PropertyId::BackgroundColor, "currentcolor"s},
                                },
                        },
                },
        };

        auto &child = root.children[0];
        child.parent = &root;

        expect_eq(child.get_property<css::PropertyId::BackgroundColor>(), gfx::Color::from_css_name("blue"));

        // "color: currentcolor" should be treated as inherit.
        child.properties.push_back({css::PropertyId::Color, "currentcolor"s});
        expect_eq(child.get_property<css::PropertyId::Color>(), gfx::Color::from_css_name("blue"));
    });

    etest::test("get_font_style_property", [] {
        expect_property_eq<css::PropertyId::FontStyle>("oblique", style::FontStyle::Oblique);

        // Unhandled properties don't break things.
        expect_property_eq<css::PropertyId::FontStyle>("???", style::FontStyle::Normal);
    });

    etest::test("get_font_family_property", [] {
        expect_property_eq<css::PropertyId::FontFamily>("abc, def", std::vector<std::string_view>{"abc", "def"});
    });

    etest::test("get_font_size_property", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode root{
                .node = dom_node,
                .properties = {{css::PropertyId::FontSize, "50px"s}},
                .children{
                        style::StyledNode{
                                .node{dom_node},
                                .properties{{css::PropertyId::FontSize, "10px"s}},
                        },
                },
        };
        int default_font_size = style::StyledNode{dom_node, {}, {}}.get_property<css::PropertyId::FontSize>();

        auto &child = root.children[0];
        child.parent = &root;

        // px
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 10);
        expect_eq(root.get_property<css::PropertyId::FontSize>(), 50);

        // %
        child.properties[0] = {css::PropertyId::FontSize, "100%"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 50);
        child.properties[0] = {css::PropertyId::FontSize, "50%"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 25);

        child.properties[0] = {css::PropertyId::FontSize, "larger"};
        expect(child.get_property<css::PropertyId::FontSize>() > 50);
        child.properties[0] = {css::PropertyId::FontSize, "smaller"};
        expect(child.get_property<css::PropertyId::FontSize>() < 50);

        // rem
        auto &child2 = child.children.emplace_back(
                style::StyledNode{.node{dom_node}, .properties{{css::PropertyId::FontSize, "2rem"}}, .parent = &child});
        expect_eq(child2.get_property<css::PropertyId::FontSize>(), 50 * 2);
        child2.properties[0] = {css::PropertyId::FontSize, "0.5rem"};
        expect_eq(child2.get_property<css::PropertyId::FontSize>(), 25);

        // em
        child.properties[0] = {css::PropertyId::FontSize, "2em"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 50 * 2);
        root.properties[0] = {css::PropertyId::FontSize, "25px"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 25 * 2);
        root.properties[0] = {css::PropertyId::FontSize, "2em"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), default_font_size * 2 * 2);
        root.properties.clear();
        expect_eq(child.get_property<css::PropertyId::FontSize>(), default_font_size * 2);

        // unhandled units
        child.properties[0] = {css::PropertyId::FontSize, "1asdf"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 0);

        // 0
        child.properties[0] = {css::PropertyId::FontSize, "0"};
        expect_eq(child.get_property<css::PropertyId::FontSize>(), 0);

        // pt
        expect_property_eq<css::PropertyId::FontSize>("12pt", 16);
        expect_property_eq<css::PropertyId::FontSize>("24pt", 32);

        // Invalid, shouldn't crash.
        // TODO(robinlinden): Make this do whatever other browsers do.
        child.properties[0] = {css::PropertyId::FontSize, "abcd"};
        std::ignore = child.get_property<css::PropertyId::FontSize>();
    });

    etest::test("xpath", [] {
        dom::Node html_node = dom::Element{"html"s};
        dom::Node div_node = dom::Element{"div"s};
        dom::Node text_node = dom::Text{"hello!"s};
        style::StyledNode styled_node{
                .node = html_node,
                .children{
                        style::StyledNode{.node = text_node},
                        style::StyledNode{.node = div_node},
                },
        };

        using NodeVec = std::vector<style::StyledNode const *>;
        expect_eq(dom::nodes_by_xpath(styled_node, "/html"), NodeVec{&styled_node});
        expect_eq(dom::nodes_by_xpath(styled_node, "/html/div"), NodeVec{&styled_node.children[1]});
        expect_eq(dom::nodes_by_xpath(styled_node, "/html/div/"), NodeVec{});
        expect_eq(dom::nodes_by_xpath(styled_node, "/html/div/p"), NodeVec{});
        expect_eq(dom::nodes_by_xpath(styled_node, "/htm/div"), NodeVec{});
        expect_eq(dom::nodes_by_xpath(styled_node, "//div"), NodeVec{&styled_node.children[1]});
    });

    etest::test("get_property, last property gets priority", [] {
        dom::Node dom_node = dom::Element{"dummy"s};
        style::StyledNode styled_node{
                .node = dom_node,
                .properties = {{css::PropertyId::Display, "block"s}, {css::PropertyId::Display, "none"}},
                .children = {},
        };

        expect_eq(styled_node.get_property<css::PropertyId::Display>(), style::DisplayValue::None);
    });

    etest::test("get_property, unhandled display value",
            [] { expect_property_eq<css::PropertyId::Display>("i cant believe this", style::DisplayValue::Block); });

    etest::test("get_property, border-style", [] {
        expect_property_eq<css::PropertyId::BorderBottomStyle>("none", style::BorderStyle::None);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("hidden", style::BorderStyle::Hidden);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("dotted", style::BorderStyle::Dotted);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("dashed", style::BorderStyle::Dashed);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("solid", style::BorderStyle::Solid);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("double", style::BorderStyle::Double);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("groove", style::BorderStyle::Groove);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("ridge", style::BorderStyle::Ridge);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("inset", style::BorderStyle::Inset);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("outset", style::BorderStyle::Outset);
        expect_property_eq<css::PropertyId::BorderBottomStyle>("???", style::BorderStyle::None);

        expect_property_eq<css::PropertyId::BorderLeftStyle>("ridge", style::BorderStyle::Ridge);
        expect_property_eq<css::PropertyId::BorderRightStyle>("ridge", style::BorderStyle::Ridge);
        expect_property_eq<css::PropertyId::BorderTopStyle>("ridge", style::BorderStyle::Ridge);
    });

    etest::test("get_property, color", [] {
        expect_property_eq<css::PropertyId::Color>("rgba(1 2 3)", gfx::Color{1, 2, 3});
        expect_property_eq<css::PropertyId::Color>("rgba(1 2 3 / .5)", gfx::Color{1, 2, 3, 127});
        expect_property_eq<css::PropertyId::Color>("rgba(1 2 3 / -0.5)", gfx::Color{1, 2, 3, 0});
        expect_property_eq<css::PropertyId::Color>("rgba(1 2 3 / 1.5)", gfx::Color{1, 2, 3, 0xFF});

        // Invalid syntax.
        constexpr gfx::Color kErrorColor{0xFF, 0, 0};
        expect_property_eq<css::PropertyId::Color>("rgba(1 2)", kErrorColor);
    });

    etest::test("get_property, text-decoration-line", [] {
        using enum style::TextDecorationLine;
        expect_property_eq<css::PropertyId::TextDecorationLine>("none", std::vector{None});
        expect_property_eq<css::PropertyId::TextDecorationLine>("underline", std::vector{Underline});
        expect_property_eq<css::PropertyId::TextDecorationLine>("overline", std::vector{Overline});
        expect_property_eq<css::PropertyId::TextDecorationLine>("line-through", std::vector{LineThrough});
        expect_property_eq<css::PropertyId::TextDecorationLine>("blink", std::vector{Blink});
        expect_property_eq<css::PropertyId::TextDecorationLine>("underline blink", std::vector{Underline, Blink});

        expect_property_eq<css::PropertyId::TextDecorationLine>("unhandled!", std::vector<style::TextDecorationLine>{});
    });

    etest::test("get_property, white-space", [] {
        expect_property_eq<css::PropertyId::WhiteSpace>("normal", style::WhiteSpace::Normal);
        expect_property_eq<css::PropertyId::WhiteSpace>("pre", style::WhiteSpace::Pre);
        expect_property_eq<css::PropertyId::WhiteSpace>("nowrap", style::WhiteSpace::Nowrap);
        expect_property_eq<css::PropertyId::WhiteSpace>("pre-wrap", style::WhiteSpace::PreWrap);
        expect_property_eq<css::PropertyId::WhiteSpace>("break-spaces", style::WhiteSpace::BreakSpaces);
        expect_property_eq<css::PropertyId::WhiteSpace>("pre-line", style::WhiteSpace::PreLine);

        expect_property_eq<css::PropertyId::WhiteSpace>("unhandled!", std::nullopt);
    });

    etest::test("get_property, non-inherited property for a text node", [] {
        dom::Node dom = dom::Element{"hello"};
        dom::Node text = dom::Text{"world"};
        style::StyledNode styled_node{.node = dom, .properties = {{css::PropertyId::TextDecorationLine, "blink"s}}};
        auto const &child = styled_node.children.emplace_back(style::StyledNode{.node = text, .parent = &styled_node});

        expect(!css::is_inherited(css::PropertyId::TextDecorationLine));
        expect_eq(child.get_property<css::PropertyId::TextDecorationLine>(),
                std::vector{style::TextDecorationLine::Blink});
    });

    return etest::run_all_tests();
}
