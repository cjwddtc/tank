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
using graphic::ritem_show;
using graphic::twinkl_show;
namespace core{

engine::engine(boost::filesystem::path xml_file){
	read_xml(xml_file.string(), p_tree);
	size=p_tree.get<int>("block.size");
	width=p_tree.get<int>("block.width");
	height=p_tree.get<int>("block.height");
	Showmanage::init_Showmanage(height*size,width*size);
	this->checker=new bumpchecker::bumpchecker(width*size,height*size);
	ptree &b=p_tree.get_child("picture");
	for(auto c:b){
		map[lexical_cast<int>(c.first)].load_from_file(	c.second.get<path>("").string(),
														c.second.get<int>("width"),
														c.second.get<int>("height"));
	}
}
void engine::load_map(unsigned level){
	checker->reset();
	ifstream f(path(p_tree.get<string>("map."+lexical_cast<string>(level))));
	istreambuf_iterator<char> start(f),end;
	unsigned hsize=size>>1;
	ritems.clear();
	for(unsigned i=0;i<height;i++){
		for(unsigned j=0;j<width;j++){
			unsigned char state;
			unsigned n=*start++;
			std::stringstream a;
			a<<n;
			a<<".type";
			unsigned type;
			switch(p_tree.get<unsigned>(a.str())){
				case 1:
				state=*start++;
				if(state&0x4)
				{
					ritems.push_back(logic::ritem(item::pos(i*size,j*size),hsize,hsize,n));
					ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size),hsize,hsize,n));
					ritems.push_back(logic::ritem(item::pos(i*size,j*size+hsize),hsize,hsize,n));
					ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size+hsize),hsize,hsize,n));
				}
				else
				{
					if(state&0x1)
					{
						ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size+hsize),hsize,hsize,n));
					}
					else
					{
						ritems.push_back(logic::ritem(item::pos(i*size,j*size),hsize,hsize,n));
					}
					state++;
					if(state&0x2)
					{
						ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size),hsize,hsize,n));
					}
					else
					{
						ritems.push_back(logic::ritem(item::pos(i*size,j*size+hsize),hsize,hsize,n));
					}
				}
				break;
				case 3:
                    a<<".arround";
                    type=p_tree.get<int>(a.str());
                    ritems.push_back(logic::ritem(item::pos(i*size-hsize,j*size-hsize),hsize,hsize,type));
                    ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size-hsize),hsize,hsize,type));
                    ritems.push_back(logic::ritem(item::pos(i*size,j*size-hsize),hsize,hsize,type));

                    ritems.push_back(logic::ritem(item::pos(i*size-hsize,j*size),hsize,hsize,type));
                    ritems.push_back(logic::ritem(item::pos(i*size-hsize,j*size+hsize),hsize,hsize,type));

                    ritems.push_back(logic::ritem(item::pos(i*size-hsize,j*size+size),hsize,hsize,type));
                    ritems.push_back(logic::ritem(item::pos(i*size,j*size+size),hsize,hsize,type));
                    ritems.push_back(logic::ritem(item::pos(i*size+hsize,j*size+size),hsize,hsize,type));
				case 0:
					ritems.push_back(logic::ritem(item::pos(i*size,j*size),size,size,n));
				break;
				case 2:
				break;
			}
		}
	}
	for(logic::ritem &i:ritems){
		show *sh;
        ptree &tr=p_tree.get_child(lexical_cast<std::string>(i.type)+".show");
        sh=new ritem_show(	&map[tr.get<unsigned>("pid")],
        							tr.get<unsigned>("x"),
        							tr.get<unsigned>("y"),
        							&i);
        try{
            ptree &ttr=tr.get_child("twinkle");
            sh=new twinkl_show(sh,
            		new ritem_show(&map[ttr.get<unsigned>("pid")],
            								ttr.get<unsigned>("x"),
            								ttr.get<unsigned>("y"),&i),
            		ttr.get<double>("freq"));
        }catch(...){}
        i.bind_show(sh);
        checker->add_static(&i);
	}
	{
		ptree &b=p_tree.get_child("item.player1");
		ptree &pos=b.get_child("item.pos");
		tank *ta=new tank(item::pos(b.get<unsigned>("pos.x"),12*size,));
		new tank_control(new tank())
		for(auto c:b){
			map[lexical_cast<int>(c.first)].load_from_file(	c.second.get<path>("").string(),
																c.second.get<int>("width"),
															c.second.get<int>("height"));
		}
	}
}

void engine::run(){
	checker->run();
	for(logic::ritem &i:ritems)
		i.re_show();
    Showmanage::update();
}
}
