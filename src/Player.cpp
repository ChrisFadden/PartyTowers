#include "Player.h"

Player::Player(string PlayerID, int Score, int Money) {
  playerID = PlayerID;
  score = Score;
  money = Money;
}

string Player::getPlayerID() { return playerID; }

void Player::setScore(int Score) { score = Score; }

int Player::getScore() { return score; }

void Player::setMoney(int Money) { money = Money; }

int Player::getMoney() { return money; }
