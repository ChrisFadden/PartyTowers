#include "Player.h"

Player::Player(int PlayerID, int Score, int Money, Level* l) {
  playerID = PlayerID;
  score = Score;
  money = Money;
  cursor = new Cursor();
  lvl = l;
}

int Player::getPlayerID() { return playerID; }

void Player::setScore(int Score) { score = Score; }

int Player::getScore() { return score; }

void Player::setMoney(int Money) { money = Money; }

void Player::addMoney(int dm) {
    money += dm;
}

int Player::getMoney() { return money; }

void Player::setName(string name) {
    this->name = name;
}

string Player::getName() {
    return name;
}

void Player::moveUp() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 0, -32);
}

void Player::moveDown() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 0, 32);
}

void Player::moveLeft() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, -32, 0);
}

void Player::moveRight() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 32, 0);
}

std::pair<int,int> Player::getPos() {
    return std::pair<int,int>(cursor->getX(),cursor->getY());
}

SDL_Texture* Player::getTexture() {
    return cursor->draw();
}

void Player::loadImg(SDL_Renderer* r) {
    std::string fn = "./res/Cursor.png";
    cursor->loadImg(fn, r);
}
