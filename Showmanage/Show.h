#ifndef SHOW_H
#define SHOW_H
#include <core/core.h>
#include <Showmanage/Showmanage.h>
namespace graphic{
class Show{
    public:
	virtual void show()=0;
};
class ritem_show:public Show
{
	Showmanagemap *map;
	int x;
	int y;
	core::ritem *item;
	public:
	ritem_show(Showmanagemap *map,int x,int y,core::ritem *it);
	void show();
};
class twinkl_show:public Show{
    Show *a;
    Show *b;
    double freq;
    public:
    twinkl_show(Show *,Show *,double);
    void show();
};
}
#endif
