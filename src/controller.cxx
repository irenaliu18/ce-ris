#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{
    if(key == ge211::Key::left()){
        model_.move_left();
    }
    else if(key == ge211::Key::right()){
        model_.move_right();
    }
    else if (key == ge211::Key::up()){
        model_.rotate();
    }
    else if (key == ge211::Key::code(' '))
    {
        model_.c_drop_down();
    }
    else if (key == ge211::Key::down()) {
        model_.update();
    }
    else if (key == ge211::Key::code('P')) {
        model_.switch_state();
    }
    //}
    //else if (key == ge211::Key::ESCAPE KEY)
    //else if (key == ge211::Key::SPACE BAR)
    //      then we hard drop the curr piece
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}


//PAUSE -- make it so that on_frame doesn't do anything,
//and ignore some controls
// if (state == pause), return;