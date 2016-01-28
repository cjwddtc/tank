#ifndef LOGIC_H
#define LOGIC_H
#include <bumpcheck_extra/square.h>
#include <graphic/preshow.h>

namespace logic{

class block:virtual public ::item::square{
	graphic::show *shower;
	public:
	bind_show(graphic::show *show);
	block();
	virtual void re_show();
	virtual ~block();
};

class ritem:virtual public block
{
public:
	int type;
	ritem(::item::pos p,int lenth,int width,int type);
};

class move_block:virtual public ::item::move_square,virtual public block
{
	
};
}
#endif