#ifndef SHOW_H
#define SHOW_H
#include <core/core.h>
namespace graphic{
class show{
    public:
	virtual void re_show()=0;
	virtual ~show()=default;
};
class ritem_show:public show
{
	Showmanagemap *map;
	int x;
	int y;
	logic::ritem *item;
	public:
	ritem_show(Showmanagemap *map,int x,int y,logic::ritem *it);
	void re_show();
};

class move_ritem_show:public show
{
	Showmanagemap *map;
	move_block
};

class twinkl_show:public show{
    show *a;
    show *b;
    double freq;
    public:
    twinkl_show(show *,show *,double);
    virtual void re_show();
    virtual ~twinkl_show();
};
}
#endif
