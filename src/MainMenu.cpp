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
    backgroundTexture = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/bgmenu.png");
}

void MainMenu::Update()
{
    TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void MainMenu::Close()
{
    backgroundTexture = nullptr;
}
