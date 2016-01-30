#ifndef SHOWMANAGE_H
#define SHOWMANAGE_H
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <functional>
namespace graphic
{
//Texture wrapper class
class Showmanage
{
protected:
    //Initializes variables
    Showmanage();
    //Deallocates memory
    ~Showmanage();
public:
    //Loads image at specified path
    bool load_from_file( std::string path,int x,int y);
    //Deallocates texture
    void free();
    //Renders texture at given point
    void render( int x, int y );
    Showmanage(const Showmanage&)=delete;
    Showmanage& operator=(const Showmanage&)=delete;

    static SDL_Renderer *gRenderer;
    static SDL_Window* gWindow;
    static bool init_Showmanage(int x,int y);
    static void clear_Showmanage();
    static void update();
protected:
    //The actual hardware texture
    SDL_Texture* mTexture;
    int sonlenth;
    int lenth;
    int sonwidth;
    int width;
};


class Showmanageline:public Showmanage
{
public:
    Showmanage &operator[](int x);
};

class Showmanagemap:public Showmanage
{
public:
    Showmanageline &operator[](int y);
};
}
#endif
