#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SDL_image.h>
#include <string>

class DrawableObject {
    public:
        DrawableObject(std::string fname, SDL_Renderer* r);
        ~DrawableObject();
        SDL_Texture* getTexture();
    private:
        SDL_Texture* img;
        SDL_Surface* surface;
};
#endif
