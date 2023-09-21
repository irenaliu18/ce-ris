#include "view.hxx"

//type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static int const grid_size = 40;

View::View(Model const& model)
        : model_(model),
        dark_sprite({int(grid_size*.9), int(grid_size*.9)}, Color::from_rgba
        (50, 50, 50)),
        red_sprite({int(grid_size*.9), int(grid_size*.9)}, Color::medium_red()),
        yellow_sprite({int(grid_size*.9), int(grid_size*.9)},
                     Color::medium_yellow()),
        font("sans.ttf", 30)
{ }

void
View::draw(Sprite_set& set) // updates every frame
{
    // game over
    if (model_.get_over()) {
        ge211::Text_sprite::Builder text_builder(font);
        text_builder << "Game over! " << "Score: " << model_.get_score();
        game_over_sprite.reconfigure(text_builder);
        set.add_sprite(game_over_sprite, {2*grid_size, 10*grid_size});

        //text_builder << "Score: " << model_.get_score();
        //score_sprite.reconfigure(text_builder);
        //set.add_sprite(score_sprite, {5*grid_size, 15*grid_size});

    }
    else {

        //loop through vector, draw empty or filled shape
        // This needs to do something!
        for (int j = 19; j >= 0; j--) {
            for (int i = 9; i >= 0; i--) {
                if (model_[{i, j}]) {
                    //this the way to access bools?
                    set.add_sprite(red_sprite, {i * grid_size, j * grid_size});
                } else {
                    set.add_sprite(dark_sprite, {i * grid_size, j * grid_size});
                }
            }
        }

        Shape curr = model_.get_curr();
        for (auto offset: curr.getOffsets()) {
            ge211::Posn<int> pos = curr.getPos() + offset;
            set.add_sprite(red_sprite,
                           {pos.x * grid_size, pos.y * grid_size},
                           1);
        }
        // std::cout << curr.getPos() << " ";

        Shape ghost = model_.get_ghost();
        for (auto offset: ghost.getOffsets()) {
            ge211::Posn<int> pos = ghost.getPos() + offset;

            set.add_sprite(yellow_sprite,
                           {pos.x * grid_size, pos.y * grid_size},
                           1);
        }
    }
    // std::cout << ghost.getPos();

    //update score
//    set.add_sprite();
}

View::Dimensions
View::initial_window_dimensions() const
{
    return { 500,  1000};
}