#include "model.hxx"
#include <catch.hxx>
#include <ge211.hxx>

using namespace ge211;
using namespace std;

struct Test_access
{
    Model& model;

    explicit Test_access(Model&);

    void update();


    void rotate();
    void move_left();
    void move_right();

    void drop_down(Shape s, bool isCurr);
    void complete_move();

    Shape get_curr() const;
    Shape get_ghost() const;
    bool operator[](ge211::Posn<int> pos) const;
    int get_score() const;
    bool get_over() const;


    Shape get_first();
    void set_curr(Shape s);

};

//test case that checks that if a shape is on the edge of the
// screen, it does not rotate
TEST_CASE("Test rotate out")
{
    Model model;

    Test_access access(model);

    Shape a({0, 1}, 'a');
    Shape b({0, 2}, 'b');
    Shape c({0, 3}, 'c');
    Shape d({0, 4}, 'd');
    Shape e({0, 5}, 'e');
    Shape f({0, 6}, 'f');
    Shape g({0,7}, 'g');

    access.set_curr(a);
    access.rotate();
    CHECK(access.get_curr().getIndex() == 0);


    access.set_curr(e);
    access.rotate();
    CHECK(access.get_curr().getIndex() == 0);


    access.set_curr(g);
    access.rotate();
    CHECK(access.get_curr().getIndex() == 0);

}

//test case that checks that if a shape is on the edge of the
// screen, it does not move
TEST_CASE("Test move out")
{
    Model model;

    Test_access access(model);

    Shape a({0, 1}, 'a');
    Shape b({0, 2}, 'b');
    Shape c({0, 3}, 'c');
    Shape d({0, 4}, 'd');
    Shape e({0, 5}, 'e');
    Shape f({0, 6}, 'f');
    Shape g({0,7}, 'g');

    ge211::Posn<int> p = a.getPos();
    access.set_curr(a);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);

    p = b.getPos();
    access.set_curr(b);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);

     p = c.getPos();
    access.set_curr(c);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);


     p = d.getPos();
    access.set_curr(d);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);


     p = e.getPos();
    access.set_curr(e);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);

     p = f.getPos();
    access.set_curr(f);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);

     p = g.getPos();
    access.set_curr(g);
    access.move_left();
    CHECK(access.get_curr().getPos() == p);

}

//test case that checks that if a shape is on the edge of the
// screen, it moves right
TEST_CASE("Test move right")
{
    Model model;

    Test_access access(model);

    Shape a({0, 1}, 'a');
    Shape b({0, 2}, 'b');
    Shape c({0, 3}, 'c');
    Shape d({0, 4}, 'd');
    Shape e({0, 5}, 'e');
    Shape f({0, 6}, 'f');
    Shape g({0,7}, 'g');

    ge211::Posn<int> p = a.getPos();
    access.set_curr(a);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);

    p = b.getPos();
    access.set_curr(b);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);

    p = c.getPos();
    access.set_curr(c);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);


    p = d.getPos();
    access.set_curr(d);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);


    p = e.getPos();
    access.set_curr(e);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);

    p = f.getPos();
    access.set_curr(f);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);

    p = g.getPos();
    access.set_curr(g);
    access.move_right();
    CHECK(access.get_curr().getPos() != p);

}

//test case that checks that if a shape is on the edge of the
// screen, it moves down
TEST_CASE("Test make new")
{
    Model model;

    Test_access access(model);

    Shape a({3, 15}, 'a');

    ge211::Posn<int> p= a.getPos();
    access.set_curr(a);
    access.drop_down(access.get_curr(), true);
    CHECK(access.get_curr().getPos() == access.get_first().getPos());

    Shape b({3, 15}, 'b');
    Shape c({3, 15}, 'c');
    Shape d({3, 15}, 'd');
    Shape e({3, 15}, 'e');
    Shape f({2, 5}, 'f');
    Shape g({4,12}, 'g');



    p = b.getPos();
    access.set_curr(b);
    access.drop_down(access.get_curr(), true);
    CHECK(access.get_curr().getPos() == access.get_first().getPos());

    p = c.getPos();
    access.set_curr(c);
    access.drop_down(access.get_curr(), true);
    CHECK(access.get_curr().getPos() == access.get_first().getPos());


    p = d.getPos();
    access.set_curr(d);
    access.drop_down(access.get_curr(), true);
    CHECK(access.get_curr().getPos() == access.get_first().getPos());


    p = e.getPos();
    access.set_curr(e);
    access.drop_down(access.get_curr(), true);
    CHECK(access.get_curr().getPos() == access.get_first().getPos());

}

TEST_CASE("Test update")
{
    Model model;

    Test_access access(model);

    Shape e({0, 5}, 'e');

    access.set_curr(e);
    ge211::Posn<int> next = access.get_curr().getPos().down_by(1);
    access.update();
    CHECK(next == access.get_curr().getPos());


}

//
//member function definitions for test_access

Test_access::Test_access(Model& model)
        : model(model)
{ }

void
Test_access::update()
{
    model.update();
}

void
Test_access::rotate()
{
    model.rotate();
}

void
Test_access::move_left()
{
    model.move_left();
}

void
Test_access::move_right()
{
    model.move_right();
}

void
Test_access::drop_down(Shape s, bool isCurr)
{
    model.drop_down( s, isCurr);
}

Shape
Test_access::get_curr() const
{
    return model.get_curr();
}

Shape
Test_access::get_ghost() const
{
    return model.get_ghost();
}

int
Test_access::get_score() const
{
    return model.get_score();
}

bool
Test_access::get_over() const {
    return model.get_over();
}

Shape
Test_access::get_first()
{
    return model.get_first();
}

void
Test_access::set_curr(Shape s)
{
    model.set_curr(s);
}

void
Test_access::complete_move()
{
    model.complete_move();
}

