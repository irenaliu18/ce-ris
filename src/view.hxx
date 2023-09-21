
#pragma once

#include "model.hxx"

#include <ge211.hxx>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;


    //
    // public member functions
    //

    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

    // initial window dimensions
    View::Dimensions initial_window_dimensions() const;

private:
    Model const& model_;

    ge211::Rectangle_sprite const dark_sprite;
    ge211::Rectangle_sprite const red_sprite;
    ge211::Rectangle_sprite const yellow_sprite;
    ge211::Text_sprite game_over_sprite;
    ge211::Text_sprite score_sprite;
    ge211::Font font;

};
