#include "Show.h"
namespace graphic{
	ritem_show::ritem_show(Showmanagemap *map_,int x_,int y_,core::ritem *it):map(map_),x(x_),y(y_),item(it){	}
	void ritem_show::show(){
		(*map)[x][y].render(item->point.x,item->point.y);
	}
}
//graphic::ritem_show::ritem_show(Showmanagemap* map_, int x_, int y_, core::ritem* it):map(map_),x(x_),y(y_),item(it){	}
