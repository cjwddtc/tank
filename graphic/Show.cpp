#include "Show.h"
namespace graphic{
    using logic::ritem;
	ritem_show::ritem_show(Showmanagemap *map_,int x_,int y_,ritem *it):map(map_),x(x_),y(y_),item(it){	}
	void ritem_show::re_show(){
		(*map)[x][y].render(item->point.x,item->point.y);
	}

    twinkl_show::twinkl_show(show *a_,show *b_,double freq_):a(a_),b(b_),freq(freq_){}
    void twinkl_show::re_show(){
        if((int)((double)clock()*freq/CLOCKS_PER_SEC)&1)
            a->re_show();
        else
            b->re_show();
    }
    twinkl_show::~twinkl_show(){
        delete a;
        delete b;
    }
}
//graphic::ritem_show::ritem_show(Showmanagemap* map_, int x_, int y_, core::ritem* it):map(map_),x(x_),y(y_),item(it){	}
