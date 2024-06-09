#include "MainMenu.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
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
    SDL_Renderer* renderer = Engine::GetInstance().GetRenderer();
    backgroundTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/bgmenu.png");
    buttonPlayTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/button.png");
    buttonQuitTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/button.png");
}

void MainMenu::Update()
{
    SDL_Renderer* renderer = Engine::GetInstance().GetRenderer();
    TextureManager::GetInstance().ShowTexture(renderer, backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    TextureManager::GetInstance().ShowTexture(renderer, buttonPlayTexture, 200, 200, 120, 40);
    TextureManager::GetInstance().ShowTexture(renderer, buttonQuitTexture, 200, 250, 120, 40);
    TextureManager::GetInstance().RenderText(renderer, " Play", 250, 220, {255, 0, 0});
    TextureManager::GetInstance().RenderText(renderer, "Quit", 250, 270);
}

void MainMenu::Close()
{
    backgroundTexture = nullptr;
    buttonPlayTexture = nullptr;
    buttonQuitTexture = nullptr;
}
