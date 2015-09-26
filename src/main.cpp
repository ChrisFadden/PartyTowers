#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <MsgStruct.h>
#include "Player.h"
#include "GameObject.h"
#include "Cursor.h"
#include <unordered_map>

using namespace std;

int send(string);
int send(MsgStruct*, int);
int send(string, int);
MsgStruct* createMsgStruct(int, bool);
void setupMessages();
MsgStruct* newPacket(int);
bool canHandleMsg(bool);
MsgStruct* readPacket(bool);

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDLNet_SocketSet socketSet;
TCPsocket sock;

char buffer[512];
int bufferSize;

map<int, MsgStruct*> outMsgStructs;
map<int, MsgStruct*> inMsgStructs;

string roomCode;

vector<GameObject*> listObj;
unordered_map<int,Player*> listPlayers;
Level lvl1(640, 480);



//User IO functions to be called from networking code?
Player* getPlayerbyID(int id);
void addPlayerbyID(int id, SDL_Renderer* r);

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        std::cout << "ERROR, SDL_Init\n";
        return -1;
    }

    cout << "SDL2 loaded.\n";

    // The window we'll be rendering to
    SDL_Window* window = NULL;
    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    window = SDL_CreateWindow("Party Towers", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    int flag = IMG_INIT_PNG;
    if ((IMG_Init(flag)&flag) != flag) {
        std::cout << "Error, SDL_image!\n";
        return -1;
    }

    if (SDLNet_Init() == -1) {
        std::cout << "ERROR, SDLNet_Init\n";
        return -1;
    }

    std::cout << "SDL_net loaded.\n";

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

    setupMessages();

    send("TCP");

    bool waiting = true;
    while (waiting) {
        if (SDLNet_TCP_Recv(sock, buffer, 512) > 0) {
            waiting = false;
            if (string(buffer) == "1") {
                cout << "Handshake to server made.\n";
            }
        }
    }
    
    send("9990000");

    //Create Renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    printf("This is what happens when Marcus writes a renderer %s\n",SDL_GetError());
    if (renderer) {
        cout << "It works!\n";
    }

    //Testing Images
    Player p1(0, 0, 0, &lvl1);
    p1.loadImg(renderer);
    listPlayers.emplace(0,&p1);
    GameObject go1;
    go1.loadImg("./res/BaseTower.png", renderer);

    SDL_Event e;
    bool running = true;
    int k = 0;
    Uint32 ctime = SDL_GetTicks();
    int wave = 1;

    bool confirmed = false;

    while (running) {
        SDL_UpdateWindowSurface(window);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        int ready = SDLNet_CheckSockets(socketSet, 15);
        if (ready > 0 && SDLNet_SocketReady(sock)) {
            int s = SDLNet_TCP_Recv(sock, buffer+bufferSize, 512);
            if (s > 0) {
                bufferSize += s;
                /*               
                   cout << "\nData: \n";
                   cout << buffer;
                   cout << "\n"; 
                   */
                   
            }
        }

        if (canHandleMsg(confirmed)) {
            //cout << "We have a message!\n";
            MsgStruct* packet = readPacket(confirmed);
            int pID = packet->getPID();
            int msgID = packet->getMsgID();
            /*
            cout << "Player ID: ";
            cout << packet->getPID();
            cout << "\n";
            cout << "Msg ID: ";
            cout << msgID;
            cout << "\n";
            */
            if (msgID == 999) {
                confirmed = true;
                roomCode = packet->read();
                cout << "Room code: "+roomCode+"\n"; 
            } else if (msgID == 998) {
                cout << "New player!\n";
                addPlayerbyID(pID, renderer);
            } else if (msgID == 2) {
                string dir = packet->read();
                // We have pID and dir
                // dir is l, r, u, or d
                Player* p = getPlayerbyID(pID);
                if(dir == "l") {
                    p->moveLeft();
                } else if (dir == "r") {
                    p->moveRight();
                } else if (dir == "u") {
                    p->moveUp();
                } else if (dir == "d") {
                    p->moveDown();
                } else {
                    cout << "error, direction: " << dir << "\n";
                }
            } else if (msgID == 3) {
                string t = packet->read();
                MsgStruct* p = newPacket(3);
                p->write(t);
                send(p, pID);
            }
        }

        k +=1 ;
        if (SDL_GetTicks() - ctime > 1000) {
            //cout << k;
            k = 0;
            ctime = SDL_GetTicks();
            //cout << "\n";
        }

        //Drawing code
        SDL_RenderClear(renderer);
        //For each path item, draw
        //For each base tower, draw
        //For each object, get image, draw, SDL_RenderCopy
        SDL_Texture* t = go1.draw();
        SDL_Rect txr;
        //img position
        txr.x = 0;
        txr.y = 0;
        //img size
        txr.w = 32;
        txr.h = 32;
        //For each player, get cursor, draw
        for(auto it : listPlayers) {
            Player* p = it.second;
            pair<int,int>player_pos = p->getPos();
            txr.x = player_pos.first;
            txr.y = player_pos.second;
            SDL_Texture* t = p->getTexture();
            SDL_RenderCopy(renderer, t, NULL, &txr);
        }
        //SDL_RenderCopy(renderer, t, NULL, &txr);
        SDL_RenderPresent(renderer);

    }


    SDL_FreeSurface( screenSurface );
    SDL_DestroyWindow( window );

    SDLNet_TCP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}

