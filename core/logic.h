#ifndef LOGIC_H
#define LOGIC_H
#include <bumpcheck_extra/square.h>
#include <graphic/preshow.h>
#include <iostream>
#include <chrono>
#include <map>

namespace core
{

class block:virtual public ::item::square
{
	graphic::show *shower;
public:
	void bind_show(graphic::show *show);
	block();
	virtual void re_show();
	virtual ~block();
};

class ritem:virtual public block
{
public:
	unsigned type;
	ritem(::item::pos p,unsigned lenth,unsigned width,int type,bool is_mide=false);
};

class move_ritem:virtual public ::item::move_square,virtual public block
{
public:
	unsigned x;//the x offset of x in the bmp
	unsigned y;//the y offset of y in the bmp
	move_ritem(::item::pos p,unsigned lenth,unsigned width,bool is_mid=false);
	virtual void move(boost::any);
};


enum bump_result {
    stop=0x1,
    pass=0x2,
    cover=0x4,
    src_des=0x8,
    des_des=0x10,
    des_dec=0x20,
};

class ritem_control:public control::square_control
{
protected:
	unsigned type;
	move_ritem *it;
	unsigned speed;
	std::map<int,bump_result> static_map;
	std::map<int,bump_result> move_map;
	bump_result null_result;
public:
	void add_bump_deal(int type,bump_result res,unsigned is_static);
	virtual unsigned get_level() const ;
	ritem_control(move_ritem *it,unsigned speed,int type);
	move_ritem *get_target();
	virtual unsigned bump(item::item *);
	virtual unsigned bump(::control::control *);
	virtual ~ritem_control();
};

class direct_control:public ritem_control
{
	unsigned drt;
public:
	direct_control(move_ritem *item,unsigned speed,int type,unsigned drt);
	virtual std::vector<boost::any> run();
};

class fire_control:public ritem_control
{
	std::vector<std::string> firename;
	std::chrono::time_point<std::chrono::system_clock> firetime;
public:
	fire_control(move_ritem *it,unsigned speed,int type,std::vector<std::string> filename);
	void fire();
};

class key_control:public fire_control
{
	int key_codes[5];
public:
	key_control(move_ritem *it,unsigned speed,int type,std::vector<std::string> firename,int codes[5]);
	std::vector<boost::any> run();
};
/*
class auto_control:public fire_control
{
	
};*/

}
#endif
