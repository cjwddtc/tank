#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <iterator>
#include <sstream>
#include <iostream>
#include <graphic/Showmanage.h>
#include <graphic/show.h>
#include "core.h"

using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::lexical_cast;
using boost::property_tree::ptree;
using std::istreambuf_iterator;
using std::string;
using ::item::pos;
using ::item::square;
using graphic::Showmanage;
using graphic::show;
using graphic::move_ritem_show;
using graphic::ritem_show;
using graphic::twinkl_show;
namespace core
{

engine::engine(boost::filesystem::path xml_file)
{
    read_xml(xml_file.string(), p_tree);
    size=p_tree.get<int>("block.size");
    width=p_tree.get<int>("block.width");
    height=p_tree.get<int>("block.height");
    Showmanage::init_Showmanage(height*size,width*size);
    this->checker=new bumpchecker::bumpchecker(width*size,height*size);
    ptree &b=p_tree.get_child("picture");
    for(auto c:b)
    {
        map[lexical_cast<int>(c.first)].load_from_file(	c.second.get<path>("").string(),
                c.second.get<int>("width"),
                c.second.get<int>("height"));
    }
}

void engine::init(boost::filesystem::path xml_file){
    self=new engine(xml_file);
}

void engine::load_map_imp(unsigned level)
{
    checker->reset();
    ifstream f(path(p_tree.get<string>("map."+lexical_cast<string>(level))));
    istreambuf_iterator<char> start(f),end;
    unsigned hsize=size>>1;
    ritems.clear();
    for(unsigned i=0; i<height; i++)
    {
        for(unsigned j=0; j<width; j++)
        {
            unsigned char state;
            unsigned n=*start++;
            std::stringstream a;
            a<<n;
            a<<".type";
            unsigned type;
            switch(p_tree.get<unsigned>(a.str()))
            {
            case 1:
                state=*start++;
                if(state&0x4)
                {
                    ritems.insert(new ritem(item::pos(j*size,i*size),hsize,hsize,n));
                    ritems.insert(new ritem(item::pos(j*size,i*size+hsize),hsize,hsize,n));
                    ritems.insert(new ritem(item::pos(j*size+hsize,i*size),hsize,hsize,n));
                    ritems.insert(new ritem(item::pos(j*size+hsize,i*size+hsize),hsize,hsize,n));
                }
                else
                {
                    if(state&0x1)
                    {
                        ritems.insert(new ritem(item::pos(j*size+hsize,i*size+hsize),hsize,hsize,n));
                    }
                    else
                    {
                        ritems.insert(new ritem(item::pos(j*size,i*size),hsize,hsize,n));
                    }
                    state++;
                    if(state&0x2)
                    {
                        ritems.insert(new ritem(item::pos(j*size,i*size+hsize),hsize,hsize,n));
                    }
                    else
                    {
                        ritems.insert(new ritem(item::pos(j*size+hsize,i*size),hsize,hsize,n));
                    }
                }
                break;
            case 3:
                a<<".arround";
                type=p_tree.get<int>(a.str());
                ritems.insert(new ritem(item::pos(j*size-hsize,i*size-hsize),hsize,hsize,type));
                ritems.insert(new ritem(item::pos(j*size-hsize,i*size+hsize),hsize,hsize,type));
                ritems.insert(new ritem(item::pos(j*size-hsize,i*size),hsize,hsize,type));

                ritems.insert(new ritem(item::pos(j*size,i*size-hsize),hsize,hsize,type));
                ritems.insert(new ritem(item::pos(j*size+hsize,i*size-hsize),hsize,hsize,type));

                ritems.insert(new ritem(item::pos(j*size+size,i*size-hsize),hsize,hsize,type));
                ritems.insert(new ritem(item::pos(j*size+size,i*size),hsize,hsize,type));
                ritems.insert(new ritem(item::pos(j*size+size,i*size+hsize),hsize,hsize,type));
            case 0:
                ritems.insert(new ritem(item::pos(j*size,i*size),size,size,n));
                break;
            case 2:
                break;
            }
        }
    }
    for(ritem *i:ritems)
    {
        show *sh;
        ptree &tr=p_tree.get_child(lexical_cast<std::string>(i->type)+".show");
        sh=new ritem_show(	&map[tr.get<unsigned>("pid")],
                            tr.get<unsigned>("x"),
                            tr.get<unsigned>("y"),
                            i);
        try
        {
            ptree &ttr=tr.get_child("twinkle");
            sh=new twinkl_show(sh,
                               new ritem_show(&map[ttr.get<unsigned>("pid")],
                                              ttr.get<unsigned>("x"),
                                              ttr.get<unsigned>("y"),i),
                               ttr.get<double>("freq"));
        }
        catch(...) {}
        i->bind_show(sh);
        checker->add_static(i);
    }
    ptree &b=p_tree.get_child("load");
    for(auto c:b)
    {
        create_control(c.first);
    }
}

void engine::load_map(unsigned level){
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
    for(auto a:to_delete_item){
        remove_imp(a);
    }
    to_delete_item.clear();
    for(auto a:to_delete_control){
        remove_imp(a);
    }
    to_delete_control.clear();
}

void engine::run(){
    self->run_imp();
}

ritem_control *engine::create_control_imp(std::string control_type,va_list vl){
    ptree &b=p_tree.get_child("control."+control_type);
    ritem_control *con;
    ptree &item_t=p_tree.get_child("item."+b.get<string>("item"));
    move_ritem *it;
    if(b.get<string>("type")=="direct_control")
    {
        it=new move_ritem(item::pos(va_arg(vl,item::pos)),
                                      item_t.get<unsigned>("size.width"),
                                      item_t.get<unsigned>("size.height"),
                                      true);
        unsigned drt=va_arg(vl,unsigned);
        con=new direct_control(it,b.get<unsigned>("speed"),b.get<unsigned>("id"),drt);
    }else if(b.get<string>("type")=="key_control")
    {
        it=new move_ritem(item::pos(item_t.get<double>("pos.x")*size,
                                                item_t.get<double>("pos.y")*size),
                                      item_t.get<unsigned>("size.width"),
                                      item_t.get<unsigned>("size.height"));
        int a[5];
        a[0]=b.get<unsigned>("key.up");
        a[1]=b.get<unsigned>("key.right");
        a[2]=b.get<unsigned>("key.down");
        a[3]=b.get<unsigned>("key.left");
        a[4]=b.get<unsigned>("key.fire");
        con=new key_control(it,b.get<unsigned>("speed"),b.get<unsigned>("id"),b.get<string>("fire"),a);
    }else{
        assert(0);
    }
    ptree &show=item_t.get_child("show");
    it->bind_show(new move_ritem_show(&map[show.get<int>("pid")],show.get<int>("x"),show.get<int>("y"),it));
    try{
        for(auto c:b.get_child("bump.static"))
        {
            con->add_bump_deal(lexical_cast<int>(c.first),
                (bump_result)lexical_cast<unsigned>(c.second.get<path>("").string()),1);
        }
    }catch(...){}
    try{
        for(auto c:b.get_child("bump.move"))
        {
            con->add_bump_deal(lexical_cast<int>(c.first),
                (bump_result)lexical_cast<unsigned>(c.second.get<path>("").string()),0);
        }
    }catch(...){}
    con->add_bump_deal(0,(bump_result)b.get<unsigned>("bump"),2);
    checker->add_control(con);
    return con;
}

ritem_control *engine::create_control(std::string control_type,...){
	va_list a;
	va_start(a,control_type);
	return self->create_control_imp(control_type,a);
}

engine::~engine(){
    for(ritem *i:ritems){
        delete i;
    }
}

void engine::remove_imp(ritem *a){
    if(lock){
        to_delete_item.insert(a);
        return ;
    }
    checker->remove_static(a);
    ritems.erase(a);
}
void engine::remove_imp(ritem_control *a){
    if(lock){
        to_delete_control.insert(a);
        return ;
    }
    checker->remove_control(a);
}

void engine::remove(ritem *a){
    self->remove_imp(a);
}
void engine::remove(ritem_control *a){
    self->remove_imp(a);
}

void engine::free(){
    delete self;
    self=0;
} 
engine *engine::self=0;
bool engine::key[256];
}