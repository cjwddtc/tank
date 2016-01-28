#include "logic.h"
#include <graphic/Show.h>
#include <bumpcheck_extra/square.h>
extern bool key[];
namespace logic{
using item::square;
using namespace control;
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

tank::tank(::item::pos p,int lenth,int width,int type_):square(p,lenth,width),type(type_),x(0),y(0){}

tank_control::tank_control(tank *block):item(block){}
void tank::move(boost::any cmd){
	move_square::move(cmd);
	x=boost::any_cast<unsigned>(cmd);
}

tank *tank_control::get_target(){
	return item;
}

std::vector<boost::any> tank_control::run(){
	if(key[SDLK_w]){
		item->x^=0x1;
		std::vector<boost::any> a;
		a.push_back((unsigned)3);
		//a.resize(1,(unsigned)3);
		return a;
	}
	return std::vector<boost::any>();
}
unsigned tank_control::bump(item::item *a){
	ritem *b=dynamic_cast<ritem *>(a);
	printf("bump%f,%f\n",(float)b->point.x/32,(float)b->point.y/32);
	return bump_type::stop;
}
tank_control::~tank_control(){
	delete item;
}
}

