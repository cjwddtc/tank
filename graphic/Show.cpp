#include "Show.h"
#include <time.h>
namespace graphic
{
using core::ritem;
ritem_show::ritem_show(Showmanagemap *map_,int x_,int y_,ritem *it):map(map_),x(x_),y(y_),item(it) {	}
void ritem_show::re_show()
{
    (*map)[x][y].render(item->point.x,item->point.y);
}

twinkl_show::twinkl_show(show *a_,show *b_,double freq_):a(a_),b(b_),freq(freq_) {}
void twinkl_show::re_show()
{
    if((int)((double)clock()*freq/CLOCKS_PER_SEC)&1)
        a->re_show();
    else
        b->re_show();
}
twinkl_show::~twinkl_show()
{
    delete a;
    delete b;
}
move_ritem_show::move_ritem_show(Showmanagemap *map_,int x_,int y_,core::move_ritem *it):map(map_),x(x_),y(y_),item(it) {   }
void move_ritem_show::re_show()
{
    (*map)[x+item->x][y+item->y].render(item->point.x,item->point.y);
}
}
//graphic::ritem_show::ritem_show(Showmanagemap* map_, int x_, int y_, core::ritem* it):map(map_),x(x_),y(y_),item(it){	}
