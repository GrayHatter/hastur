// SPDX-FileCopyrightText: 2022-2023 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef GFX_SFML_CANVAS_H_
#define GFX_SFML_CANVAS_H_

#include "gfx/icanvas.h"

#include <SFML/Graphics/Shader.hpp>

#include <map>
#include <memory>

namespace sf {
class Font;
class RenderTarget;
} // namespace sf

namespace gfx {

class SfmlCanvas : public ICanvas {
public:
    explicit SfmlCanvas(sf::RenderTarget &target);

    void set_viewport_size(int width, int height) override;
    constexpr void set_scale(int scale) override { scale_ = scale; }

    constexpr void add_translation(int dx, int dy) override {
        tx_ += dx;
        ty_ += dy;
    }

    void fill_rect(geom::Rect const &, Color) override;
    void draw_rect(geom::Rect const &, Color const &, Borders const &, Corners const &) override;
    void draw_text(geom::Position, std::string_view, std::vector<Font> const &, FontSize, FontStyle, Color) override;
    void draw_text(geom::Position, std::string_view, Font, FontSize, FontStyle, Color) override;

private:
    sf::RenderTarget &target_;
    sf::Shader border_shader_{};
    std::map<std::string, std::shared_ptr<sf::Font>, std::less<>> font_cache_;

    int scale_{1};
    int tx_{0};
    int ty_{0};
};

} // namespace gfx

#endif
