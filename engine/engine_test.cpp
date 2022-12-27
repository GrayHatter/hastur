// SPDX-FileCopyrightText: 2021-2022 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#include "engine/engine.h"

#include "etest/etest.h"
#include "protocol/iprotocol_handler.h"
#include "protocol/response.h"
#include "uri/uri.h"

#include <utility>

using namespace std::literals;
using etest::expect;
using etest::expect_eq;
using etest::require;

namespace {

class FakeProtocolHandler final : public protocol::IProtocolHandler {
public:
    explicit FakeProtocolHandler(protocol::Response response) : response_{std::move(response)} {}
    [[nodiscard]] protocol::Response handle(uri::Uri const &) override { return response_; }

private:
    protocol::Response response_;
};

} // namespace

int main() {
    etest::test("no handlers set", [] {
        engine::Engine e{std::make_unique<FakeProtocolHandler>(protocol::Response{.err = protocol::Error::Unresolved})};
        e.navigate(uri::Uri::parse("hax://example.com"));

        e = engine::Engine{std::make_unique<FakeProtocolHandler>(protocol::Response{.err = protocol::Error::Ok})};
        e.navigate(uri::Uri::parse("hax://example.com"));
        e.set_layout_width(10);
    });

    etest::test("navigation failure", [] {
        bool success{false};
        engine::Engine e{std::make_unique<FakeProtocolHandler>(protocol::Response{.err = protocol::Error::Unresolved})};
        e.set_on_navigation_failure([&](protocol::Error err) { success = err != protocol::Error::Ok; });
        e.set_on_page_loaded([] { require(false); });
        e.set_on_layout_updated([] { require(false); });

        e.navigate(uri::Uri::parse("hax://example.com"));
        expect(success);
    });

    etest::test("page load", [] {
        bool success{false};
        engine::Engine e{std::make_unique<FakeProtocolHandler>(protocol::Response{.err = protocol::Error::Ok})};
        e.set_on_navigation_failure([&](protocol::Error) { require(false); });
        e.set_on_page_loaded([&] { success = true; });
        e.set_on_layout_updated([] { require(false); });

        e.navigate(uri::Uri::parse("hax://example.com"));
        expect(success);
    });

    etest::test("layout update", [] {
        engine::Engine e{std::make_unique<FakeProtocolHandler>(protocol::Response{.err = protocol::Error::Ok})};
        e.set_on_navigation_failure([&](protocol::Error) { require(false); });
        e.set_on_page_loaded([] { require(false); });
        e.set_on_layout_updated([] { require(false); });

        e.set_layout_width(10);

        bool success{false};
        e.set_on_page_loaded([&] { success = true; });

        e.navigate(uri::Uri::parse("hax://example.com"));

        expect(success);

        e.set_on_page_loaded([&] { require(false); });
        success = false;
        e.set_on_layout_updated([&] { success = true; });

        e.set_layout_width(100);
        expect(success);
    });

    return etest::run_all_tests();
}
