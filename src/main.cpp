#include <iostream>
#include <SDL2/SDL_net.h>

int main() {
    std::cout << "HELLO PARTY TOWERS!!!!\n";
    if(SDL_Init(0) == -1) {
        std::cout << "ERROR, SDL_Init\n";
        return -1;
    }

    if(SDLNet_Init() == -1) {
        std::cout << "ERROR, SDLNet_Init\n";
        return -1;
    }

    std::cout << "WOO SDL2_Net!!!!\n";
    return 0;
}
