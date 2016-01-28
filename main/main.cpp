#include <boost/filesystem.hpp>
#include <Showmanage/Showmanage.h>
#include <core/core_show.h>
#include <vector>
#include <windows.h>
#include <algorithm>
using boost::filesystem::path;
using namespace graphic;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
    main(0,0);
}/*
int WinMain(int argc,char *argv[]){
	main(argc,argv);
}*/
bool show(core::show_manager &b){
    for(Show *a:b.vec) a->show();
    return false;
}
int SDL_main(int argc,char *argv[]){
	core::map_manager a(path("config.xml"));
	core::show_manager b(path("config.xml"));
	std::vector<core::ritem> vec;
	a.read_map(1,vec);
	b.create_show(vec);
	bool flag=true;
	SDL_Event ev;
	std::reverse(b.vec.begin(),b.vec.end());
	//b.map[1][0][0].render(0,0);
	while(flag){
        while(SDL_PollEvent(&ev)){
            if(ev.type==SDL_QUIT){
                flag=false;
            }
        }
        for(Show *a:b.vec){
            a->show();
        }
        b.vec.pop_back();
        Showmanage::update();
        Sleep(100);
	}
	Showmanage::clear_Showmanage();
    return 0;
}
