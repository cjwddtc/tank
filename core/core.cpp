#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <array>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <graphic/Showmanage.h>
#include <graphic/Show.h>
#include "core.h"
#define NDEBUG

using boost::filesystem::path;
using boost::lexical_cast;
using boost::property_tree::ptree;
using std::istreambuf_iterator;
using std::ifstream;
using std::string;
using std::vector;
using std::swap;
using std::array;
using namespace graphic;
using namespace bumpchecker;
namespace core
{

engine::engine(boost::filesystem::path xml_file)
{
	read_xml(xml_file.string(), p_tree);
	size=p_tree.get<int>("block.size");
	width=p_tree.get<int>("block.width");
	height=p_tree.get<int>("block.height");
	Showmanage::init_Showmanage(height*size,width*size);
	this->checker=new bumpcheck(width*size,height*size);
	ptree &b=p_tree.get_child("picture");
	for(auto c:b) {
		map[lexical_cast<int>(c.first)].load_from_file(	c.second.get<path>("").string(),
		        c.second.get<int>("width"),
		        c.second.get<int>("height"));
	}
}

void engine::init(boost::filesystem::path xml_file)
{
	self=new engine(xml_file);
}

void engine::load_map_imp(unsigned level)
{
	checker->reset();
	ptree &map_t=p_tree.get_child("map."+lexical_cast<string>(level));
	for(auto &b:map_t){
		enemy_names.insert(enemy_names.end(),b.second.get<unsigned>(""),b.first);
	}
	std::string rpath=map_t.get<string>("");
	rpath.erase(remove_if(rpath.begin(),rpath.end(),[](char a){
		if(a=='\t') return true;
		else if(a=='\n') return true;
		else if(a==' ') return true;
		else return false;}),rpath.end());
	ifstream f(path(rpath).string());
	istreambuf_iterator<char> start(f),end;
	unsigned hsize=size>>1;
	ritems.clear();
	for(unsigned i=0; i<height; i++) {
		for(unsigned j=0; j<width; j++) {
			unsigned char state;
			unsigned n=*start++;
			std::stringstream a;
			a<<n;
			a<<".type";
			unsigned type;
			switch(p_tree.get<unsigned>(a.str())) {
			case 1:
				state=*start++;
				if(state&0x4) {
					ritems.insert(new ritem(pos(j*size,i*size),hsize,hsize,n));
					ritems.insert(new ritem(pos(j*size,i*size+hsize),hsize,hsize,n));
					ritems.insert(new ritem(pos(j*size+hsize,i*size),hsize,hsize,n));
					ritems.insert(new ritem(pos(j*size+hsize,i*size+hsize),hsize,hsize,n));
				} else {
					if(state&0x1) {
						ritems.insert(new ritem(pos(j*size+hsize,i*size+hsize),hsize,hsize,n));
					} else {
						ritems.insert(new ritem(pos(j*size,i*size),hsize,hsize,n));
					}
					state++;
					if(state&0x2) {
						ritems.insert(new ritem(pos(j*size,i*size+hsize),hsize,hsize,n));
					} else {
						ritems.insert(new ritem(pos(j*size+hsize,i*size),hsize,hsize,n));
					}
				}
				break;
			case 3:
				a<<".arround";
				type=p_tree.get<int>(a.str());
				ritems.insert(new ritem(pos(j*size-hsize,i*size-hsize),hsize,hsize,type));
				ritems.insert(new ritem(pos(j*size-hsize,i*size+hsize),hsize,hsize,type));
				ritems.insert(new ritem(pos(j*size-hsize,i*size),hsize,hsize,type));

				ritems.insert(new ritem(pos(j*size,i*size-hsize),hsize,hsize,type));
				ritems.insert(new ritem(pos(j*size+hsize,i*size-hsize),hsize,hsize,type));

				ritems.insert(new ritem(pos(j*size+size,i*size-hsize),hsize,hsize,type));
				ritems.insert(new ritem(pos(j*size+size,i*size),hsize,hsize,type));
				ritems.insert(new ritem(pos(j*size+size,i*size+hsize),hsize,hsize,type));
			case 0:
				ritems.insert(new ritem(pos(j*size,i*size),size,size,n));
				break;
			case 2:
				break;
			}
		}
	}
	for(ritem *i:ritems) {
		show *sh;
		ptree &tr=p_tree.get_child(lexical_cast<std::string>(i->type)+".show");
		sh=new ritem_show(	&map[tr.get<unsigned>("pid")],
		                    tr.get<unsigned>("x"),
		                    tr.get<unsigned>("y"),
		                    i);
		if(tr.find("twinkle")!=tr.not_found()){
			ptree &ttr=tr.get_child("twinkle");
			sh=new twinkl_show(sh,
			                   new ritem_show(&map[ttr.get<unsigned>("pid")],
			                                  ttr.get<unsigned>("x"),
			                                  ttr.get<unsigned>("y"),i),
			                   ttr.get<double>("freq"));
		} 
		i->bind_show(sh);
		checker->add_static(i);
	}
	ptree &b=p_tree.get_child("load");
	for(auto c:b) {
		for(int i=0;i<c.second.get("",1);i++)
			create_control(c.first);
	}
}

std::string engine::rand_get_name_imp(){
	if(enemy_names.size()==0){
		return std::string();
	}
	swap(enemy_names[rand()%enemy_names.size()],enemy_names.back());
	std::string p=enemy_names.back();
	enemy_names.pop_back();
	return p;
}

void engine::load_map(unsigned level)
{
	self->load_map_imp(level);
}

void engine::run_imp()
{
	lock=true;
	checker->run();
	for(ritem *i:ritems)
		i->re_show();
	Showmanage::update();
	lock=false;
	for(auto a:to_delete_item) {
		remove_imp(a);
	}
	to_delete_item.clear();
	for(auto a:to_delete_control) {
		remove_imp(a);
	}
	to_delete_control.clear();
}

void engine::run()
{
#ifndef NDEBUG
	std::cout << "start:" << std::endl;
#endif
	self->run_imp();
#ifndef NDEBUG
	std::cout << "end" << std::endl;
#endif
}

ritem_control *engine::create_control_imp(std::string control_type,va_list vl)
{
	ptree &b=p_tree.get_child("control."+control_type);
	ritem_control *con;
	move_ritem *it;
	pos po;
	bool flag;
	std::string str=b.get("type",control_type);
	if(str=="auto_control"){
		flag=false;
		ptree &born=b.get_child("born");
		std::array<bumpchecker::pos,3> ar;
		ar[0].x=born.get<unsigned>("1.x")*size;
		ar[0].y=born.get<unsigned>("1.y")*size;
		ar[1].x=born.get<unsigned>("2.x")*size;
		ar[1].y=born.get<unsigned>("2.y")*size;
		ar[2].x=born.get<unsigned>("3.x")*size;
		ar[2].y=born.get<unsigned>("3.y")*size;
		ptree &fire=b.get_child("fire");
		vector<string> fires;
		unsigned n=b.get<unsigned>("maxlevel");
		for(unsigned i=0; i<n; i++) {
			fires.push_back(fire.get<string>(lexical_cast<string>(i)));
		}
		std::cout << control_type << std::endl;
		con=(new auto_control())->init_auto(ar)->init_fire(fires)->init_explode(b.get<string>("explode"));
		con->destroy();
		it=con->get_target();
	}else{
		if(str=="direct_control") {
			po=pos(va_arg(vl,pos));
			flag=true;
			unsigned drt=va_arg(vl,unsigned);
			con=(new direct_control())->init_drt(drt)->init_explode(b.get<string>("explode"));
		} else if(str=="key_control") {
			flag=false;
			po=pos(b.get<double>("pos.x")*size,b.get<double>("pos.y")*size);
			std::array<int,5> a;
			a[0]=b.get<unsigned>("key.up");
			a[1]=b.get<unsigned>("key.right");
			a[2]=b.get<unsigned>("key.down");
			a[3]=b.get<unsigned>("key.left");
			a[4]=b.get<unsigned>("key.fire");
			vector<string> fires;
			unsigned n=b.get<unsigned>("maxlevel");
			fires.reserve(n);
			ptree &fire=b.get_child("fire");
			for(unsigned i=0; i<n; i++) {
				fires.push_back(fire.get<string>(lexical_cast<string>(i)));
			}
			con=(new key_control())->init_key(a)->
					init_fire(fires)->init_explode(b.get<string>("explode"));
			(con->static_map)[0]=stop;
		}else if(str=="static_control"){
			po=pos(va_arg(vl,pos));
			flag=true;
			con=(new static_control());
		}else{
			assert(0);
		}
		it=create_mritem_imp(b.get<string>("item"),po,flag);
	}
	con->init_r_c(it,b.get<unsigned>("speed"),b.get<unsigned>("id"));
	for(auto c:b.get_child("bump.static")) {
		con->add_bump_deal(lexical_cast<int>(c.first),
						   (bump_result)lexical_cast<unsigned>(c.second.get<path>("").string()),1);
	}
	for(auto c:b.get_child("bump.move")) {
		con->add_bump_deal(lexical_cast<int>(c.first),
						   (bump_result)lexical_cast<unsigned>(c.second.get<path>("").string()),0);
	}
	con->add_bump_deal(0,(bump_result)b.get("bump",1),2);
	checker->add_control(con);
	return con;
}


move_ritem *engine::create_mritem_imp(std::string ritem_type,bumpchecker::pos point,bool flag){
	if(ritem_type.size()==0){
		return 0;
	}
	ptree &item_t=p_tree.get_child("item."+ritem_type);
	move_ritem *it=new move_ritem(point,
	                  item_t.get<unsigned>("size.width"),
	                  item_t.get<unsigned>("size.height"),
	                  flag);
	it->init_x_y(item_t.get("x",0),item_t.get("y",0));
	ptree &show=item_t.get_child("show");
	it->bind_show(new move_ritem_show(&map[show.get<int>("pid")],show.get<int>("x"),show.get<int>("y"),it));
	return it;
}

ritem_control *engine::create_control(std::string control_type,...)
{
	va_list a;
	va_start(a,control_type);
	return self->create_control_imp(control_type,a);
}

engine::~engine()
{
	for(ritem *i:ritems) {
		delete i;
	}
}


void engine::remove_imp(ritem *a)
{
	if(lock) {
		to_delete_item.insert(a);
		return ;
	}
	checker->remove_static(a);
	ritems.erase(a);
	delete a;
}
void engine::remove_imp(ritem_control *a)
{
	if(lock) {
		to_delete_control.insert(a);
		return ;
	}
	if(a->destroy()){
		checker->remove_control(a);
		delete a;
	}
}

void engine::remove(ritem *a)
{
	self->remove_imp(a);
}
void engine::remove(ritem_control *a)
{
	self->remove_imp(a);
}

move_ritem *engine::create_mritem(std::string ritem_type,bumpchecker::pos point,bool flag){
	return self->create_mritem_imp(ritem_type,point,flag);
}


void engine::free()
{
	delete self;
	self=0;
}

void engine::add_imp(ritem_control *a)
{
	checker->add_control(a);
}

void engine::add(ritem_control *a)
{
	self->add_imp(a);
}

std::string engine::rand_get_name()
{
	return self->rand_get_name_imp();
}
engine *engine::self=0;
bool engine::key[256];
}
