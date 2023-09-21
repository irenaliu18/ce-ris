#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//Represents the state of the tetris game board
class Board
{
public:
    //
    // HELPFUL TYPE ALIASES
    //

    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Each row vector of the board will be of booleans
    using rowVec = std::vector<bool>;


private:
    //
    // PRIVATE DATA MEMBERS
    //
    Dimensions dims_; // will be width = 10, height = 20
    rowVec row_; //each invididual row of bools in the board
    std::vector<rowVec> boolBoard_; // 2D vector of booleans that keeps
                              // track of whcih positions are occupied


public:
    //
    // PUBLIC CONSTRUCTOR & FUNCTION MEMBERS
    //

    /// Constructs a board of dimensions 20 x 10
    Board();


    /// Returns the dimensions of the board
    Dimensions dimensions() const;

    /// Returns whether the given position is in bounds.
    bool good_position(Position) const;

    /// Returns whether or not the position is filled by a tetrimino block
    ///
    /// ## Errors
    ///
    ///  - throws `ge211::Client_logic_error` if `!good_position(pos)`.
    bool operator[](Position pos) const;

    //mutator for elements of boolBoard
    void set(Position where, bool filled);

    //function that sets all elements of a rowVec to user input
    void setAll(int row, bool filled);





private:
    //
    // PRIVATE HELPER FUNCTION MEMBERS
    //
    void bounds_check_(Position where) const;

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

};

//
// FREE FUNCTIONS FOR WORKING WITH THE CLASS
//

/// Board printing, suitable for debugging.
std::ostream&
operator<<(std::ostream&, Board const&);

