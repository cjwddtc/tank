#include "logic.h"
#include <graphic/Show.h>
#include <bumpcheck_extra/square.h>
extern bool key[];
namespace logic
{
using item::square;
using namespace control;
block::block():shower(0) {}
void block::re_show()
{
    shower->re_show();
}

block::bind_show(graphic::show *show_)
{
    if(shower) delete shower;
    shower=show_;
}
block::~block()
{
    if(shower) delete shower;
}

ritem::ritem(::item::pos p,int lenth,int width,int type_):square(p,lenth,width),type(type_) {}

move_ritem::move_ritem(::item::pos p,int lenth,int width,int type_):square(p,lenth,width),type(type_),x(0),y(0) {}

tank_control::tank_control(move_ritem *block):item(block) {}
void move_ritem::move(boost::any cmd)
{
    move_square::move(cmd);
}

move_ritem *tank_control::get_target()
{
    return item;
}

std::vector<boost::any> tank_control::run()
{
    std::vector<boost::any> a;
    if(key[SDLK_w])
    {
        item->x^=0x1;
        //a.push_back((unsigned)4);
        a.resize(4,(unsigned)0);
        item->y=0;
    }
    else if(key[SDLK_s])
    {
        item->x^=0x1;
        a.resize(4,(unsigned)2);
        item->y=2;
    }
    else if(key[SDLK_a])
    {
        item->x^=0x1;
        a.resize(4,(unsigned)3);
        item->y=3;
    }
    else if(key[SDLK_d])
    {
        item->x^=0x1;
        a.resize(4,(unsigned)1);
        item->y=1;
    }
    return a;
}
unsigned tank_control::bump(item::item *a)
{
    if(a==0){
        return bump_type::stop;
    }
    ritem *b=dynamic_cast<ritem *>(a);
    return bump_type::stop;
}
tank_control::~tank_control()
{
    delete item;
}
}

