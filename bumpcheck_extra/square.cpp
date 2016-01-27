#include "square.h"
#include <assert.h>

namespace item{

std::vector<pos> square::get_range()
{
	pos b=point;
	std::vector<pos> vec;
	vec.reserve(((lenth+width)<<1)-4);
	for(size_t i=0;i<lenth;i++){
		b.y=point.y;
		vec.push_back(b);
		b.y=point.y+width;
		vec.push_back(b);
		b.x++;
	}
	for(size_t i=0;i<lenth;i++){
		b.y=point.y;
		vec.push_back(b);
		b.y=point.y+width;
		vec.push_back(b);
		b.x++;
	}
	for(size_t i=0;i<width-2;i++){
		b.y--;
		b.x=point.x;
		vec.push_back(b);
		b.x=point.x+lenth;
		vec.push_back(b);
	}
	return vec;
}

square::square()
{
	assert(0);
}

square::square(pos point_, unsigned int lenth_, unsigned int width_):point(point_),lenth(lenth_),width(width_)
{
}


void move_square::move(data d)
{
	switch(boost::any_cast<unsigned int>(d)){
		case 0:
		point.x++;
		break;
		case 1:
		point.x--;
		break;
		case 2:
		point.y++;
		break;
		case 3:
		point.y--;
		break;
		default:
		assert(0);
	}
}
}
namespace control{
data square_control::revert(data cmd)
{
	return boost::any_cast<unsigned>(cmd)^0xfffffffe;
}
}
