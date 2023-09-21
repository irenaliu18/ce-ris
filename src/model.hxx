#pragma once

#include <ge211.hxx>
#include "shape.hxx"
#include "board.hxx"

class Model
{
public:
    //
    //public member variables
    //

    // Model dimensions will use 'int' width and height, like board
    using Dimensions = Board::Dimensions;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = Board::Position;


    /// Constructs a model with the given width and height.
    ///
    /// ## Errors
    ///
    ///  - Throws `ge211::Client_logic_error` if either dimension is less
    ///    than 2 or greater than 8.
    Model();


    //clears and shifts
    void clear_shift();

    //moves the current piece down
    void update();


    void on_frame(double dt);

    ///rotate shape left and right based on keys
    void rotate();

    ///shifts shape left based on mouse
    void move_left();

    ///shifts shape right based on mouse
    void move_right();

    ///drop down piece when down arrow clicked
    void drop_down(Shape& s, bool isCurr);

    ///checks whether curr shape has hit the bottom ??
    void complete_move();

    //drop curr piece down
    void c_drop_down();


    //
    // Accessors
    //
    Shape get_curr() const;
    Shape get_ghost() const;
    bool operator[](Position pos) const;
    int get_score() const;
    bool get_over() const;

    //checks if  game is paused
    bool get_state();
    void switch_state();


private:
    Board board_;
    Shape curr_shape_;
    Shape ghost_shape_;

    int score = 0;
    double timer = 0;
    double speedTimer = 0;
    double speed = 1;
    bool paused = false;
    bool over = false;

    //sets the curr piece, just for testing
    void set_curr(Shape s);

    //gets the first piece
    Shape get_first();

    //gets next piece
    void get_next();

    //drop ghost piece down
    //ghost piece
    //member variable that tracks current piece being played, take its position
    //another that tracks ghost piece
    //for loop that increases y-pos until hit bottom or another piece
    void g_drop_down();

#ifdef CS211_TESTING
    // When this class is compiled for testing, members of a struct named
    // Test_access will be allowed to access private members of this class.
    friend struct Test_access;
#endif

};


/*
* void update();

void rotate();
void move_left();
void move_right();

void drop_down();
void complete_move();

Shape get_curr() const;
Shape get_ghost() const;
bool operator[](ge211::Posn<int> pos) const;
int get_score() const;
bool get_over() const;


Shape get_first();
void set_curr(Shape s);
*/

