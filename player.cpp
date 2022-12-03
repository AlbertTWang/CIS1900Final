#include <iostream>
#include <vector>
#include "player.h"

using namespace std;

Player::Player(string name, int wood, int brick, int wheat, int sheep, int ore, int VPs)
{
    this->name = name;
    this->wood = wood;
    this->brick = brick;
    this->wheat = wheat;
    this->sheep = sheep;
    this->ore = ore;
    this->VPs = VPs;
}

string Player::getName()
{
    return name;
}

int Player::getWood()
{
    return wood;
}

int Player::getBrick()
{
    return brick;
}

int Player::getWheat()
{
    return wheat;
}

int Player::getSheep()
{
    return sheep;
}

int Player::getOre()
{
    return ore;
}
int Player::getVPs()
{
    return VPs;
}
void Player::setWood(int addedWood)
{
    wood += addedWood;
}

void Player::setBrick(int addedBrick)
{
    brick += addedBrick;
}

void Player::setWheat(int addedWheat)
{
    wheat += addedWheat;
}

void Player::setSheep(int addedSheep)
{
    sheep += addedSheep;
}

void Player::setOre(int addedOre)
{
    ore += addedOre;
}
void Player::setVPs(int addedVPs)
{
    VPs += addedVPs;
}