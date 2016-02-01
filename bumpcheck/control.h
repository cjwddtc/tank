#ifndef CONTROL_H
#define CONTROL_H
#include <stddef.h>
#include <vector>
#include "item.h"
namespace bumpchecker
{

enum bump_type {
	pass=0x0,
    stop=0x1,
    cover=0x2,
};

typedef std::vector<data> move_cmds;
//class control is to control the move_item
class control
{
public:
	control()=default;
	virtual bumpchecker::move_item*get_target()=0;
	virtual unsigned get_level() const =0;
	//this function return the move command
	virtual move_cmds run()=0;
	//revert the move command
	virtual data revert(data cmd)=0;
	//this function is to tell the control the cmd to bump
	virtual void bump_drt(boost::any cmd);
	//deal with the bump
	virtual unsigned bump(bumpchecker::item *)=0;
	virtual unsigned bump(bumpchecker::control *)=0;
	virtual ~control()=default;
};
}

namespace std
{
template<>
struct less<bumpchecker::control*> {
	bool operator()(const bumpchecker::control*a,const bumpchecker::control*b) {
		return (a->get_level())<(b->get_level());
	}
};
}
#endif // CONTROL_H
