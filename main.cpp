#include <iostream>
#include <string>
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
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
std::vector<SDL_Rect*>rectArray;
SDL_Rect* rectRef = nullptr;
bool isHoldingMouse{false};
bool bCanDestroyObject{false};



int mouseX;
int mouseY;

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

//this is usable for sprite sheet animation texture
SDL_Texture* LoadTexture(std::string path, const int totalFrames, const int textureFrameWidth, const int textureFrameHeight, SDL_Rect textureClips[])
{
   SDL_Texture* newTexture = nullptr;
   SDL_Surface* newSurface = IMG_Load(path.c_str());
   if(newSurface == nullptr)
   {
      std::cerr << "Failed to load texture! IMG Error: " << SDL_GetError() << std::endl;
   }
   else
   {
      newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
      if(newTexture == nullptr)
      {
         std::cerr << "Failed to create texture rom surface! SDL Error: " << SDL_GetError() << std::endl;
      }
      else
      {
         for (size_t i = 0; i < totalFrames; ++i)
         {
            textureClips[i].x = 0; 
            textureClips[i].y = i * textureFrameHeight / 3;
            textureClips[i].w = textureFrameWidth;
            textureClips[i].h = textureFrameHeight / 3;
         }
      }
      SDL_FreeSurface(newSurface);
   }
   
   return newTexture;
}

// this is good for individual animation texture
SDL_Texture* LoadTexture(std::string path)
{
   SDL_Texture* newTexture = nullptr;
   SDL_Surface* newSurface = IMG_Load(path.c_str());
   if(newSurface == nullptr)
   {
      std::cerr << "Failed to load texture! IMG Error: " << SDL_GetError() << std::endl;
   }
   else
   {
      newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
      if(newTexture == nullptr)
      {
         std::cerr << "Failed to create texture rom surface! SDL Error: " << SDL_GetError() << std::endl;
      }
      SDL_FreeSurface(newSurface);
   }
   return newTexture;
}

//this is usable for sprite sheet animation texture
void ShowTexture(SDL_Texture* texture, int& currentFrame, SDL_Rect* clips,int frameWidth, int frameHeight, const int totalFrames)
{
   SDL_Rect*  currentClip = &clips[currentFrame / 6];
   SDL_Rect renderQuad = { 100, 100, frameWidth, frameHeight };

   SDL_RenderCopy(renderer,texture,currentClip, &renderQuad);

   currentFrame++;
   if((currentFrame /6 ) >= totalFrames)
   {
      currentFrame = 0;
   }
  
}

// this is good for individual animation texture
void ShowTexture(SDL_Texture* texture, int& currentFrame,int frameWidth, int frameHeight, const int totalFrames) 
{
   SDL_Rect renderQuad = { 300, 300, frameWidth, frameHeight };
   SDL_RenderCopy(renderer,texture,nullptr, &renderQuad);

   currentFrame++;
   if((currentFrame / (totalFrames*2)) >= totalFrames)
   {
      currentFrame = 0;
   }
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

   delete rectRef;
   rectRef = nullptr;
   
   for (auto rect : rectArray)
    {
        delete rect;
    }
    rectArray.clear();



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
      while (!quit)
      {
         while (SDL_PollEvent(&e) != 0)
         {
            if(e.type == SDL_QUIT)
            {
               quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
               if(e.button.button == SDL_BUTTON_LEFT)
               {
                  GetCurrentMousePosition(mouseX, mouseY);
                  isHoldingMouse = true;
                  SDL_Rect* rectTemp = new SDL_Rect{mouseX, mouseY, 50, 50};
                  bool intersected = false;
                  for (size_t i = 0; i < rectArray.size(); ++i)
                  {
                     if (SDL_HasIntersection(rectTemp, rectArray[i]))
                     {
                        intersected = true;
                        rectRef = rectArray[i];
                        delete rectTemp;
                        rectTemp = nullptr;
                        break;
                     }
                  }          
                  if (!intersected)
                  {
                     rectRef = rectTemp;
                     rectArray.push_back(rectRef);
                  }
                  
               }
               else if (e.button.button == SDL_BUTTON_RIGHT)
               {
                  isHoldingMouse = false;
                  if (rectRef && bCanDestroyObject)
                  {
                     auto it = rectArray.begin();
                     while (it != rectArray.end())
                     {
                        if (*it == rectRef)
                        {
                           delete *it;
                           it = rectArray.erase(it);
                           rectRef = nullptr;
                        }
                        else
                        {
                           ++it;
                        }
                     }
                  }
               }
            }
            else if (e.type == SDL_MOUSEBUTTONUP)
            {
               isHoldingMouse = false;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
               if(!isHoldingMouse)
               {
                  GetCurrentMousePosition(mouseX, mouseY);
                  for(auto rect : rectArray)
                  {  
                     if (rect->x < mouseX && rect->w + rect->x > mouseX && rect->y < mouseY && rect->h + rect->y > mouseY)
                     {
                        rectRef = rect;
                        bCanDestroyObject = true;
                        break;
                     }
                     else
                     {
                        bCanDestroyObject = false;
                     }
                     
                  }
                 
               }
            }
         }

         RenderDefaultScreenColor(); 

         if(rectRef)
         {
            if(isHoldingMouse)
            {
               GetCurrentMousePosition(mouseX, mouseY);
               rectRef->x = mouseX;
               rectRef->y = mouseY;
               //std::cout << " x value : " << testRect->x << " and y value : " << testRect->y << std::endl;
            }
         }

         // draw rectangle
         if(!rectArray.empty())
         {
            for (auto& rect : rectArray)
            {
               SDL_SetRenderDrawColor(renderer, 10, 56, 255, 255);
               SDL_RenderFillRect(renderer, rect);
            }
         }
         // update Render
         SDL_RenderPresent(renderer);
         std::cout << " array size : " << rectArray.size() << std::endl;

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