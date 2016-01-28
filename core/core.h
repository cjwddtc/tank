#ifndef CORE_H
#define CORE_H
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <map>
#include <logic/logic.h>
#include <graphic/Showmanage.h>
namespace core
{

class engine
{
public:
    boost::property_tree::ptree p_tree;
    unsigned width;
    unsigned height;
    unsigned size;
    std::map<int,graphic::Showmanagemap> map;
    std::vector<logic::ritem> ritems;
    bumpchecker::bumpchecker *checker;
public:
    engine(boost::filesystem::path inifile);
    void load_map(unsigned level);
    void run();
};
}
#endif
