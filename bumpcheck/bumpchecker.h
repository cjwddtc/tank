#ifndef BUMPCHECKER_H
#define BUMPCHECKER_H
#include "control.h"
#include <set>
namespace bumpchecker
{
/**
this class is just high performace two delims array for pointer
**/
template <class T>
class two_array
{
	void *ptr;
	int x;
	int y;
public:
	two_array(int x, int y) {
		ptr=(T **)calloc(x*y,sizeof(T *));
		this->x=x;
		this->y=y;
	}
	T**operator[](size_t n) {
		return (T**)ptr+n*y;
	}

	void clear() {
		memset(ptr,0,sizeof(T*)*x*y);
	}
	~two_array() {
		free(ptr);
		ptr=0;
	}
};

//bumpchecher use run to bumpecher-move
class bumpcheck
{
public:
	unsigned x;
	unsigned y;
	two_array<item> static_map;
	two_array<control> map;
	std::multiset<control *> controls;
	bumpcheck(unsigned width,unsigned height);
	void add_static(item *);
	void remove_static(item *);
	void add_control(control *control);
	void remove_control(control *control);
	size_t count_control(control *control);
	void run();
	void reset();
	~bumpcheck();
};
}
#endif
