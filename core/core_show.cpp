#include <core/core_show.h>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>
using boost::property_tree::ptree;
using boost::filesystem::path;
using boost::lexical_cast;
namespace core{
void show_manager::create_show(std::vector<ritem>&vec)
{
	//int size=map_tree.get<int>("block.size");
	ptree &b=map_tree.get_child("picture");
	for(auto c:b){
		map[lexical_cast<int>(c.first)].load_from_file(c.second.get<path>("").string());
		map[lexical_cast<int>(c.first)].set_size(
                                           c.second.get<int>("lenth"),
                                           c.second.get<int>("width"));
	}
	for(ritem &i:vec){
        ptree &tr=map_tree.get_child(lexical_cast<std::string>(i.type)+".show");
        int x=tr.get<int>("x");
        int y=tr.get<int>("y");
        int id=tr.get<int>("pid");
        this->vec.push_back(new graphic::ritem_show(&map[id],x,y,&i));
        try{
            ptree &ttr=tr.get_child("twinkle");
            x=ttr.get<int>("x");
            y=ttr.get<int>("y");
            id=ttr.get<int>("pid");
            double freq=ttr.get<double>("freq");
            this->vec.back()=new graphic::twinkl_show(this->vec.back(),
                                                      new graphic::ritem_show(&map[id],x,y,&i),
                                                      freq);
        }catch(...){}
	}
}
show_manager::show_manager(boost::filesystem::path ini_file)
{
	read_xml(ini_file.string(), map_tree);
}
}
