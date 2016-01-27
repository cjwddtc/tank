#ifndef SHOW_H
#define SHOW_H
#include <core/core.h>
#include <Showmanage/Showmanage.h>
namespace graphic{
class Show{
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
}
#endif