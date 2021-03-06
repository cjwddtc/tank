#include "logic.h"
#include <graphic/Show.h>
#include <bumpcheck_extra/square.h>
#include <core/core.h>
#include <thread>
#include "core.h"
namespace core
{
using namespace std::chrono_literals;
using namespace std::chrono;
using namespace std::this_thread;
using namespace bumpchecker;
using namespace graphic;
using namespace std;
using boost::any;
block::block():shower(0) {}
void block::re_show()
{
	shower->re_show();
}

void block::bind_show(show *show_)
{
	if(shower) delete shower;
	shower=show_;
}
block::~block()
{
	if(shower) delete shower;
}

ritem::ritem(pos p,unsigned lenth,unsigned width,int type_,bool is_mid):square(p,lenth,width,is_mid),type(type_) {}

move_ritem::move_ritem(pos p,unsigned lenth,unsigned width,bool is_mid):square(p,lenth,width,is_mid),x(0),y(0) {}

void move_ritem::init_x_y(unsigned x,unsigned y)
{
	this->x=x;
	this->y=y;
}

void move_ritem::move(any cmd)
{
	move_square::move(cmd);
}

ritem_control *ritem_control::init_r_c(move_ritem *item,unsigned speed_,int type_)
{
	is_delete=false;
	it=item;
	speed=speed_;
	type=type_;
	return this;
}

void ritem_control::add_bump_deal(int type,bump_result res,unsigned is_static)
{
 	if(is_static==1) {
		static_map[type]=res;
	} else if(is_static==0) {
		move_map[type]=res;
	} else if(is_static==2) {
		null_result=res;
	}
}

move_ritem *ritem_control::get_target()
{
	return it;
}

unsigned ritem_control::bump(item *a)
{
	unsigned n;
	if(a==0) {
		n=null_result;
	} else {
		ritem *b=dynamic_cast<ritem*>(a);
		n=static_map[b->type];
		if(n&des_des)
			engine::remove(b);
	}
	if(n&src_des){
		engine::remove(this);
	}
	return n;
}

unsigned ritem_control::bump(control *a)
{
	ritem_control *c=dynamic_cast<ritem_control *>(a);
    if(c->type>type){
        return c->bump(this);
    }
	unsigned n=move_map[c->type];
	if(n&des_des){
		engine::remove(c);
	}
	if(n&src_des){
		engine::remove(this);
	}
	return n;
}

unsigned ritem_control::get_level() const
{
	return type;
}

bool ritem_control::destroy()
{
	return true;
}

ritem_control::~ritem_control()
{
	delete it;
}


std::vector<boost::any> static_control::run(){
	//std::cout << this << ":" << speed << std::endl;
	if(!speed--){
		engine::remove(this);
	}
	return std::vector<boost::any>();
}


explode_control *explode_control::init_explode(std::string explod_name_){
	explod_name=explod_name_;
	return this;
}

bool explode_control::destroy(){
	bumpchecker::pos p=it->point;
	p.x+=it->width/2;
	p.y+=it->height/2;
	if(it)
		engine::create_control(explod_name,p);
	return true;
}

explode_control::~explode_control(){
	explode_control::destroy();
}

direct_control *direct_control::init_drt(unsigned drt_)
{
	drt=drt_;
	return this;
}

std::vector<boost::any> direct_control::run()
{
	it->x=drt;
	std::vector<boost::any> a;
	a.resize(speed,(unsigned)drt);
	return a;
}


fire_control *fire_control::init_fire(std::vector<std::string> strs)
{
	firename=strs;
	return this;
}

void fire_control::fire()
{
	if(system_clock::now()<firetime) return ;
	firetime = system_clock::now()+500ms;
	pos point((it->y&1?(it->y&2?0:it->width):it->width/2)+it->point.x,
		          (it->y&1?it->height/2:(it->y&2?it->height:0))+it->point.y);
	engine::create_control(firename[it->x>>1],point,it->y);
}

key_control *key_control::init_key(std::array<int,5> codes)
{
	key_codes=codes;
	return this;
}

std::vector<boost::any> key_control::run()
{
	std::vector<boost::any> a;
	for(unsigned i=0; i<4; i++) {
		if(engine::key[key_codes[i]]) {
			a.resize(speed,(unsigned)i);
			it->y=i;
			break;
		}
	}
	if(engine::key[key_codes[4]]) {
		fire();
	}
	return a;
}

auto_control *auto_control::init_auto(std::array<bumpchecker::pos,3> born_)
{
	born=born_;
	return this;
}

std::vector<boost::any> auto_control::run()
{
	std::vector<boost::any> a;
	fire();/*
	if(ok_drt.empty()){
		a.push_back((unsigned)0);
		a.push_back((unsigned)1);
		a.push_back((unsigned)2);
		a.push_back((unsigned)3);
		it->y=rand()%4;
	}else{
		if(!rand()%10){
			current_drt =ok_drt[rand()%ok_drt.size()];
		}
		a.resize(speed,current_drt);/*
		a.push_back(revert(current_drt));
		a.push_back(current_drt^1);
		a.push_back(current_drt^3);
		a.push_back(current_drt^3);
		it->y=current_drt;
	}*/
	if(ok_drt.size()==0){
		current_drt=rand()%4;
	}else if(ok_drt.size()!=4){
		current_drt =rand()%4;//ok_drt[rand()%ok_drt.size()];
	}
	a.resize(speed,current_drt);
	it->y=current_drt;
	ok_drt.assign( {0,1,2,3});
	return a;
}
void auto_control::bump_drt(boost::any drti)
{
	unsigned drt=boost::any_cast<unsigned>(drti);
	ok_drt.erase(remove_if(ok_drt.begin(),ok_drt.end(),bind1st(std::equal_to<unsigned>(),drt)),ok_drt.end());
}
bool auto_control::destroy(){
	if(it){
		if(it->x>>1==0){
			explode_control::destroy();
			delete it;
			it=engine::create_mritem(engine::rand_get_name(),born[rand()%3]);
			if(it==0) return ritem_control::destroy();
		}else 
			it->x-=2;
	}else{
		it=engine::create_mritem(engine::rand_get_name(),born[rand()%3]);
		if(it==0) return ritem_control::destroy();
	}
	return false;
}
}
