
#include "SdlWindow.hpp"

#include "configs.h"
#include <stdio.h>

SdlWindow::SdlWindow()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        _window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( _window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            _screenSurface = SDL_GetWindowSurface( _window );

            //Fill the surface white
            SDL_FillRect( _screenSurface, NULL, SDL_MapRGB( _screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( _window );

            //Wait two seconds
            SDL_Delay( 2000 );
        }
    }
}

SdlWindow::~SdlWindow()
{
    //Destroy window
    SDL_DestroyWindow( _window );

    //Quit SDL subsystems
    SDL_Quit();
}
