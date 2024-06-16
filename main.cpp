#include <stdio.h>
#include "src/TextureManager.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>
#include <vector>
#include "src/Engine.h"
#include "src/MainMenu.h"

//-----------------
#undef main
//-----------------

#define WHITE            \
   {                     \
      255, 255, 255, 255 \
   }


bool quit = false;
SDL_Event e;

SDL_Texture *backgroundTexture = nullptr;
SDL_Texture *buttonPlay = nullptr;
SDL_Texture *buttonQuit = nullptr;

int main(int argc, char **argv)
{
   MainMenu* mainMenu = nullptr;
   if (!Engine::GetInstance().Init())
   {
      std::cerr << "something is wrong in initializing stuff in Init() function !\n";
   }
   else
   {

      //backgroundTexture = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/bgmenu.png");
      //buttonPlay = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/button.png");
      //buttonQuit = TextureManager::GetInstance().LoadTexture(Engine::GetInstance().GetRenderer(), "assets/button.png");
      mainMenu = new MainMenu();
      while (!quit)
      {
         while (SDL_PollEvent(&e) != 0)
         {
            if (e.type == SDL_QUIT)
            {
               quit = true;
            }
            //TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), backgroundTexture, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            //TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), buttonPlay, 200, 200, 120, 40);
            //TextureManager::GetInstance().ShowTexture(Engine::GetInstance().GetRenderer(), buttonQuit, 200, 250, 120, 40);
            mainMenu->Update(e);
         }

         // update Render
         Engine::GetInstance().Render();

         // Simulate slower frame rate
         // SDL_Delay(100); //Add 100ms delay per frame
      }
   }
   Engine::GetInstance().Close();
   delete mainMenu;
   mainMenu = nullptr;
   return 0;
}
