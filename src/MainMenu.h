#pragma once
#include "Widget.h"

class SDL_Texture;
class MainMenu:public Widget
{

public:
    MainMenu();
    ~MainMenu();

    void Update();
    void Close();
private:
    void CreateBackgroundMenu();
    
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* buttonPlayTexture = nullptr;
    SDL_Texture* buttonQuitTexture = nullptr;
public:

};


