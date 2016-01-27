#include <boost/filesystem.hpp>
#include <Showmanage/Showmanage.h>
#include <core/core_show.h>
#include <vector>
using boost::filesystem::path;
using namespace graphic;
int WinMain(int argc,char *argv[]){
	main(argc,argv);
}

int main(int argc,char *argv[]){
	core::map_manager a(path("config.ini"));
	core::show_manager b(path("config.ini"));
	std::vector<core::ritem> vec;
	a.read_map(1,vec);
	b.create_show(vec);
	Showmanage::loop();
	Showmanage::clear_Showmanage();
}