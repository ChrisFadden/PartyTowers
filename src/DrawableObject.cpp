#include "DrawableObject.h"

DrawableObject::DrawableObject(std::string filename, SDL_Renderer* r) {
   surface =  IMG_Load(filename.c_str());
   img = SDL_CreateTextureFromSurface(r, surface);
}



DrawableObject::~DrawableObject() {
}


SDL_Texture* DrawableObject::getTexture() {
    return img;
}
