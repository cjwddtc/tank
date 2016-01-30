#include "Showmanage.h"

namespace graphic
{
SDL_Renderer *Showmanage::gRenderer=0;
SDL_Window *Showmanage::gWindow=0;


bool Showmanage::load_from_file( std::string path,int x,int y)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    sonlenth=y;
    sonwidth=x;
    return mTexture != NULL;
}

void Showmanage::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        sonlenth=0;
        sonwidth=0;
        lenth=0;
        width=0;
    }
}

void Showmanage::render( int x, int y )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, sonlenth, sonwidth};
    SDL_Rect renderFrom = { width,lenth,sonwidth, sonlenth};
    SDL_RenderCopy( gRenderer, mTexture, &renderFrom, &renderQuad );
}

Showmanage::Showmanage()   //Initialize
{
    mTexture = NULL;
    sonlenth=0;
    sonwidth=0;
    lenth=0;
    width=0;
}
Showmanage::~Showmanage()   //Deallocate
{
    free();
}
bool Showmanage::init_Showmanage(int x,int y)
{

    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}
void Showmanage::clear_Showmanage()
{
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void Showmanage::update()
{
    SDL_RenderPresent( gRenderer );
    SDL_RenderFillRect(gRenderer,NULL);
}


Showmanage &Showmanageline::operator[](int x)
{
    lenth=x*sonlenth;
    return  *(Showmanage *)this;
}


Showmanageline &Showmanagemap::operator[](int y)
{
    width=y*sonwidth;
    return  *(Showmanageline *)this;
}
}
