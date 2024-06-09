#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Engine.h"
#include <iostream>
#include <string>

bool Engine::Init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL could not initialized!" << SDL_GetError() << std::endl;
        success = false;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cerr << "SDL_image could not initialized!" << IMG_GetError() << std::endl;
        success = false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! TTF Error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_WAVPACK) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! Mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Open audio device
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not open audio! Mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Allocate 16 mixing channels
    Mix_AllocateChannels(16);

    Engine &instance = Engine::GetInstance();
    instance.GetInstance().m_GameState = EGS_MainMenu;

    instance.m_Window = SDL_CreateWindow("Unknown!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (instance.m_Window == nullptr)
    {
        std::cerr << "window not created!" << SDL_GetError() << std::endl;
        success = false;
    }

    instance.m_Renderer = SDL_CreateRenderer(instance.m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (instance.m_Renderer == nullptr)
    {
        std::cerr << "renderer not created!" << SDL_GetError() << std::endl;
        success = false;
    }

    int fontSize = int(instance.m_FontSize);
    instance.m_GameplayFont = TTF_OpenFont("assets/fonts/lazy.ttf", fontSize);
    if (instance.m_GameplayFont == nullptr)
    {
        std::cerr << "Failed to load gameplayfont! TTF Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    return success;
}

void Engine::Close()
{
    Engine &instance = Engine::GetInstance();
    SDL_DestroyRenderer(instance.m_Renderer);
    SDL_DestroyWindow(instance.m_Window);
    TTF_CloseFont(instance.m_GameplayFont);

    instance.m_Renderer = nullptr;
    instance.m_Window = nullptr;
    instance.m_GameplayFont = nullptr;

    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void Engine::Update()
{

}

void Engine::Render()
{
    SDL_RenderPresent(m_Renderer);
}

void Engine::GetCurrentMousePosition(int &x, int &y)
{
    SDL_GetMouseState(&x, &y);
}

void Engine::RenderDefaultScreenColor()
{
    SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(Engine::GetInstance().GetRenderer());
}

void Engine::SetFontSize(int newFontSize)
{
    Engine &instance = Engine::GetInstance();
    instance.m_GameplayFont = TTF_OpenFont("assets/fonts/lazy.ttf", newFontSize);
}
