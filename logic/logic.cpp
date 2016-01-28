#include "logic.h"
#include <graphic/Show.h>
namespace logic{
using item::square;
block::block():shower(0){}
void block::re_show(){
	shower->re_show();
}

block::bind_show(graphic::show *show_){
	if(shower) delete shower;
	shower=show_;
}
block::~block(){
	if(shower) delete shower;
}

ritem::ritem(::item::pos p,int lenth,int width,int type_):square(p,lenth,width),type(type_){}
}