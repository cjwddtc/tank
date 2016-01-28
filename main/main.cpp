#include <boost/filesystem.hpp>
#include <core/core.h>
#include <vector>
#include <windows.h>
#include <algorithm>
using boost::filesystem::path;
using namespace graphic;
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    main(0, 0);
}/*
int WinMain(int argc,char *argv[]){
    main(argc,argv);
}*/
bool key[256];
int SDL_main(int argc, char *argv[]) {
    core::engine a(path("config.xml"));
    //a.checker=new bumpchecker::bumpchecker(a.width,a.height);
    a.load_map(1);
    bool flag = true;
    SDL_Event ev;
    while (flag) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                flag = false;
                break;
            case SDL_KEYDOWN:
                key[ev.key.keysym.sym] = true;
                break;
            case SDL_KEYUP:
                key[ev.key.keysym.sym] = false;
                break;
            }
        }
        a.run();
        Sleep(100);
    }
    Showmanage::clear_Showmanage();
    return 0;
}
