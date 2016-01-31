#include "bumpchecker.h"
#include <map>
#include <algorithm>
#include <functional>
#include <omp.h>
#include <mutex>
namespace bumpchecker
{
using std::equal_to;
using std::find_if;

bumpchecker::bumpchecker(unsigned x_,unsigned y_):x(x_),y(y_),static_map(x,y),map(x,y) {}

void bumpchecker::run()
{
	map.clear();
	for(control *control_:controls) {
		for(auto &b:control_->get_target()->get_range()) {
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
			std::map<item *,std::pair<unsigned int,std::mutex> > cache_item;
			std::map<control *,std::pair<unsigned int,std::mutex> > cache_control;
			//get the range and cal
			unsigned int res=0;
			for(auto &b:ptr->get_range()) {
				if(b.x<0 || b.y<0 || b.x>=x || b.y>=y) {
					res|=bump_type::stop;
					control_->bump((item *)0);
				} else {
					if(map[b.x][b.y]==0) {
						map[b.x][b.y]=control_;
					} else if(map[b.x][b.y]!=control_) {
						cache_control[map[b.x][b.y]].second.lock();
						unsigned int &c=cache_control[map[b.x][b.y]].first;
						if(c==0) {
							c=control_->bump(map[b.x][b.y]);
							control_->bump_drt(a);
						}
						cache_control[map[b.x][b.y]].second.unlock();
						if(c|bump_type::cover) {
							map[b.x][b.y]=control_;
						}
						res|=c;
					}
					if(static_map[b.x][b.y]!=0) {
						cache_item[static_map[b.x][b.y]].second.lock();
						unsigned int &c=cache_item[static_map[b.x][b.y]].first;
						if(c==0) {
							c=control_->bump(static_map[b.x][b.y]);
							control_->bump_drt(a);
						}
						cache_item[static_map[b.x][b.y]].second.unlock();
						res|=c;
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

void bumpchecker::add_static(item *ptr)
{
	for(pos p:ptr->get_range()) {
		static_map[p.x][p.y]=ptr;
	}
}

void bumpchecker::remove_static(item* ptr)
{
	for(pos p:ptr->get_range()) {
		static_map[p.x][p.y]=0;
	}
}

void bumpchecker::add_control(control *contro)
{
	controls.insert(contro);
}
void bumpchecker::remove_control(control *contro)
{
	controls.erase(find_if(controls.lower_bound(contro),controls.end(),bind2nd(equal_to<control* >(),contro)));
}

size_t bumpchecker::count_control(control *contro){
	auto a=controls.equal_range(contro);
	return std::distance(a.first,a.second);
}
void bumpchecker::reset()
{
	controls.clear();
	static_map.clear();
}

bumpchecker::~bumpchecker()
{
	for(control *a:controls) {
		delete a;
	}
}
}
