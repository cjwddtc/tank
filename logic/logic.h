#ifndef LOGIC_H
#define LOGIC_H
#include <bumpcheck_extra/square.h>
#include <graphic/preshow.h>

namespace logic
{

class block:virtual public ::item::square
{
    graphic::show *shower;
public:
    bind_show(graphic::show *show);
    block();
    virtual void re_show();
    virtual ~block();
};

class ritem:virtual public block
{
public:
    unsigned type;
    ritem(::item::pos p,int lenth,int width,int type);
};

class tank:virtual public ::item::move_square,virtual public block
{
public:
    unsigned type;
    unsigned x;//the level<<1 and the state 0,1
    unsigned y;//the drt
    tank(::item::pos p,int lenth,int width,int type);
    virtual void move(boost::any);
};
class tank_control:public control::square_control
{
    tank *item;
public:
    tank_control(tank *);
    tank *get_target();
    std::vector<boost::any> run();
    unsigned bump(item::item *);
    ~tank_control();
};
}
#endif
