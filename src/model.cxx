#include "model.hxx"
#include "view.hxx"

//#pragma once

#include <ge211.hxx>
#include <cstdlib>

#include <iostream>
#include <vector>

Model::Model()
    : curr_shape_(get_first()),
      ghost_shape_(curr_shape_)
{}


//
void
Model::update()
{
    if (paused || over) {
        return;
    }
    Position next_pos = curr_shape_.getPos().down_by(1);
    for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
//        board_.set(curr_shape_.getPos() + offset, true); //***
        if (!board_.good_position(next_pos + offset)
            || board_[{next_pos + offset}] == true) {
            complete_move(); //sets the positon of the current piece into the
                               // board, also gives a new shape to current shape
            clear_shift();  //checks to see if any rows can be cleared. if
                            // yes, acts accordingly
            return;
        }
    }

    // for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
    //     board_.set(curr_shape_.getPos() + offset, false);
    //     board_.set(next_pos + offset, true);
    // }
    curr_shape_.setPos(next_pos);
}

void
Model::on_frame(double dt)
{
    if (paused || over) {
        return;
    }
    ghost_shape_ = curr_shape_;
     g_drop_down();

    timer += dt;
    speedTimer += dt;
    if (timer > speed) {
        timer = 0;
        update();
    }
    if (speedTimer > 60 && speed > .2) {
        speedTimer = 0;
        speed -= .1;
    }

}

void
Model::clear_shift() { // does the clear shifting
    for (int j = 19; j >= 0; j--) {
        int counter = 0;
        for (int i = 9; i >= 0; i--) {
            if (board_[{i, j}]) {
                counter++;
            }
            if (counter == 10) { //whole row is occupied
                for (int col = 0; col < 10; col++) {//col set to false
                    board_.set({col, j}, false);
                    score += 10;
                    std::cout << "clear row ";
                }
                //shift rows down
                for (int r = j; r > 0; --r) {
                    for (int col = 0; col < 10; ++col) {
                        bool f = board_[{col, r - 1}];
                        board_.set({col, r}, f);
                    }
                }
                // Clear the top row
                for (int col = 0; col < 10; ++col) {
                    //board_[0][col] = false;
                    board_.set({col, 0}, false); // check
                }
            }
        }
    }
}


//HELPER FUNCTIONS
void
Model::rotate(){
    if (paused || over) {
        return;
    }
    //sets curr to false
//     for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
// //        board_[s.getPos().x][s.getPos().y] = false;
//         board_.set({curr_shape_.getPos().x, curr_shape_.getPos().y}, false);
//     }
    int prev_index = curr_shape_.getIndex();
    if (curr_shape_.getIndex() == 0) {
        curr_shape_.setIndex(1);
    }
    else {
        curr_shape_.setIndex(0);
    }

    Position pos = curr_shape_.getPos();
    for (auto offset: curr_shape_.getOffsets()) {
        if ((!board_.good_position(pos + offset))
            || (board_[{pos + offset}] == true)) {
            curr_shape_.setIndex(prev_index);
            return;
        }
    }
    //sets new to true
//     for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
// //        board_[s.getPos().x][s.getPos().y] = true;
//         board_.set({curr_shape_.getPos().x, curr_shape_.getPos().y}, true);
//     }
}
void
Model::move_left(){
    if (paused || over) {
        return;
    }

    Position next_pos = curr_shape_.getPos().left_by(1);

    for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
        //      board_.set(curr_shape_.getPos() + offset, true);
        if ((!board_.good_position(next_pos + offset))
            || (board_[{next_pos + offset}] == true)) {
            return;
        }
    }

    // for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
    //     board_.set(curr_shape_.getPos() + offset, false);
    //     board_.set(next_pos + offset, true);
    // }
    curr_shape_.setPos(next_pos);
}

void
Model::move_right(){
    if (paused || over) {
        return;
    }

    Position next_pos = curr_shape_.getPos().right_by(1);

    for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
        //      board_.set(curr_shape_.getPos() + offset, true);
        if ((!board_.good_position(next_pos + offset))
            || (board_[{next_pos + offset}] == true)) {
            return;
        }
    }

    // for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
    //     board_.set(curr_shape_.getPos() + offset, false);
    //     board_.set(next_pos + offset, true);
    // }
    curr_shape_.setPos(next_pos);
}
void
Model::drop_down(Shape& s, bool isCurr)
{
    if (paused || over) {
        return;
    }

    while (true) {
        bool valid_pos = true;
        for (ge211::Dims<int> offset: s.getOffsets()) {
            // board_.set({s.getPos().x, s.getPos().y}, false);
            //current position
            int x = s.getPos().x + offset.width;
            int y = s.getPos().y + offset.height;
            if (y < 0) {
                continue;
            }
            if (y >= 20 || board_[{x, y}]) {

                valid_pos = false;
                break;
            }
        }
        if (valid_pos) {

            s.setPos(s.getPos().down_by(1));
        }
        else {
            s.setPos(s.getPos().up_by(1));
            break;
        }

    }

    if (isCurr) {
        complete_move();
    }

    //
    //
    // Position newPos = {s.getPos().x, minY - minOffset - 2};
    // s.setPos(newPos);
    //
    // for (ge211::Dims<int> offset: curr_shape_.getOffsets()) {
    //    board_[s.getPos().x][s.getPos().y + hDiff] = true;
    //      board_.set({s.getPos().x + offset.width, minY + offset.height}, true);
    //  }
}

// finishes placing down current shape, gets the next current shape
void
Model::complete_move()
{
    for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
        if (curr_shape_.getPos().y + offset.height <= 0 ){
            over = true;
            return;
            std::cout<<"over ";
        }
    }
    for (ge211::Dims<int> offset : curr_shape_.getOffsets()) {
        board_.set(curr_shape_.getPos() + offset, true);
    }
    get_next();
}

Shape
Model::get_curr() const
{
    return curr_shape_;
}

Shape
Model::get_ghost() const
{
    return ghost_shape_;
}

bool
Model::operator[](Position pos) const
{
    return board_[pos];
}


int
Model::get_score() const {
    return score;
}

bool
Model::get_state(){
    return paused;
}

bool
Model::get_over() const{
    return over;
}

void
Model::switch_state(){
    paused = !paused;
}

Shape
Model::get_first(){
    vector<char> p = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    ge211::Random_source<int> RANDOMMMM(0, 6);
    int rand = RANDOMMMM.next();
    Shape next({5, 0}, p[rand]);
    return next;
}
void
Model::get_next() {
    if(over){
        return;
    }
    vector<char> p = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    ge211::Random_source<int> RANDOMMMM(0, 6);
    int rand = RANDOMMMM.next();
    Shape next({5, 0}, p[rand]);
    curr_shape_ = next;
}

/*
 * is there a way to make the dimensions of the board less than the entire
 * screen? that way we can make a new shape without CLion throwing an exception
 * and check if the shape comes on screen.
 */
void
Model::g_drop_down()
{
    drop_down(ghost_shape_, false);
}

void
Model::c_drop_down()
{
    drop_down(curr_shape_, true);
    clear_shift();
}

void
Model::set_curr(Shape s)
{
    curr_shape_ = s;
}

