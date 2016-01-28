#ifndef SHOW_H
#define SHOW_H
#include <logic/logic.h>
#include "Showmanage.h"
namespace graphic
{
class show
{
public:
    virtual void re_show()=0;
    virtual ~show()=default;
};
class ritem_show:public show
{
    Showmanagemap *map;
    int x;
    int y;
    logic::ritem *item;
public:
    ritem_show(Showmanagemap *map,int x,int y,logic::ritem *it);
    void re_show();
};

class tank_show:public show
{
    Showmanagemap *map;
    logic::tank *item;
    int x;
    int y;
public:
    tank_show(Showmanagemap *map,int x,int y,logic::tank *it);
    void re_show();
};

class twinkl_show:public show
{
    show *a;
    show *b;
    double freq;
public:
    twinkl_show(show *,show *,double);
    virtual void re_show();
    virtual ~twinkl_show();
};
}
#endif
