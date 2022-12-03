#include "card.h"
#include "player.h"
#include "tile.h"
#include <iostream>
#include <vector>

using namespace std;

void rollDice() {
    int roll = 1 + (rand() % 11);
    cout << "Dice rolled: " << roll < "\n";
}

void setTiles(vector<Tile*> &tiles) {
    
}

void setPlayers(vector<Player*> &players, int numPlayers) {
    for (int i = 0; i < numPlayers; i++)
    {
        String name;
        cout << "Enter Player " << (i + 1) << "'s name";
        cin >> name;
        players.push_back(new Player(name));
    }
}

int main() {
    srand(time(0)); // Seed to generate different random numbers every game

    int numPlayers;

    vector<Card*> deck;
    vector<Player*> players;
    vector<Tile*> tiles;


}