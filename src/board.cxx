#include "board.hxx"
#include <algorithm>

using namespace ge211;

Board::Board()
    : dims_({10, 20})
{
   for(int i = 0; i < 20; i++){
       boolBoard_.push_back({});
       for(int j = 0; j < 10; j++){
           boolBoard_[i].push_back(false);
       }
   }
}


Board::Dimensions
Board::dimensions() const
{
    return dims_;
}

bool
Board::good_position(Position pos) const
{
    return 0 <= pos.x && pos.x < dims_.width &&
           0 <= pos.y && pos.y < dims_.height;
}

bool
Board::operator[](Position pos) const
{
    bounds_check_(pos);
    return boolBoard_[pos.y][pos.x];  //y = the row, x = column
}


void Board::set(Position pos, bool f)
{
    boolBoard_[pos.y][pos.x] = f;
}

void Board::setAll(int r, bool f)
{
    for(int i = 0; i < 10; i++){
        boolBoard_[r][i] = f;
    }
}

void
Board::bounds_check_(Position pos) const
{
    if(!good_position(pos)){
        throw Client_logic_error("Board: position out of bounds");
    }
}


std::ostream&
operator<<(std::ostream& os, Board const& board)
{
    Board::Dimensions dims = board.dimensions();

    for (int y = 0; y < dims.height; ++y) {
        for (int x = 0; x < dims.width; ++x) {
            os << board[{x, y}];
        }
        os << "\n";
    }

    return os;
}