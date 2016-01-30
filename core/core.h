#ifndef CORE_H
#define CORE_H
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <set>
#include <map>
#include <graphic/Showmanage.h>
#include <stdarg.h>
#include "logic.h"
namespace core
{

class engine
{
	boost::property_tree::ptree p_tree;
	unsigned width;
	unsigned height;
	unsigned size;
	std::map<int,graphic::Showmanagemap> map;
	std::set<ritem *> ritems;
	bool lock;
	std::set<ritem *> to_delete_item;
	std::set<ritem_control *> to_delete_control;
	bumpchecker::bumpchecker *checker;
	engine(boost::filesystem::path inifile);
	ritem_control *create_control_imp(std::string control_type,va_list b);
	void load_map_imp(unsigned level);
	void run_imp();
	~engine();
	void remove_imp(ritem *);
	void remove_imp(ritem_control *);
	static engine *self;
public:
	static bool key[256];
	static void init(boost::filesystem::path inifile);
	static ritem_control *create_control(std::string control_type,...);
	static void load_map(unsigned level);
	static void run();
	static void free();
	static void remove(ritem *);
	static void remove(ritem_control *);
};
}
#endif
