#ifndef CONTROL_H
#define CONTROL_H
#include <stddef.h>
#include <vector>
#include "item.h"
namespace control
{
using item::data;

/*this class design of base tpye
 * class may no run right on this class
 */

/*
class data{
	char *ptr;
	size_t pos;
	size_t size;
	public:
	data();
	data(data &&);
	data(const data &);
	template <class T>
	void push_data(T a);
	template <class T>
	T pop_data();
	~data();
};*/

enum bump_type {
    stop=0x1,
    pass=0x2,
    cover=0x4,
};

typedef std::vector<data> move_cmds;
//class control is to control the move_item
class control
{
public:
	control()=default;
	virtual item::move_item*get_target()=0;
	virtual unsigned get_level() const =0;
	//this function return the move command
	virtual move_cmds run()=0;
	//revert the move command
	virtual data revert(data cmd)=0;
	//this function is to tell the control the cmd to bump
	virtual void bump_drt(boost::any cmd);
	//deal with the bump
	virtual unsigned bump(item::item *)=0;
	virtual unsigned bump(::control::control *)=0;
	virtual ~control()=default;
};
}

namespace std
{
template<>
struct less<control::control*> {
	bool operator()(const control::control*a,const control::control*b) {
		return (a->get_level())<(b->get_level());
	}
};
}
#endif // CONTROL_H
