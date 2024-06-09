#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>
#include <string>

class TextureManager
{
public:
    static TextureManager& GetInstance() 
    {
        static TextureManager s_Instance;
        return s_Instance;
    }


    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path, const int totalFrames, const int textureFrameWidth, const int textureFrameHeight, SDL_Rect textureClips[]);

    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);

    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture, int& currentFrame, SDL_Rect* clips,int frameWidth, int frameHeight, const int totalFrames);

    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture, int& currentFrame,int frameWidth, int frameHeight, const int totalFrames);

    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture,int x, int y, int frameWidth, int frameHeight);

    void RenderText(SDL_Renderer *renderer, const char* text, int posX, int posY, SDL_Color textColor = {0, 0, 0});
private:
    TextureManager(){}
    ~TextureManager() {}



protected:

public:


};











// how make singelton with pointer:
// dont forget add this line in cpp:
//TextureManager* TextureManager::s_Instance = nullptr;


/*

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <iostream>
#include <string>

class TextureManager
{
public:
    static TextureManager* GetInstance() 
    {
        return s_Instance = (s_Instance != nullptr ? s_Instance : new TextureManager());
    }


    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path, const int totalFrames, const int textureFrameWidth, const int textureFrameHeight, SDL_Rect textureClips[]);
    SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture, int& currentFrame, SDL_Rect* clips,int frameWidth, int frameHeight, const int totalFrames);
    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture, int& currentFrame,int frameWidth, int frameHeight, const int totalFrames);
    void ShowTexture(SDL_Renderer* renderer, SDL_Texture* texture,int x, int y, int frameWidth, int frameHeight);
private:
    TextureManager(){}
    ~TextureManager() {}



    static TextureManager* s_Instance;

protected:

public:






*/


