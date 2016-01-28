#include <iostream>
#include "core.h"
#include <iterator>
#include <bumpcheck_extra/square.h>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <Showmanage/Showmanage.h>
#include <sstream>

using boost::filesystem::path;
using boost::filesystem::ifstream;
using std::istreambuf_iterator;
using std::string;
using ::item::pos;
using ::item::square;
using boost::lexical_cast;
namespace core{
void ritem::ReShow(){

}
map_manager::map_manager(path ini_file)
{
	read_xml(ini_file.string(), map_tree);
}

void map_manager::read_map(int level,std::vector<ritem> &items)
{
	ifstream f(path(map_tree.get<string>("map."+lexical_cast<string>(level))));
	istreambuf_iterator<char> start(f),end;
	int n;
	int size=map_tree.get<int>("block.size");
	int width=map_tree.get<int>("block.width");
	int lenth=map_tree.get<int>("block.lenth");
	int bsize=size<<1;
	graphic::Showmanage::init_Showmanage(lenth*bsize,width*bsize);
	unsigned char state;
	size_t ii=1;
	for(int i=0;i<width;i++){
		for(int j=0;j<lenth;j++){
			n=*start++;
			std::stringstream a;
			a<<n;
			a<<".type";
			int type;
			switch(map_tree.get<int>(a.str())){
				case 1:
				state=*start++;
				if(state&0x4)
				{
					items.push_back(ritem(item::pos(i*bsize,j*bsize),size,size,n));
					items.push_back(ritem(item::pos(i*bsize+size,j*bsize),size,size,n));
					items.push_back(ritem(item::pos(i*bsize,j*bsize+size),size,size,n));
					items.push_back(ritem(item::pos(i*bsize+size,j*bsize+size),size,size,n));
				}
				else
				{
					if(state&0x1)
					{
						items.push_back(ritem(item::pos(i*bsize+size,j*bsize+size),size,size,n));
					}
					else
					{
						items.push_back(ritem(item::pos(i*bsize,j*bsize),size,size,n));
					}
					state++;
					if(state&0x2)
					{
						items.push_back(ritem(item::pos(i*bsize+size,j*bsize),size,size,n));
					}
					else
					{
						items.push_back(ritem(item::pos(i*bsize,j*bsize+size),size,size,n));
					}
				}
                printf("%d:block:%d\n",ii++,state);
				break;
				case 3:
                    a<<".arround";
                    type=map_tree.get<int>(a.str());
                    items.push_back(ritem(item::pos(i*bsize-size,j*bsize-size),size,size,type));
                    items.push_back(ritem(item::pos(i*bsize+size,j*bsize-size),size,size,type));
                    items.push_back(ritem(item::pos(i*bsize,j*bsize-size),size,size,type));


                    items.push_back(ritem(item::pos(i*bsize-size,j*bsize),size,size,type));
                    items.push_back(ritem(item::pos(i*bsize-size,j*bsize+size),size,size,type));

                    items.push_back(ritem(item::pos(i*bsize-size,j*bsize+bsize),size,size,type));
                    items.push_back(ritem(item::pos(i*bsize,j*bsize+bsize),size,size,type));
                    items.push_back(ritem(item::pos(i*bsize+size,j*bsize+bsize),size,size,type));
				case 0:
					items.push_back(ritem(item::pos(i*bsize,j*bsize),bsize,bsize,n));
				break;
				case 2:
				    printf("%d:pass\n",ii++);
				break;
			}
		}
	}
}
ritem::ritem(pos pos_, int lenth, int width,int type_):square(pos_,lenth,width),type(type_)
{
}
}