void setupMessages() {
    MsgStruct* m1 = createMsgStruct(999, false);
    m1->addChars(4);

    MsgStruct* m998 = createMsgStruct(998, false);

    MsgStruct* m2 = createMsgStruct(2, false);
    m2->addChars(1);

    MsgStruct* m3 = createMsgStruct(3, false);
    m3->addChars(2);

    MsgStruct* o3 = createMsgStruct(3, true);
    o3->addChars(2);
}

bool canHandleMsg(bool confirmed) {
    if (bufferSize < 5) {
        return false;
    }
    string data = string(buffer);
    if (data.size() < 5) {
        return false;
    }
    //cout << "Handling message...\n";
    int offset = 2;
    if (confirmed) {
        offset += 2;
    }
    //cout << data + "\n";
    data = data.substr(offset);
    //cout << data + "\n";
    string rawMsgID = data.substr(0, 3);
    //cout << rawMsgID + "\n";
    int msgID = atoi(rawMsgID.c_str());
    if (inMsgStructs.find(msgID) != inMsgStructs.end()) {
        return inMsgStructs[msgID]->canHandle(data);
    }
    cout << "Message ID does not exist " + rawMsgID+ "\n";
    return false;
}

MsgStruct* readPacket(bool confirmed) {
    string data = string(buffer).substr(0,bufferSize);
    int offset = 2;
    if (confirmed) {
        offset += 2;
    }
    int msgID = atoi(data.substr(offset,3).c_str());
    return inMsgStructs[msgID]->fillFromData(confirmed);
}

MsgStruct* createMsgStruct(int msgID, bool outgoing) {
    MsgStruct* packet = new MsgStruct(msgID);
    if (outgoing) {
        outMsgStructs[msgID] = packet;
    } else {
        inMsgStructs[msgID] = packet;
    }
    return packet;
}

MsgStruct* newPacket(int msgID) {
    return outMsgStructs[msgID]->reset();
}

int send(string data) {
    send(data, 0);
}

int send(string data, int pID) {
    if (pID > 0) {
        data = extend(pID, 2) + data;
    }
    int len = data.size() + 1;
    int out = SDLNet_TCP_Send(sock, (void*)data.c_str(), len);
    if (out < len) {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    return 0;
}

int send(MsgStruct* packet, int pID) {
    send(packet->getData(), pID);
}


Player* getPlayerbyID(int id) {
    auto it = listPlayers.find(id);
    if(it != listPlayers.end()) {
        return it->second;
    }
    return nullptr;
}

void addPlayerbyID(int id, SDL_Renderer* r) {
    auto it = listPlayers.find(id);
    if(it == listPlayers.end()) {
        Player* p = new Player(id, 0, 0, &lvl1);
        p->loadImg(r);
        listPlayers.emplace(id, p);
    }
}
