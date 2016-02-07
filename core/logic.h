#ifndef LOGIC_H
#define LOGIC_H
#include <bumpcheck_extra/square.h>
#include <graphic/preshow.h>
#include <iostream>
#include <chrono>
#include <map>
#include <array>

namespace core
{

class block:virtual public bumpchecker::square
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
	ritem(bumpchecker::pos p,unsigned lenth,unsigned width,int type,bool is_mide=false);
};

class move_ritem:virtual public bumpchecker::move_square,virtual public block
{
public:
	unsigned x;//the x offset of x in the bmp
	unsigned y;//the y offset of y in the bmp
	move_ritem(bumpchecker::pos p,unsigned lenth,unsigned width,bool is_mid=false);
	void init_x_y(unsigned x,unsigned y);
	virtual void move(boost::any);
};


enum bump_result {
    stop=0x1,
    cover=0x2,
    src_des=0x4,
    des_des=0x8,
};

class ritem_control:public bumpchecker::square_control
{
protected:
	unsigned type;
	move_ritem *it;
	unsigned speed;
	std::map<int,bump_result> move_map;
	bump_result null_result;
	bool is_delete;
public:
	std::map<int,bump_result> static_map;
	void add_bump_deal(int type,bump_result res,unsigned is_static);
	virtual unsigned get_level() const ;
	ritem_control()=default;
	ritem_control *init_r_c(move_ritem *it,unsigned speed,int type);
	move_ritem *get_target();
	virtual unsigned bump(bumpchecker::item *);
	virtual unsigned bump(bumpchecker::control *);
	virtual ~ritem_control();
	virtual bool destroy();
};

class static_control:public ritem_control
{
	virtual std::vector<boost::any> run();
};

class explode_control:public ritem_control
{
	std::string explod_name;
public:
	explode_control *init_explode(std::string explod_name);
	virtual bool destroy();
	virtual ~explode_control();
};

class direct_control:public explode_control
{
	unsigned drt;
public:
	direct_control()=default;
	direct_control *init_drt(unsigned drt);
	virtual std::vector<boost::any> run();
};

class fire_control:public explode_control
{
	std::vector<std::string> firename;
	std::chrono::time_point<std::chrono::system_clock> firetime;
public:
	fire_control()=default;
	fire_control *init_fire(std::vector<std::string> firename);
	void fire();
};

class key_control:public fire_control
{
	std::array<int,5> key_codes;
public:
	key_control()=default;
	key_control *init_key(std::array<int,5> codes);
	std::vector<boost::any> run();
};

class auto_control:public fire_control
{
	std::array<bumpchecker::pos,3> born;
	std::vector<unsigned> ok_drt;
	unsigned current_drt;
public:
	auto_control()=default;
	auto_control *init_auto(std::array<bumpchecker::pos,3> born);
	virtual std::vector<boost::any> run();
	virtual void bump_drt(boost::any drt);
	virtual bool destroy();
};

}
#endif
