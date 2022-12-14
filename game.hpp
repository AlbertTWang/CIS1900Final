#ifndef GAME_HPP
#define GAME_HPP
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "claimedTile.hpp"
#include "unclaimedTile.hpp"
#include "upgradedTile.hpp"
#include "player.hpp"
#include "card.hpp"

void getResources(vector<Player*> &players, vector<Tile*> &tiles, int i);
void stealRandomResource(vector<Player*> &players, int player, int playerToSteal);
void moveRobber(vector<Player*> &players, vector<Tile*> &tiles, int player, int size);
void rollDice(vector<Player*> &players, vector<Tile*> &tiles, int player, int size, int roll);
void renderTiles(vector<Tile*> tiles, int size);
void setDevDeck(vector<Card*> &deck);
void setTiles(vector<Tile*> &tiles, int size, int playerCount, vector<Player*> & players);
void resources(vector<Player*> &players, int z);
void createPlayers(vector<Player*> &players, int playerCount);
void buyDev(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);
int calculateIndex(int row, int col, int size);
bool checkIfRoadExistsAdj(int road, Tile* adjTile, vector<Player*> & players, int player);
void buySettle(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);

//TBI
void buyRoadHandler(vector<Player*> & players, int player, int road, Tile* tile);
void buyRoad(vector<Player*> & players, vector<Tile*> & tiles,vector<Card*> & deck, int player, int size);

void buyCity(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);
void buyInterface(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);
std::string choicePrintHelper(int choice);
bool checkIfAmtViable(int amount, int resource);
void giveResource(int amount, int resource, int giver, int receiver, vector<Player*> & player);
void tradeBank(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);
void tradePlayer(vector<Player*> & players, int player, int size);
int playTurn(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size);

#endif