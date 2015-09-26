#ifndef TEXT_H
#define TEXT_H

#include <SDL.h>
#include <string>

void drawString(std::string in, int x, int y);
void initFont();
void fontSetRenderer(SDL_Renderer* r);
void quitFont();

#endif
