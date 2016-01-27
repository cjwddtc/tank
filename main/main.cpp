#include <boost/filesystem.hpp>
#include <Showmanage/Showmanage.h>
using namespace graphic;
int WinMain(int argc,char *argv[]){
	main(argc,argv);
}

int main(int argc,char *argv[]){
	Showmanage::init_Showmanage(800,600);
	Showmanagemap a;
	a.load_from_file(boost::filesystem::path("graphics/enemy.bmp").string());
	a.set_size(28,28);
	a[2][2].render(0,0);
	Showmanage::update();
	Showmanage::loop();
	Showmanage::clear_Showmanage();
}