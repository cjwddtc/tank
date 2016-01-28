#ifndef SQUARE_H
#define SQUARE_H
#include <bumpcheck/bumpchecker.h>
namespace item
{
class square:virtual public item::item
{
public:
    pos point;
    unsigned int height;
    unsigned int width;
    square();
    square(pos point_,unsigned int height_,unsigned int width_);
    virtual std::vector<pos> get_range();
};

class move_square:virtual public square,virtual public move_item
{
public:
    move_square();
    move_square(pos point_,unsigned int lenth_,unsigned int width_);
    virtual void move(data d);
};
}

namespace control
{
class square_control:public control
{
    virtual data revert(data cmd);
};
}
#endif
