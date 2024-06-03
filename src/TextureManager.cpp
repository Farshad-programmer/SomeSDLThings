#include "TextureManager.h"


//this is usable for sprite sheet animation texture
SDL_Texture *TextureManager::LoadTexture(SDL_Renderer* renderer, std::string path, const int totalFrames, const int textureFrameWidth, const int textureFrameHeight, SDL_Rect textureClips[])
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
SDL_Texture *TextureManager::LoadTexture(SDL_Renderer *renderer, std::string path)
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
void TextureManager::ShowTexture(SDL_Renderer* renderer, SDL_Texture *texture, int &currentFrame, SDL_Rect *clips, int frameWidth, int frameHeight, const int totalFrames)
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
void TextureManager::ShowTexture(SDL_Renderer *renderer, SDL_Texture *texture, int &currentFrame, int frameWidth, int frameHeight, const int totalFrames)
{
    SDL_Rect renderQuad = { 300, 300, frameWidth, frameHeight };
   SDL_RenderCopy(renderer,texture,nullptr, &renderQuad);

   currentFrame++;
   if((currentFrame / (totalFrames*2)) >= totalFrames)
   {
      currentFrame = 0;
   }
}

// this is good for showing a normal texture
void TextureManager::ShowTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int frameWidth, int frameHeight)
{
   SDL_Rect renderQuad = { x, y, frameWidth, frameHeight };
   SDL_RenderCopy(renderer,texture,nullptr, &renderQuad);
}
