#include "logic.h"
#include <graphic/Show.h>
#include <bumpcheck_extra/square.h>
#include <core/core.h>
#include <thread>
#include "core.h"
using namespace std::chrono_literals;
using namespace std::chrono;
using namespace std::this_thread;
namespace core
{
using item::square;
using namespace control;
block::block():shower(0) {}
void block::re_show()
{
    shower->re_show();
}

void block::bind_show(graphic::show *show_)
{
    if(shower) delete shower;
    shower=show_;
}
block::~block()
{
    if(shower) delete shower;
}

ritem::ritem(::item::pos p,unsigned lenth,unsigned width,int type_,bool is_mid):square(p,lenth,width,is_mid),type(type_) {}

move_ritem::move_ritem(::item::pos p,unsigned lenth,unsigned width,bool is_mid):square(p,lenth,width,is_mid),x(0),y(0) {}

void move_ritem::move(boost::any cmd)
{
    move_square::move(cmd);
}

ritem_control::ritem_control(move_ritem *item,unsigned speed_,int type_):it(item),speed(speed_),type(type_){}

void ritem_control::add_bump_deal(int type,bump_result res,unsigned is_static){
	if(is_static==1){
		static_map[type]=res;
	}else if(is_static==0){
		move_map[type]=res;
	}else if(is_static==2){
		null_result=res;
	}
}
move_ritem *ritem_control::get_target(){
    return it;
}

unsigned ritem_control::bump(item::item *a){
	unsigned n;
	if(a==0){
		n=null_result;
	}else{
		ritem *b=dynamic_cast<ritem*>(a);
		n=static_map[b->type];
		if(n&des_des)
			engine::remove(b);
	}
	if(n&src_des)
		engine::remove(this);
    return n;
}

unsigned ritem_control::get_level() const {
	return type;
}

unsigned ritem_control::bump(::control::control *a){
	ritem_control *c=dynamic_cast<ritem_control *>(a);
	move_ritem *b=c->get_target();
	unsigned n=move_map[c->type];
	if(n&des_des)
		engine::remove(c);
	else if(n&des_dec){
		if(b->x>=2)
			b->x-=2;
		else engine::remove(c);
	}
	if(n&src_des)
		engine::remove(this);
    return n;
}

ritem_control::~ritem_control(){
	delete it;
}

direct_control::direct_control(move_ritem *item,unsigned speed_,int type,unsigned drt_):ritem_control(item,speed_,type),drt(drt_){
	item->x=drt;
}
std::vector<boost::any> direct_control::run(){
    std::vector<boost::any> a;
    a.resize(speed,(unsigned)drt);
    return a;
}


fire_control::fire_control(move_ritem* it,unsigned speed,int type,std::string str):
						ritem_control(it,speed,type),firename(str),
						firetime(system_clock::now()){}

void fire_control::fire()
{
	if(system_clock::now()<firetime) return ;
    firetime = system_clock::now()+200ms;
	item::pos point((it->y&1?(it->y&2?0:it->width):it->width/2)+it->point.x,
					(it->y&1?it->height/2:(it->y&2?it->height:0))+it->point.y);
	core::engine::create_control(firename,point,it->y);
}

key_control::key_control(move_ritem* it, unsigned speed,
						int type,std::string firename, int codes [5]):
								fire_control(it,speed,type,firename)
{
	memcpy(key_codes,codes,sizeof(int)*5);
}

std::vector<boost::any> key_control::run(){
	std::vector<boost::any> a;
	for(unsigned i=0;i<4;i++){
		if(engine::key[key_codes[i]]){
			a.resize(speed,(unsigned)i);
			it->y=i;
			break;
		}
	}
	if(engine::key[key_codes[4]]){
		fire();
	}
	return a;
}
}
