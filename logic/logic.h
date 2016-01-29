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

class move_ritem:virtual public ::item::move_square,virtual public block
{
public:
    unsigned type;
    unsigned x;//the x offset of x in the bmp
    unsigned y;//the y offset of y in the bmp
    move_ritem(::item::pos p,int lenth,int width,int type);
    virtual void move(boost::any);
};
class tank_control:public control::square_control
{
    move_ritem *item;
public:
    tank_control(move_ritem *);
    move_ritem *get_target();
    std::vector<boost::any> run();
    unsigned bump(item::item *);
    ~tank_control();
};
}
#endif
