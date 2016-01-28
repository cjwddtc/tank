#include "Show.h"
namespace graphic{
	ritem_show::ritem_show(Showmanagemap *map_,int x_,int y_,core::ritem *it):map(map_),x(x_),y(y_),item(it){	}
	void ritem_show::show(){
		(*map)[x][y].render(item->point.x,item->point.y);
	}

    twinkl_show::twinkl_show(Show *a_,Show *b_,double freq_):a(a_),b(b_),freq(freq_){}
    void twinkl_show::show(){
        if((int)((double)clock()*freq/CLOCKS_PER_SEC)&1)
            a->show();
        else
            b->show();
    }
}
//graphic::ritem_show::ritem_show(Showmanagemap* map_, int x_, int y_, core::ritem* it):map(map_),x(x_),y(y_),item(it){	}
