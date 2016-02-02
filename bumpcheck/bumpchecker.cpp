#include "bumpchecker.h"
#include <map>
#include <algorithm>
#include <functional>
#include <omp.h>
#include <iostream>
#include <mutex>
namespace bumpchecker
{
using std::equal_to;
using std::find_if;
using std::map;
using boost::any;
using std::pair;
using std::make_pair;

typedef pair<control *,void *> cpair;
typedef map<cpair,unsigned> cache_map;

class cache
{
	cache_map c_m_;
	public:
	inline unsigned get(control *a,item *b,any drt){
		const cpair &p=make_pair(a,(void *)b);
		auto it=c_m_.find(p);
		if(it!=c_m_.end()){
			return it->second;
		}else{
			unsigned n=a->bump(b);
			a->bump_drt(drt);
			c_m_.insert(make_pair(p,n));
			return n;
		}
	}
    
	inline unsigned get(control *a,control *b,any drt){
        if(a->get_level()<b->get_level()){
            std::swap(a,b);
        }
		const cpair &p=make_pair(a,(void *)b);
		auto it=c_m_.find(p);
		if(it!=c_m_.end()){
			return it->second;
		}else{
			unsigned n=a->bump(b);
			a->bump_drt(drt);
			c_m_.insert(make_pair(p,n));
			return n;
		}
	}
	
	inline void set_pass(control *a,void *b){
		const cpair &p=make_pair(a,b);
		if(c_m_.find(p)==c_m_.end()){
			c_m_.insert(make_pair(p,pass));
		}
	}
};

bumpcheck::bumpcheck(unsigned x_,unsigned y_):x(x_),y(y_),static_map(x,y),map(x,y) {}

void bumpcheck::run()
{
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
