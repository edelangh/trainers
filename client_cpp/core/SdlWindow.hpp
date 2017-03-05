
#pragma once

#include <SDL2/SDL.h>

class SdlWindow
{
    public:
        SdlWindow();
        ~SdlWindow();

    private:
        //The window we'll be rendering to
        SDL_Window*  _window;
        //The surface contained by the window
        SDL_Surface* _screenSurface;
};
