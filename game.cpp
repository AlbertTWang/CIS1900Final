#include "card.h"
#include "player.h"
#include "tile.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

void pregameSetup(vector<Player*> &players) {
    int roll = 1 + (rand() % 11);
    cout << "Dice rolled: " << roll << "\n";
}

void setTiles(vector<Tile*> &tiles) {
    
}

void setPlayers(vector<Player*> &players, int numPlayers) {
    for (int i = 0; i < numPlayers; i++)
    {
        string name;
        cout << "Enter Player " << (i + 1) << "'s name";
        cin >> name;
        players.push_back(new Player(name, 0, 0, 0, 0, 0, 0));
    }
}

void setDevDeck(vector<Card*> &deck) {
    for (int i = 0; i < 14; i++) {
        deck.push_back(new Card(KNIGHT));
    }
    for (int i = 0; i < 2; i++) {
        deck.push_back(new Card(YOP));
        deck.push_back(new Card(ROADBUILDING));
        deck.push_back(new Card(MONOPOLY));
    }
    for (int i = 0; i < 5; i++) {
        deck.push_back(new Card(VP));
    }
    random_device rd;
    mt19937 g(rd());

    shuffle(deck.begin(), deck.end(), g);
}

void buyRoad() {
    
}

void buySettle() {

}

void buyCity() {

}

void buyDev() {

}

void playTurn() {
    while (1 == 1) {
        
    }
}

int main() {
    srand(time(0)); // Seed to generate different random numbers every game

    int numPlayers;

    vector<Card*> deck;
    vector<Player*> players;
    vector<Tile*> tiles;

    cout << "Select number of players (2-4): ";
    cin >> numPlayers;
    cout << endl;
    while (numPlayers < 2 || numPlayers > 4)
    {
        cout << "Invalid number of players" << endl;
        cout << "Select number of players (2-4): ";
        cin >> numPlayers;
        cout << endl;
    }

    setPlayers(players, numPlayers);

    setDevDeck(deck);

    pregameSetup(players);

    playTurn();
    return 0;
}