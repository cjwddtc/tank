#include "bumpchecker.h"
#include <unordered_map>
namespace bumpchecker{
using std::unordered_map;
using ::item::move_item;
using ::control::bump_type;
using ::control::control;

bumpchecker::bumpchecker(size_t x,size_t y):static_map(x,y),map(x,y){}

void bumpchecker::run()
{
	map.clear();
	//遍历所有命令
	for(control *control_:controls){
		move_item *ptr=control_->get_target();
		//遍历移动命令
		for(auto &&a:control_->run()){
			//this data won't use so std::move
			//move the item
			ptr->move(a);
			unordered_map<item::item *,unsigned int> cache;
			//get the range and cal
			unsigned int res=0;
			for(auto &b:ptr->get_range()){
				if(map[b.x][b.y]==0){
					map[b.x][b.y]=ptr;
				}else if(map[b.x][b.y]!=ptr){
					unsigned int &c=cache[map[b.x][b.y]];
					if(c==0){
						c=control_->bump(map[b.x][b.y]);
					}
					if(c|bump_type::cover){
						map[b.x][b.y]=ptr;
					}
					res|=c;
				}else if(static_map[b.x][b.y]!=0){
					unsigned int &c=cache[static_map[b.x][b.y]];
					if(c==0){
						c=control_->bump(static_map[b.x][b.y]);
					}
					res|=c;
				}
			}
			if(res|bump_type::stop){
				ptr->move(control_->revert(a));
			}
		}
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


template <class T>
two_array<T>::two_array(int x, int y){
	ptr=(T **)calloc(x*y,sizeof(T *));
	this->x=x;
	this->y=y;
}

template <class T>
T** two_array<T>::operator[](size_t n){
	return (T**)ptr+n*y;
}

template <class T>
void two_array<T>::clear(){
}

template <class T>
two_array<T>::~two_array(){
	free(ptr);
}
}