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
	two_array(int x,int y);
	T**operator[](size_t n);
	void clear();
	~two_array();
};
	
class bumpchecker{
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