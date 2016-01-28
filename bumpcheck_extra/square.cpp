#include "square.h"
#include <assert.h>

namespace item
{

std::vector<pos> square::get_range()
{
    pos b=point;
    std::vector<pos> vec;
    vec.reserve(((height+width)<<1)-4);
    for(size_t i=0; i<width; i++)
    {
        b.y=point.y;
        vec.push_back(b);
        b.y=point.y+(height-1);
        vec.push_back(b);
        b.x++;
    }
    for(size_t i=0; i<height-2; i++)
    {
        b.y--;
        b.x=point.x;
        vec.push_back(b);
        b.x=point.x+(width-1);
        vec.push_back(b);
    }
    return vec;
}

square::square()
{
    assert(0);
}

square::square(pos point_, unsigned int height_, unsigned int width_):point(point_),height(height_),width(width_)
{
}

move_square::move_square()
{
    //assert(0);
}

move_square::move_square(pos point_,unsigned int height_,unsigned int width_):square(point_,height_,width_) {}

void move_square::move(data d)
{
    switch(boost::any_cast<unsigned>(d))
    {
    //switch(d){
    case 3:
        point.x--;
        break;
    case 1:
        point.x++;
        break;
    case 0:
        point.y--;
        break;
    case 2:
        point.y++;
        break;
    default:
        assert(0);
    }
}
}
namespace control
{
data square_control::revert(data cmd)
{
    return boost::any_cast<unsigned>(cmd)^0x2;
}
}
