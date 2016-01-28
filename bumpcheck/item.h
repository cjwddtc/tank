#ifndef ITEM_H
#define ITEM_H
#include <vector>
#include <stdarg.h>
#include <boost/any.hpp>
namespace item{
typedef boost::any data;
struct pos{
	unsigned int x;
	unsigned int y;
	pos(size_t x_,size_t y_);
	pos()=default;
};

class item{
	public:
	//the function to get the range
	virtual std::vector<pos> get_range()=0;
	virtual void re_show()=0;
	virtual ~item()=default;
};

class move_item:virtual public item{
	public:
	virtual void move(data da)=0;
};
}
#endif
