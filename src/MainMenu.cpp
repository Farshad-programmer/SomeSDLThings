#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "MainMenu.h"
#include "Engine.h"
#include "TextureManager.h"

MainMenu::MainMenu()
{
    CreateBackgroundMenu();
}

MainMenu::~MainMenu()
{
}

void MainMenu::CreateBackgroundMenu()
{
    SDL_Renderer *renderer = Engine::GetInstance().GetRenderer();
    backgroundTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/bgmenu.png");
    buttonUnhoveredTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/button.png");
    buttonHoveredTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/buttonHovered.png");
}

void MainMenu::SetupPlayerInput(SDL_Event e) // show and Update buttons effects
{
    if (e.type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > buttonPlayX && x < buttonPlayX + buttonPlayW &&
            y > buttonPlayY && y < buttonPlayY + buttonPlayH)
        {
            startButtonHovered = true;
            quitButtonHovered = false;
        }
        else if (x > buttonQuitX && x < buttonQuitX + buttonQuitW &&
                 y > buttonQuitY && y < buttonQuitY + buttonQuitH)
        {
            startButtonHovered = false;
            quitButtonHovered = true;
        }
        else
        {
            startButtonHovered = false;
            quitButtonHovered = false;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > buttonPlayX && x < buttonPlayX + buttonPlayW &&
            y > buttonPlayY && y < buttonPlayY + buttonPlayH)
        {
            std::cout << " Play button pressed" << std::endl;
        }
        else if (x > buttonQuitX && x < buttonQuitX + buttonQuitW &&
                 y > buttonQuitY && y < buttonQuitY + buttonQuitH)
        {
            std::cout << " Quit button pressed" << std::endl;
        }
    }
    else if (e.type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        if (x > buttonPlayX && x < buttonPlayX + buttonPlayW &&
            y > buttonPlayY && y < buttonPlayY + buttonPlayH)
        {
            std::cout << " Play button Released" << std::endl;
        }
        else if (x > buttonQuitX && x < buttonQuitX + buttonQuitW &&
                 y > buttonQuitY && y < buttonQuitY + buttonQuitH)
        {
            std::cout << " Quit button Released" << std::endl;
        }
    }

    UpdateButtonsVisually();
}

void MainMenu::UpdateButtonsVisually()
{
    SDL_Renderer *renderer = Engine::GetInstance().GetRenderer();
    if (startButtonHovered)
    {
        buttonPlayTexture = buttonHoveredTexture;
        buttonQuitTexture = buttonUnhoveredTexture;
        TextureManager::GetInstance().ShowTexture(renderer, buttonPlayTexture, 200, 200, 120, 40);
        TextureManager::GetInstance().ShowTexture(renderer, buttonQuitTexture, 200, 250, 120, 40);
    }
    else if (quitButtonHovered)
    {
        buttonQuitTexture = buttonHoveredTexture;
        buttonPlayTexture = buttonUnhoveredTexture;
        TextureManager::GetInstance().ShowTexture(renderer, buttonPlayTexture, 200, 200, 120, 40);
        TextureManager::GetInstance().ShowTexture(renderer, buttonQuitTexture, 200, 250, 120, 40);
    }
    else
    {
        buttonQuitTexture = buttonUnhoveredTexture;
        buttonPlayTexture = buttonUnhoveredTexture;
        TextureManager::GetInstance().ShowTexture(renderer, buttonPlayTexture, 200, 200, 120, 40);
        TextureManager::GetInstance().ShowTexture(renderer, buttonQuitTexture, 200, 250, 120, 40);
    }
}

void MainMenu::Update(SDL_Event e)
{
    SDL_Renderer *renderer = Engine::GetInstance().GetRenderer();

    // show background of the main menu
    TextureManager::GetInstance().ShowTexture(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // show main menu buttons
    SetupPlayerInput(e);

    // show main menu button texts
    TextureManager::GetInstance().RenderText(renderer, "GAME NAME", SCREEN_WIDTH / 2, 100, 130, {255, 0, 0});
    TextureManager::GetInstance().RenderText(renderer, " Play", 250, 220);
    TextureManager::GetInstance().RenderText(renderer, "Quit", 250, 270);
}

void MainMenu::Close()
{
    backgroundTexture = nullptr;
    buttonPlayTexture = nullptr;
    buttonQuitTexture = nullptr;
    buttonHoveredTexture = nullptr;
    buttonUnhoveredTexture = nullptr;
}
