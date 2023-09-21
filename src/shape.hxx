//
// Created by Irena Liu on 5/28/23.
//
//class for base tetrimino shapes

#pragma once

#include <ge211.hxx>

#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Shape
{
public:
    //
    // HELPFUL TYPE ALIASES
    //

    /// Shape dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Shape positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    ///Shape row vectors will be 'Dimensions'
    using rowVec = std::vector<Dimensions>;


private:
    //
    // private data types
    //

    Position pos_; // is always (0, 0) in relation to the offsets

    char type_;  // a,b,c,d,e,f,g
    int index_;   // index indicates configuraton of the shape
                  // 0 = original  1 = rotated
    std::vector<rowVec> offsets_;

private:
    //
    // private helper functions
    //


public:
    //
    // public functions
    //

    //public constructor
    Shape(Position p, char t);

    //accessor for pos
    Position getPos() const;

    //mutator for pos
    void setPos(Position p);

    //accessor for type
    char getType();

    //mutator for type
    void setType(char t);

    //accessor for index
    int getIndex();

    //mutator for index
    void setIndex(int i);

    //accessor for offsets for current index
    std::vector<Dimensions> getOffsets() const;

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

};


