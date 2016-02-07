#include "bumpchecker.h"
#include <map>
#include <algorithm>
#include <functional>
#include <omp.h>
#include <iostream>
#define NDEBUG
#include <mutex>
namespace bumpchecker
{
using std::equal_to;
using std::find_if;
using std::map;
using boost::any;
using std::pair;
using std::make_pair;

typedef pair<control *,item *> item_pair;
typedef pair<control *,control *> control_pair;
typedef pair<unsigned,unsigned> result;
typedef map<item_pair,unsigned> item_cache_map;
typedef map<control_pair,result> control_cache_map;

class cache
{
	item_cache_map i_c_m;
	control_cache_map c_c_m;
	public:
	inline void clear(){
		i_c_m.clear();
		c_c_m.clear();
	}
	inline unsigned get(control *a,item *b,any drt){
		const item_pair &p=make_pair(a,b);
		auto it=i_c_m.find(p);
		if(it!=i_c_m.end()){
			return it->second;
		}else{
			unsigned n=a->bump(b);
			if(n&stop)
				a->bump_drt(drt);
			i_c_m.insert(make_pair(p,n));
			return n;
		}
	}
    
	inline unsigned get(control *a,control *b,any drt){
		int n=a->get_level()-b->get_level();
		unsigned flag=0x1;
		control_pair p;
        if(n<0 || (n==0 && a<b)){
			p=make_pair(b,a);
			flag=0x2;
        }else{
			p=make_pair(a,b);
		}
		auto it=c_c_m.find(p);
		if(it!=c_c_m.end()){
			if(!(it->second.second&flag)){
				if(it->second.first&stop)
					a->bump_drt(drt);
				it->second.second|=flag;
			}
			return it->second.first;
		}else{
			unsigned n=a->bump(b);
			if(n&stop)
				a->bump_drt(drt);
			c_c_m.insert(make_pair(p,make_pair(n,flag)));
			return n;
		}
	}
	
	inline void set_pass(control *a,control *b){
		const control_pair &p=make_pair(a,b);
		if(c_c_m.find(p)==c_c_m.end()){
			c_c_m.insert(make_pair(p,make_pair(pass,(unsigned)0)));
		}
	}
};

bumpcheck::bumpcheck(unsigned x_,unsigned y_):x(x_),y(y_),static_map(x,y),map(x,y) {}

void bumpcheck::run()
{
#ifndef NDEBUG
	std::cout << controls.size() << std::endl;
#endif
	cache cache_;
	map.clear();
	for(control *control_:controls) {
		for(auto &b:control_->get_target()->get_range()) {
            if(b.x>=x || b.y>=y) continue;
			if(map[b.x][b.y]) cache_.set_pass(control_,map[b.x][b.y]);
			map[b.x][b.y]=control_;
		}
	}
	//遍历所有命令
	for(control *control_:controls) {
		move_item *ptr=control_->get_target();
		//遍历移动命令
		for(auto &a:control_->run()) {
			//this data won't use so std::move
			//move the item
			ptr->move(a);
			//get the range and cal
			unsigned int res=0;
			for(auto &b:ptr->get_range()) {
				if(b.x>=x || b.y>=y) {
					res|=cache_.get(control_,(item*)0,a);
				} else {
					if(map[b.x][b.y]==0) {
						map[b.x][b.y]=control_;
					} else if(map[b.x][b.y]!=control_) {
						unsigned c=cache_.get(control_,map[b.x][b.y],a);
						if(c&bump_type::cover) {
							map[b.x][b.y]=control_;
						}
						res|=c;
					}
					if(static_map[b.x][b.y]!=0) {
						res|=cache_.get(control_,static_map[b.x][b.y],a);
					}
				}
			}
			if(res&bump_type::stop) {
				ptr->move(control_->revert(a));
				//break;
			}
		}
		control_->get_target()->re_show();
	}
}

void bumpcheck::add_static(item *ptr)
{
	for(pos p:ptr->get_range()) {
		static_map[p.x][p.y]=ptr;
	}
}

void bumpcheck::remove_static(item* ptr)
{
	for(pos p:ptr->get_range()) {
		static_map[p.x][p.y]=0;
	}
}

void bumpcheck::add_control(control *contro)
{
	controls.insert(contro);
}
void bumpcheck::remove_control(control *contro)
{
	controls.erase(find_if(controls.lower_bound(contro),controls.end(),bind2nd(equal_to<control* >(),contro)));
}

size_t bumpcheck::count_control(control *contro)
{
	auto a=controls.equal_range(contro);
	return std::distance(a.first,a.second);
}
void bumpcheck::reset()
{
	controls.clear();
	static_map.clear();
}

bumpcheck::~bumpcheck()
{
	for(control *a:controls) {
		delete a;
	}
}
}
