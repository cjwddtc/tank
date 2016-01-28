#ifndef CONTROL_H
#define CONTROL_H
#include <stddef.h>
#include <vector>
#include "item.h"
namespace control{
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

enum bump_type{
	stop=0x1,
	pass=0x2,
	cover=0x4
};

typedef std::vector<data> move_cmds;
//class control is to control the move_item
class control
{
public:
	control()=default;
	virtual item::move_item*get_target()=0;
	//this function return the move command
	virtual move_cmds run()=0;
	//revert the move command
	virtual data revert(data cmd)=0;
	//deal with the bump
	virtual unsigned int bump(item::item *)=0;
	virtual ~control()=default;
};
}

#endif // CONTROL_H
