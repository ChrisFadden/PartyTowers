#include "TextureLoader.h"

std::unordered_map<std::string, SDL_Texture*> TextureLoader::imgs;

TextureLoader::TextureLoader() {
}

TextureLoader::~TextureLoader() {
}

SDL_Texture* TextureLoader::loadImg(std::string name, SDL_Renderer* r) {
    auto it = imgs.find(name);
    SDL_Texture* ret;
    if(it == imgs.end()) {
        //load img
        //std::cout << "NEW IMAGE BEING MADE!!!!\n";
        //std::cout << "File name: " << name << "\n";
        SDL_Surface* surface =  IMG_Load(name.c_str());
        ret = SDL_CreateTextureFromSurface(r, surface);
        imgs.emplace(name, ret);
    } else {
        //std::cout << "IMAGE ALREADY LOADED!\n";
        ret = it->second;
    }

    return ret;
}
