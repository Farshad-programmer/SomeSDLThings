#pragma once
#include "Widget.h"

class MainMenu:public Widget
{

public:
    MainMenu();
    ~MainMenu();

    void Update(SDL_Event e);
    void Close();
private:
    void CreateBackgroundMenu();
    
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* buttonPlayTexture = nullptr;
    SDL_Texture* buttonQuitTexture = nullptr;
    SDL_Texture* buttonHoveredTexture = nullptr;
    SDL_Texture* buttonUnhoveredTexture = nullptr;

    int buttonPlayX = 200;
    int buttonPlayY = 200;
    int buttonPlayW = 120;
    int buttonPlayH = 40;

    int buttonQuitX = 200;
    int buttonQuitY = 250;
    int buttonQuitW = 120;
    int buttonQuitH = 40;

    bool startButtonHovered = false;
    bool quitButtonHovered = false;
protected:
    virtual void SetupPlayerInput(SDL_Event e)override;
    virtual void UpdateButtonsVisually() override;
public:

};


