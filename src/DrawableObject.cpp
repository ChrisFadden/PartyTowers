#include <iostream>
#include "DrawableObject.h"
#include "TextureLoader.h"

DrawableObject::DrawableObject(std::string filename, SDL_Renderer* r) {
    img = TextureLoader::getInstance().loadImg(filename, r);
}



DrawableObject::~DrawableObject() {
}


SDL_Texture* DrawableObject::getTexture() {
    return img;
}
