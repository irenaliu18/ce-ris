//
// Created by Irena Liu on 5/28/23.
//
//class for base tetrimino shapes

#include "shape.hxx"
#include <algorithm>

using namespace ge211;

//
// HELPFUL TYPE ALIASES
//


Shape::Shape(Position p, char t)
    : pos_(p),
      type_(t),
      index_(0) //starting
{
    if(t == 'a') { //0
        offsets_.push_back({{0,  0},
                            {-1, 0},
                            {1,  0},
                            {0,  -1}});
        offsets_.push_back({{0, 1},
                            {0, 0},
                            {-1, 0},
                            {1, 0},});
    }
    else if(t == 'b'){
        offsets_.push_back({ {0, 1},
                             {1, 1},
                             {0, 0},
                            {1, 0},
                           });
    }
    else if(t == 'c'){ //2
        offsets_.push_back({{0, 0},
                            {1, 0},
                            {-1, -1},
                            {0, -1}});
        offsets_.push_back({{1, 1},
                            {0, 0},
                            {1, 0},
                            {0, -1}});
    }
    else if(t == 'd'){
        offsets_.push_back({{0, 0},
                            {-1, 0},
                            {0, -1},
                            {1, -1}});
        offsets_.push_back({{1, 1},
                            {0, 0},
                            {1, 0},
                            {0, -1}
                            });
    }
    else if(t == 'e'){
        offsets_.push_back({{0, 1},
                            {0, 0},
                            {0, -1},
                            {1, -1}
                            });
        offsets_.push_back({{0, 1},
                            {-1, 1},
                            {0, 0},
                            {0, -1},
                            });
    }
    else if(t == 'f'){//5
        offsets_.push_back({{0, 1},
                            {0, 0},
                            {-1, -1},
                            {0, -1}});
        offsets_.push_back({{0, 1},
                            {-1, 1},
                            {0, 0},
                            {0, -1}});
    }
    else if(t == 'g'){
        offsets_.push_back({{0, 2},
                            {0, 1},
                            {0, 0},
                            {0, -1}});
        offsets_.push_back({{0, 0},
                            {-2, 0},
                            {-1, 0},
                            {1, 0}});
    }
}

Shape::Position
Shape::getPos() const
{
    return pos_;
}

void
Shape::setPos(Position p)
{
    pos_ = p;
}

char
Shape::getType()
{
    return type_;
}

void
Shape::setType(char t)
{
    type_ = t;
}

int
Shape::getIndex()
{
    return index_;
}

void
Shape::setIndex(int i)
{
    index_ = i;
}

std::vector<Shape::Dimensions>
Shape::getOffsets() const
{
    return offsets_[index_];
}

