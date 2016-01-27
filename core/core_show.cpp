#include <core/core_show.h>
#include <boost/lexical_cast.hpp>
using boost::property_tree::ptree;
using boost::filesystem::path;
using boost::lexical_cast;
namespace core{
void show_manager::create_show(std::vector<ritem>&vec)
{
	//int size=map_tree.get<int>("block.size");
	ptree &b=map_tree.get_child("picture");
	for(auto c:b){
		map[lexical_cast<int>(c.second.data())].load_from_file(path(c.first).string());
	}
	for(ritem &i:vec){
		std::string b=lexical_cast<std::string>(i.type);
		if(map_tree.get<bool>(b+".showtype",false)){
			int x=map_tree.get<int>(b+".showx");
			int y=map_tree.get<int>(b+".showy");
			int id=map_tree.get<int>(b+".pid");
			this->vec.push_back(new graphic::ritem_show(&map[id],x,y,&i));
		}else assert(0);
	}
}
show_manager::show_manager(boost::filesystem::path ini_file)
{
	read_ini(ini_file.string(), map_tree);
}
}