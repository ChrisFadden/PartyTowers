#include <SDL_ttf.h>
#include "Text.h"
#include <iostream>

TTF_Font* font = nullptr;
SDL_Renderer* fontrenderer = nullptr;



void drawString(std::string in, int x, int y) {
    SDL_Color color={255,255,255};
    SDL_Surface* text_surface;
    SDL_Texture* tx;
    SDL_Rect txr;
    txr.x = x;
    txr.y = y;
    txr.h = 32;
    txr.w = in.length()*16;
    text_surface = TTF_RenderText_Solid(font, in.c_str(), color);
    tx = SDL_CreateTextureFromSurface(fontrenderer, text_surface);
    SDL_RenderCopy(fontrenderer, tx, NULL, &txr);
    SDL_FreeSurface(text_surface); 
    SDL_DestroyTexture(tx);
}

void initFont() {
    if(TTF_Init() == -1) {
        std::cout << "Error, no font rendering will work. Haha!\n";
    }

    font = TTF_OpenFont("./res/FiraSans-Medium.ttf",16);
}

void fontSetRenderer(SDL_Renderer* r) {
    fontrenderer = r;
}

void quitFont() {
    
    TTF_Quit();
}
