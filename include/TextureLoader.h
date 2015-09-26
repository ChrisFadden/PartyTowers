#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <unordered_map>
#include <SDL_image.h>
#include <string>
#include <iostream>


class TextureLoader {
    private:
        static std::unordered_map<std::string, SDL_Texture*> imgs;
    public:
    TextureLoader();
    ~TextureLoader();
    SDL_Texture* loadImg(std::string name, SDL_Renderer* r);
    static TextureLoader& getInstance() {
        static TextureLoader tl;
        return tl;
    }
        
};


#endif
