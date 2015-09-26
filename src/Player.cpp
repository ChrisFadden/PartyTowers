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

int Player::getMoney() { return money; }



void Player::moveUp() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 0, -1);
}

void Player::moveDown() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 0, 1);
}

void Player::moveLeft() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, -1, 0);
}

void Player::moveRight() {
    //x,y deltas may be wrong
    lvl->moveCursor(cursor, 1, 0);
}

std::pair<int,int> Player::getPos() {
    return std::pair<int,int>(cursor->getX(),cursor->getY());
}

SDL_Texture* Player::getTexture() {
    return cursor->draw();
}

void Player::loadImg(SDL_Renderer* r) {
    std::string fn = "./res/RedRect.png";
    cursor->loadImg(fn, r);
}
