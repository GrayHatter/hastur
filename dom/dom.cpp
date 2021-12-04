// SPDX-FileCopyrightText: 2021 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "dom/dom.h"

#include <algorithm>
#include <iterator>
#include <ostream>
#include <sstream>
#include <variant>
#include <vector>

namespace dom {
namespace {

template<class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};

// Not needed as of C++20, but gcc 10 won't work without it.
template<class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

void print_node(dom::Node const &node, std::ostream &os, uint8_t depth = 0) {
    for (int8_t i = 0; i < depth; ++i) {
        os << "  ";
    }
    std::visit(Overloaded{
                       [&os, depth](dom::Element const &element) {
                           os << "tag: " << element.name << '\n';
                           for (auto const &child : element.children) {
                               print_node(child, os, depth + 1);
                           }
                       },
                       [&os](dom::Text const &text) { os << "value: " << text.text << '\n'; },
               },
            node);
}

} // namespace

std::string to_string(Document const &document) {
    std::stringstream ss;
    ss << "doctype: " << document.doctype << '\n';
    print_node(document.html_node, ss);
    return ss.str();
}

std::vector<Element const *> nodes_by_path(std::reference_wrapper<Node const> root, std::string_view path) {
    if (!std::holds_alternative<Element>(root.get())) {
        return {};
    }

    auto const &element = std::get<Element>(root.get());
    return nodes_by_path(element, path);
}

std::vector<Element const *> nodes_by_path(std::reference_wrapper<Element const> root, std::string_view path) {
    std::vector<Element const *> next_search{&root.get()};
    std::vector<Element const *> searching{};
    std::vector<Element const *> goal_nodes{};

    while (!next_search.empty()) {
        searching.swap(next_search);
        next_search.clear();

        for (auto node : searching) {
            if (path == node->name) {
                goal_nodes.push_back(node);
                continue;
            }

            if (path.starts_with(node->name + ".")) {
                // TODO(robinlinden): This would be so much better with ranges.
                std::vector<Node const *> node_pointers{};
                std::transform(cbegin(node->children),
                        cend(node->children),
                        back_inserter(node_pointers),
                        [](Node const &n) -> Node const * { return &n; });
                std::vector<Node const *> only_elements{};
                std::remove_copy_if(cbegin(node_pointers),
                        cend(node_pointers),
                        back_inserter(only_elements),
                        [](Node const *n) -> bool { return !std::holds_alternative<Element>(*n); });
                std::transform(cbegin(only_elements),
                        cend(only_elements),
                        back_inserter(next_search),
                        [](Node const *n) -> Element const * { return std::get_if<Element>(n); });
            }
        }

        // Remove name + separator.
        std::size_t separator_position{path.find_first_of(".")};
        if (separator_position == path.npos) {
            break;
        }

        path.remove_prefix(separator_position + 1);
    }

    return goal_nodes;
}

} // namespace dom
