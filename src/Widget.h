#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"

class Widget
{
public:

    Widget();
    ~Widget();
private:

protected:

    virtual void SetupPlayerInput(SDL_Event e) = 0;
    virtual void UpdateButtonsVisually() = 0;
public:

};


