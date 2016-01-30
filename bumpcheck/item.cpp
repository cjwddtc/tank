#include "item.h"
namespace item
{
pos pos::operator-(pos a){
	return pos(x-a.x,y-a.y);
}
pos::pos(unsigned x_,unsigned y_):x(x_),y(y_) {}
}
