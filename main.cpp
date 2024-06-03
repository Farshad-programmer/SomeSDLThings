#include <stdio.h>
#include "src/TextureManager.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
#include "src/Engine.h"

//-----------------
#undef main
//-----------------

// global variables

#define WHITE            \
   {                     \
      255, 255, 255, 255 \
   }
#define RED          \
   {                 \
      255, 0, 0, 255 \
   }
#define BLUE         \
   {                 \
      0, 0, 255, 255 \
   }
#define BLACK      \
   {               \
      0, 0, 0, 255 \
   }

bool quit = false;
SDL_Event e;

int mouseX;
int mouseY;

SDL_Texture *backgroundTexture = nullptr;
SDL_Texture *buttonPlay = nullptr;

// global functions

void GetCurrentMousePosition(int &x, int &y)
{
   SDL_GetMouseState(&x, &y);
}


void RenderDefaultScreenColor()
{
   SDL_SetRenderDrawColor(Engine::GetInstance().GetRenderer(), 0, 0, 0, 255);
   SDL_RenderClear(Engine::GetInstance().GetRenderer());
}

int main(int argc, char **argv)
{
   if (!Engine::GetInstance().Init())
   {
      std::cerr << "something is wrong in initializing stuff in Init() function !\n";
   }
   else
   {

      backgroundTexture = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/bgmenu.png");
      buttonPlay = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/button.png");
      while (!quit)
      {
         while (SDL_PollEvent(&e) != 0)
         {
            if (e.type == SDL_QUIT)
            {
               quit = true;
            }
            TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), buttonPlay, 200, 200, 120, 40);
         }

         // update Render
         SDL_RenderPresent(Engine::GetInstance().GetRenderer());

         // Simulate slower frame rate
         // SDL_Delay(100); //Add 100ms delay per frame
      }
   }
   Engine::GetInstance().Close();
   return 0;
}
