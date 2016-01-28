#include "bumpchecker.h"
#include <unordered_map>
#include <omp.h>
#include <mutex>
namespace bumpchecker{
using std::unordered_map;
using ::item::move_item;
using ::control::bump_type;
using ::control::control;

bumpchecker::bumpchecker(size_t x_,size_t y_):x(x_),y(y_),static_map(x,y),map(x,y){}

void bumpchecker::run()
{
	map.clear();
    for(control *control_:controls){
        for(auto &b:control_->get_target()->get_range()){
            map[b.x][b.y]=control_->get_target();
        }
    }
	//遍历所有命令
	for(control *control_:controls){
		move_item *ptr=control_->get_target();
		//遍历移动命令
		for(auto &&a:control_->run()){
			//this data won't use so std::move
			//move the item
			ptr->move(a);
			unordered_map<item::item *,std::pair<unsigned int,std::mutex>> cache;
			//get the range and cal
			unsigned int res=0;
//#pragma omp parallel for
			for(auto &b:ptr->get_range()){
			    if(b.x<0 || b.y<0 || b.x>=x || b.y>=y){
                    res|=bump_type::stop;
                    control_->bump(0);
			    }else if(map[b.x][b.y]==0){
					map[b.x][b.y]=ptr;
				}else if(map[b.x][b.y]!=ptr){
				    cache[map[b.x][b.y]].second.lock();
					unsigned int &c=cache[map[b.x][b.y]].first;
					if(c==0){
						c=control_->bump(map[b.x][b.y]);
					}
				    cache[map[b.x][b.y]].second.unlock();
					if(c|bump_type::cover){
						map[b.x][b.y]=ptr;
					}
					res|=c;
				}else if(static_map[b.x][b.y]!=0){
				    cache[map[b.x][b.y]].second.lock();
					unsigned int &c=cache[static_map[b.x][b.y]].first;
					if(c==0){
						c=control_->bump(static_map[b.x][b.y]);
					}
				    cache[map[b.x][b.y]].second.unlock();
					res|=c;
				}
			}
			if(res&bump_type::stop){
				ptr->move(control_->revert(a));
				break;
			}
		}
		control_->get_target()->ReShow();
	}
}

void bumpchecker::add_static(item::item *ptr){
	for(item::pos p:ptr->get_range()){
		static_map[p.x][p.y]=ptr;
	}
}
void bumpchecker::remove_static(item::item* ptr)
{
	for(item::pos p:ptr->get_range()){
		static_map[p.x][p.y]=0;
	}
}

}
