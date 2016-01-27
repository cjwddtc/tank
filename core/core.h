#ifndef CORE_H
#define CORE_H
#include <bumpcheck/bumpchecker.h>
#include <bumpcheck_extra/square.h>
#include <boost/filesystem.hpp>
#include <boost/multi_array.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <vector>
namespace core{
struct block{
	unsigned char shape;
	unsigned char type;
};

class ritem:public item::square{
	public:
	int type;
	ritem(::item::pos p,int lenth,int width,int type);
	void ReShow();
};

class map_manager{
	boost::property_tree::ptree map_tree;
	map_manager(boost::filesystem::path inifile);
	void read_map(boost::filesystem::path file,std::vector<ritem> &);
};

class engine{
	//map_manager
};
}
#endif