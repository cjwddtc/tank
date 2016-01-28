#ifndef BUMPCHECKER_H
#define BUMPCHECKER_H
#include <iterator>
#include <boost/multi_array.hpp>
#include "control.h"
namespace bumpchecker{
template <class T>
class two_array{
	void *ptr;
	int x;
	int y;
	public:
	two_array(int x, int y){
        ptr=(T **)calloc(x*y,sizeof(T *));
        this->x=x;
        this->y=y;
    }
	T**operator[](size_t n){
        return (T**)ptr+n*y;
    }

	void clear(){
        memset(ptr,0,sizeof(T*)*x*y);
	}
	~two_array(){
        free(ptr);
        ptr=0;
	}
};

class bumpchecker{
    public:
    int x;
    int y;
	two_array<item::item> static_map;
	two_array<item::move_item> map;
	std::vector<control::control *> controls;
	bumpchecker(size_t width,size_t hight);
	void add_static(item::item *);
	void remove_static(item::item *);
	void run();
};
}
#endif
