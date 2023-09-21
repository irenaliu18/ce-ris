#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    // delegates to view
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;

    // executes corresponding action to key

    void on_key(ge211::Key key) override;

    void on_frame(double dt) override;


    /*
     The player is able to move the tetrimino left and right using the left and right arrow keys.

     The player can either drop the tetrimino incrementally using the down arrow key or “hard drop” the piece at once using the spacebar.

     The player can rotate the piece right using the up arrow key or rotate left using the Z arrow key.

     The Escape key pauses the game.

     ///add something for the mouse

     void on_key(Key key) override
{
    if (key == Key::code('q'))
        quit();
    else if (key == Key::up())
        move_up();
    else if (key == Key::down())
        move_down();
}
     */

private:
    Model model_;
    View view_;
};
