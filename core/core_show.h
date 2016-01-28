#include <Showmanage/Show.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>
#include <map>
#include <core/core.h>
namespace core{
class show_manager{
    public:
	std::map<int,graphic::Showmanagemap> map;
	boost::property_tree::ptree map_tree;
	public:
	show_manager(boost::filesystem::path inifile);
	void create_show(std::vector<ritem> &);
	std::vector<graphic::Show *> vec;
};
}
