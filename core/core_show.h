#include <Showmanage/Show.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <core/core.h>
namespace core{
class show_manager{
	std::map<int,graphic::Showmanagemap> map;
	boost::property_tree::ptree map_tree;
	std::vector<graphic::Show *> vec;
	public:
	show_manager(boost::filesystem::path inifile);
	void create_show(std::vector<ritem> &);
};
}