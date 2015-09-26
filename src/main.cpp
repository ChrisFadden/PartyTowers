#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <string>

using namespace std;

int send(string buffer);
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLNet_SocketSet socketSet;
TCPsocket sock;

int main() {
    std::cout << "HELLO PARTY TOWERS!!!!\n";
    if(SDL_Init( SDL_INIT_VIDEO ) == -1) {
        std::cout << "ERROR, SDL_Init\n";
        return -1;
    }

    //The window we'll be rendering to
    SDL_Window* window = NULL;        
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    window = SDL_CreateWindow( "Party Towers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    screenSurface = SDL_GetWindowSurface( window );

    if(SDLNet_Init() == -1) {
        std::cout << "ERROR, SDLNet_Init\n";
        return -1;
    }

    std::cout << "WOO SDL2_Net!!!!\n";

    IPaddress ip;

    if (SDLNet_ResolveHost(&ip, "localhost", atoi("8886")) < 0) {
        fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(sock = SDLNet_TCP_Open(&ip))) {
        fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    }

    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socketSet, sock);

    send("TCP");

    bool waiting = true;
    char buffer[512];
    while(waiting) {
        if (SDLNet_TCP_Recv(sock, buffer, 512) > 0) {
            waiting = false;
            cout << buffer;
        }
    }

    send("9990000");

    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

    SDL_Event e;
    bool running = true;
    int k = 0;
    Uint32 ctime = SDL_GetTicks();
    while (running) {
        SDL_UpdateWindowSurface( window );

        while (SDL_PollEvent( &e ) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        int ready = SDLNet_CheckSockets(socketSet, 1);
        if (ready > 0 && SDLNet_SocketReady(sock)) {
            if (SDLNet_TCP_Recv(sock, buffer, 512) > 0) {
                cout << "\nData: \n";
                cout << buffer;
                cout << "\n";
            }
        }

        k +=1 ;
        if (SDL_GetTicks() - ctime > 1000) {
            cout << k;
            k = 0;
            ctime = SDL_GetTicks();
            cout << "\n";
        }
    }
 
    SDL_FreeSurface( screenSurface );
    SDL_DestroyWindow( window );

    SDLNet_TCP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}

int send(string buffer) {
    int len = buffer.size() + 1;
    int out = SDLNet_TCP_Send(sock, (void *)buffer.c_str(), len);
    if (out < len) {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    return 0;
}
