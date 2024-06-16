#pragma once

#include "SDL_ttf.h"

enum EGameState
{
    EGS_MainMenu,
    EGS_Gameplay,
    EGS_PauseMenu,

    EGS_DefaultMax
};

class SDL_Renderer;
class SDL_Window;

class Engine
{
public:
    static Engine& GetInstance()
    {
        static Engine s_Instance;
        return s_Instance;
    }

    // static functions 
    static bool Init();
    static void Close();

    void Update();
    void Render();

    void GetCurrentMousePosition(int &x, int &y);
    void RenderDefaultScreenColor();

    void SetFontSize(int newFontSize);

    

private:
    Engine(){}
    ~Engine(){}

    #define SCREEN_WIDTH 1260
    #define SCREEN_HEIGHT 800


    SDL_Renderer* m_Renderer = nullptr;
    SDL_Window* m_Window = nullptr;
    TTF_Font* m_GameplayFont = nullptr;
    EGameState m_GameState;
    int m_FontSize = 28;
protected:

public:
    inline SDL_Renderer* GetRenderer() const {return m_Renderer;}
    inline SDL_Window* GetWindow() const {return m_Window;}
    inline TTF_Font* GetGameplayFont() const {return m_GameplayFont;}
    inline int GetFontSize() const {return m_FontSize;}
};