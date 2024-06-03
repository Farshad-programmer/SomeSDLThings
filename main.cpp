#include <stdio.h>
#include "src/TextureManager.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<array>
#include <vector>

//-----------------
#undef main
//-----------------

// global variables
#define SCREEN_WIDTH 1260
#define SCREEN_HEIGHT 800
#define WHITE {255, 255, 255, 255}
#define RED {255, 0, 0, 255}
#define BLUE {0, 0, 255, 255}
#define BLACK {0, 0, 0, 255}
SDL_Renderer* renderer = nullptr;
SDL_Window* window = nullptr;
bool quit = false;
SDL_Event e;
TTF_Font* gameplayFont = nullptr;


int mouseX;
int mouseY;

SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* buttonPlay = nullptr;

// global functions
bool Init()
{
   bool success = true;

   if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
   {
      std::cerr << "SDL could not initialized!" << SDL_GetError() << std::endl;
      success = false;
   } 
   if(IMG_Init(IMG_INIT_PNG) < 0)
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

   window = SDL_CreateWindow("Unknown!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   if(window == nullptr)
   {
      std::cerr << "window not created!" << SDL_GetError() << std::endl;
      success = false;
   } 

   renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if(renderer == nullptr)
   {
      std::cerr << "renderer not created!" << SDL_GetError() << std::endl;
      success = false;
   } 

   gameplayFont = TTF_OpenFont("assets/fonts/lazy.ttf", 28);
   if(gameplayFont == nullptr)
   {
      std::cerr << "Failed to load gameplayfont! TTF Error: " << TTF_GetError() << std::endl;
      success = false;
   }

   return success;
}


void GetCurrentMousePosition(int& x, int& y)
{
   SDL_GetMouseState(&x, &y);
}

void Close()
{
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   TTF_CloseFont(gameplayFont);


   gameplayFont = nullptr;
   renderer = nullptr;
   window = nullptr;

   SDL_Quit();
   TTF_Quit();
   IMG_Quit();
}

void RenderDefaultScreenColor()
{
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
   SDL_RenderClear(renderer);
}


int main(int argc, char **argv)
{
   if(!Init())
   {
      std::cerr << "something is wrong in initializing stuff in Init() function !\n";
   }
   else
   {
       backgroundTexture = TextureManager::GetInstance().LoadTexture(renderer, "assets/bgmenu.png");
       buttonPlay = TextureManager::GetInstance().LoadTexture(renderer, "assets/button.png");
      while (!quit)
      {
         while (SDL_PollEvent(&e) != 0)
         {
            if(e.type == SDL_QUIT)
            {
               quit = true;
            }
            TextureManager::GetInstance().ShowTexture(renderer,backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            TextureManager::GetInstance().ShowTexture(renderer,buttonPlay, 200, 200, 120, 40);
         }
         

         // update Render
         SDL_RenderPresent(renderer);

         // Simulate slower frame rate
         //SDL_Delay(100); //Add 100ms delay per frame
      }
   }
   Close();
   return 0 ;  
}












// GetCurrentMousePosition(mouseX, mouseY);
// for(auto& var : rectArray)
// {
//    if(mouseX < var->x || mouseX > var->x + var->w )
//    {

//    }
//    else if (mouseY < var->y || mouseY > var->y + var->h)
//    {
      
//    }
//    else
//    {
//       rectRef = var;
//       break;
//    }
// }