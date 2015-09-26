#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <MsgStruct.h>
#include "Player.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Cursor.h"
#include "Tower.h"
#include "Cannon.h"
#include "Rocket.h"
#include "Path.h"
#include "Soldier.h"
#include "Sound.h"
#include "Bullet.h"
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
void drawPath(Path*, SDL_Renderer*);

Player* getPlayerbyID(string);

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

SDLNet_SocketSet socketSet;
TCPsocket sock;

char buffer[512];
char tempBuffer[512];
int bufferSize;

map<int, MsgStruct*> outMsgStructs;
map<int, MsgStruct*> inMsgStructs;

string roomCode;

vector<Tower*> listTower;
vector<Enemy*> listEnemy;
vector<GameObject*> listFloors;
vector<Bullet*> listBullet;
unordered_map<int, Player*> listPlayers;
Level lvl1(1280, 720);

// User IO functions to be called from networking code?
Player* getPlayerbyID(int id);
void addPlayerbyID(int id, SDL_Renderer* r);
void addTower(int id, int type, SDL_Renderer* r);

int init();

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) || SDL_Init(SDL_INIT_AUDIO) == -1) {
        std::cout << "SDL_Init: " << SDLNet_GetError() << "\n";
        return -1;
    }

    cout << "SDL2 loaded.\n";

    GameSound game_audio;

    game_audio.PlaySound("./res/BackgroundMusic.wav"); 
    // The window we'll be rendering to
    SDL_Window* window = NULL;
    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    window = SDL_CreateWindow("Party Towers", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
            SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(init() == -1) {
        std::cout << "Quitting\n";
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

    // Create Renderer
    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    SDL_Event e;
    bool running = true;
    int k = 0;
    Uint32 ctime = SDL_GetTicks();
    int wave = 1;

    bool confirmed = false;


    Path* path = new Path();
    path->addDest(0,0);
    path->addDest(32,0);
    path->addDest(32,128);
    path->addDest(64,128);
    path->addDest(64,512);
    drawPath(path, renderer);

    Path* path2 = new Path();
    path2 -> addDest(1280-32,0);
    path2 -> addDest(1280-32,128);
    path2 -> addDest(1280-512,128);
    path2 -> addDest(1280-512,512);
    path2 -> addDest(64, 512);
    drawPath(path2, renderer);

    lvl1.addPath(path);
    //lvl1.addPath(path2);

    for (auto floor : listFloors) {
        lvl1.addGameObject(floor);
    }


    int enemyRegen = 5 * 60;
    int enemySpawn = 20 * 60;
    game_audio.PlaySound("./res/Wilhelm.wav"); 
    while (running) {
        SDL_UpdateWindowSurface(window);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        int ready = SDLNet_CheckSockets(socketSet, 15);
        if (ready > 0 && SDLNet_SocketReady(sock)) {
            int s = SDLNet_TCP_Recv(sock, tempBuffer, 512);
            for (int i=0; i<s-2; i++) {
                buffer[bufferSize + i] = tempBuffer[i+2];
            }
            if (s > 1) {
                bufferSize += s-2;
            }
        }

        if (canHandleMsg(confirmed)) {
            MsgStruct* packet = readPacket(confirmed);
            int pID = packet->getPID();
            int msgID = packet->getMsgID();

            if (msgID == 999) {
                confirmed = true;
                roomCode = packet->read();
                cout << "Room code: " + roomCode + "\n";
            } else if (msgID == 998) {
                cout << "New player!\n";
                addPlayerbyID(pID, renderer);
                MsgStruct* p2 = newPacket(5);
                p2->write(to_string(getPlayerbyID(pID)->getMoney()));
                send(p2, pID);

            } else if (msgID == 2) {
                string dir = packet->read();
                // We have pID and dir
                Player* p = getPlayerbyID(pID);
                if (dir == "l") {
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
                MsgStruct* p = newPacket(3);
                // Can I place a tower here? 1 yes, 0 no
                Player* player = getPlayerbyID(pID);
                auto player_pos = player->getPos();
                if(lvl1.spotOpen(player_pos.first, player_pos.second)) {
                    //std::cout << "Spot" << player_pos.first <<" " <<player_pos.second << "open\n";
                    p->write("1");
                } else {
                    //std::cout << "Spot" << player_pos.first <<" " <<player_pos.second << "closed\n";
                    p->write("0");
                }
                send(p, pID);
            } else if (msgID == 4) {
                int towerType = packet->readInt();
                //cout << "Placing a tower.\n";
                // Attempt to place towerType
                // here
                string out = "1";
				if ( towerType == 1) {
					if ( (getPlayerbyID(pID)->getMoney()) >= 50) {
                		addTower(pID, towerType, renderer);
						getPlayerbyID(pID)->addMoney(-50);
					} else { 
						out = "0";
					}					
				} else {
					if ( (getPlayerbyID(pID)->getMoney()) >= 100) {
							addTower(pID, towerType, renderer);
							getPlayerbyID(pID)->addMoney(-100);
					} else {
						out = "0";
					}
				}


                MsgStruct* p = newPacket(4);
                // Write success
                p->write(out);
                send(p, pID);

                MsgStruct* p2 = newPacket(5);
                p2->write(to_string(getPlayerbyID(pID)->getMoney()));
                send(p2, pID);
            } else if (msgID == 10) {
                string name = packet->read();
                getPlayerbyID(pID)->setName(name);
            }
        }

        k += 1;
        if (SDL_GetTicks() - ctime > 1000) {
            // cout << k;
            k = 0;
            ctime = SDL_GetTicks();
            // cout << "\n";
        }

        if (enemySpawn < 0) {
            //cout << "New enemy\n";
            Soldier* soldier = new Soldier(1, 0, 0);
            soldier->loadImg(renderer);
            listEnemy.push_back(soldier);
            int num = rand() % lvl1.getNumPaths();
            soldier->setPath(lvl1.getPath(num));
            enemySpawn = enemyRegen;
        } else {
            enemySpawn -= 1;
        }


        /***************
         * Aiming Code
         **************/
        Enemy* attacked = nullptr;
        int r, radius;
        int radiusAttacked = 10000;
        for (auto t : listTower) {
            t->update();
            if (!(t->canFire())) {
                continue;
            }
            for (auto e : listEnemy) {
                r = t->getRange();
                auto tpair = t->getPosition();
                auto epair = e->getPosition();
                radius = sqrt((epair.first - tpair.first) *
                        (epair.first - tpair.first) +
                        (epair.second - tpair.second) *
                        (epair.second - tpair.second));
                if(radius < r && radius < radiusAttacked) {
                    radiusAttacked = radius;
                    attacked = e;
                }
            }  // end of enemy loop
            if (attacked) {
                //cout << "Hit the enemy!\n";
                Bullet* bullet = new Bullet(t->getPlayer(), attacked, t->getPower());
                bullet->setPosition(t->getPosition());
                bullet->loadImg(renderer);
                listBullet.push_back(bullet);
                t->reloadTower();
            }
        }  // end of tower loop


        // Drawing code
        SDL_RenderClear(renderer);
        SDL_Rect txr;
        // img size
        txr.w = 32;
        txr.h = 32;
        // For each path item, draw
        // For each base tower, draw

        for (auto it : listFloors) {
            GameObject* f = it;
            pair<int, int> floor_pos = f->getPosition();
            txr.x = floor_pos.first;
            txr.y = floor_pos.second;
            SDL_Texture* tx = f->draw();
            if(!tx) {
                std::cout << "Error, tx is NULL";
            }
            SDL_RenderCopy(renderer, tx, NULL, &txr);
        }

        for (auto it : listTower) {
            Tower* t = it;
            pair<int, int> tower_pos = t->getPosition();
            txr.x = tower_pos.first;
            txr.y = tower_pos.second;
            SDL_Texture* tx = t->draw();
            if(!tx) {
                std::cout << "Error, tx is NULL";
            }
            SDL_RenderCopy(renderer, tx, NULL, &txr);
        }

        vector<int> toRemove;

        int tCount = -1;
        for (auto e : listEnemy) {
            tCount += 1;
            e->move();
            if (!(e->getAlive())) {
                toRemove.push_back(tCount);
                continue;
            }
            pair<int, int> e_pos = e->getPosition();
            txr.x = e_pos.first;
            txr.y = e_pos.second;
            SDL_Texture* tx = e->draw();
            if (!tx) {
                cout << "Error, tx is NULL";
            }
            SDL_RenderCopy(renderer, tx, NULL, &txr);
        }

        txr.w = 16;
        txr.h = 16;
        vector<int> toRemove2;
        int bCount = -1;
        for (auto it : listBullet) {
            bCount += 1;
            Bullet* b = it;
            if (b->move()) {
                Enemy* attacked = b->getTarget();
                attacked->setHealth(attacked->getHealth() - b->getPower());
                b -> getSource()->addMoney(5);
                if (attacked->getHealth() <= 0) {
                    b->getSource()->addMoney(attacked->getMoney());
                    attacked->setAlive(false);
                }
                toRemove2.push_back(bCount);
                MsgStruct* p = newPacket(5);
                p->write(to_string(b->getSource()->getMoney()));
                send(p, b->getSource()->getPlayerID());            

                continue; 
            }
            pair<int, int> bullet_pos = b->getPosition();
            txr.x = bullet_pos.first;
            txr.y = bullet_pos.second;
            SDL_Texture* tx = b->draw();
            if(!tx) {
                std::cout << "Error, tx is NULL";
            }
            SDL_RenderCopy(renderer, tx, NULL, &txr);
        }

        txr.w = 32;
        txr.h = 32;

        // For each player, get cursor, draw
        for (auto it : listPlayers) {
            Player* p = it.second;
            pair<int, int> player_pos = p->getPos();
            txr.x = player_pos.first;
            txr.y = player_pos.second;
            SDL_Texture* t = p->getTexture();
            SDL_RenderCopy(renderer, t, NULL, &txr);
        }

        for (auto i : toRemove) {
            delete(listEnemy.at(i));
            listEnemy.erase(listEnemy.begin() + i);
        }

        for (auto i: toRemove2) {
            delete(listBullet.at(i));
            listBullet.erase(listBullet.begin() + i);
        }

        // SDL_RenderCopy(renderer, t, NULL, &txr);
        SDL_RenderPresent(renderer);
    }

    SDL_FreeSurface(screenSurface);
    SDL_DestroyWindow(window);

    SDLNet_TCP_Close(sock);
    SDLNet_Quit();
    SDL_Quit();

    return 0;
}

void drawPath(Path* path, SDL_Renderer* renderer) {
    int stage = 0;
    pair<int,int> walker = path->getDest(stage);
    stage += 1;
    while (stage < path->length()) {
        GameObject* obj = new GameObject();
        obj->setPos(walker.first, walker.second);
        obj->loadImg("./res/BlueRect.png", renderer);
        listFloors.push_back(obj);
        pair<int,int> goal = path->getDest(stage);
        if (walker.first < goal.first) {
            walker.first += 32;
        } else if (walker.first > goal.first) {
            walker.first -= 32;
        } else if (walker.second < goal.second) {
            walker.second += 32;
        } else if (walker.second > goal.second) {
            walker.second -= 32;
        } else {
            stage += 1;
        }
    }
}

void setupMessages() {
    MsgStruct* m1 = createMsgStruct(999, false);
    m1->addChars(4);

    MsgStruct* m998 = createMsgStruct(998, false);

    MsgStruct* m2 = createMsgStruct(2, false);
    m2->addChars(1);

    MsgStruct* m3 = createMsgStruct(3, false);

    MsgStruct* o3 = createMsgStruct(3, true);
    o3->addChars(1);

    MsgStruct* m4 = createMsgStruct(4, false);
    m4->addChars(2);

    MsgStruct* o4 = createMsgStruct(4, true);
    o4->addChars(1);

    MsgStruct* o5 = createMsgStruct(5, true);
    o5->addString();

    MsgStruct* m10 = createMsgStruct(10, false);
    m10->addString();
}

bool canHandleMsg(bool confirmed) {
    if (bufferSize < 3) {
        return false;
    }
    string data = string(buffer);
    if (data.size() < 3) {
        return false;
    }
    // cout << "Handling message...\n";
    int offset = 0;
    if (confirmed) {
        offset += 2;
    }
    // cout << data + "\n";
    data = data.substr(offset);
    // cout << data + "\n";
    string rawMsgID = data.substr(0, 3);
    // cout << rawMsgID + "\n";
    int msgID = atoi(rawMsgID.c_str());
    if (inMsgStructs.find(msgID) != inMsgStructs.end()) {
        return inMsgStructs[msgID]->canHandle(data);
    }
    cout << "Message ID does not exist. Raw: " <<  rawMsgID << " | Parsed: " << msgID << "\n";
    cout << "Buffer: " << buffer << "\n";
    cout << "Data: " << data << "\n";
    bufferSize = 0;
    return false;
}

MsgStruct* readPacket(bool confirmed) {
    string data = string(buffer).substr(0, bufferSize);
    int offset = 0;
    if (confirmed) {
        offset += 2;
    }
    int msgID = atoi(data.substr(offset, 3).c_str());
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

MsgStruct* newPacket(int msgID) { return outMsgStructs[msgID]->reset(); }

int send(string data) { send(data, 0); }

int send(string data, int pID) {
    if (pID > 0) {
        data = extend(pID, 2) + data + "*";
    }
    int len = data.size() + 1;
    int out = SDLNet_TCP_Send(sock, (void*)data.c_str(), len);
    if (out < len) {
        fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    return 0;
}

int send(MsgStruct* packet, int pID) { send(packet->getData(), pID); }

Player* getPlayerbyID(string id) {
    return getPlayerbyID(atoi(id.c_str()));
}

Player* getPlayerbyID(int id) {
    auto it = listPlayers.find(id);
    if (it != listPlayers.end()) {
        return it->second;
    }
    return nullptr;
}

void addPlayerbyID(int id, SDL_Renderer* r) {
    auto it = listPlayers.find(id);
    if (it == listPlayers.end()) {
        Player* p = new Player(id, 0, 100, &lvl1);
        p->loadImg(r);
        listPlayers.emplace(id, p);
    }
}

void addTower(int id, int type, SDL_Renderer* r) {
    Player* p = getPlayerbyID(id);
    if(p == nullptr) {
        return;
    }

    auto pos = p->getPos();
    int x = pos.first;
    int y = pos.second;
    std::cout << "x,y " << x << "," << y << "\n";
    Tower* t;
    std::cout << type << "\n";
    if(type == 1) {
        //std::cout << "MAKING A CANNON!!\n";
        Cannon* cannon = new Cannon(x,y,1);
        cannon->loadImg(r);
        t = cannon;
    } else {
        //std::cout << "MAKING A ROCKET!!\n";
        Rocket* rocket = new Rocket(x,y,1);
        rocket->loadImg(r);
        t = rocket;
    }

    if(!lvl1.spotOpen(x, y)) {
        //std::cout << "Position wasn't open!\n";
        delete t;
        return;
    }
    t->setPlayer(p);
    listTower.push_back(t);
    lvl1.addGameObject(t);
}

int init() {
    int flag = IMG_INIT_PNG;
    if ((IMG_Init(flag) & flag) != flag) {
        std::cout << "Error, SDL_image" << "\n";
        return -1;
    }

    if (SDLNet_Init() == -1) {
        std::cout << "Error, SDLNet_Init\n";
        return -1;
    }
    return 0;
}
