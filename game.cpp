#include <vector>
#include <algorithm>
#include <random>

#include "claimedTile.hpp"
#include "unclaimedTile.hpp"
#include "upgradedTile.hpp"
#include "game.hpp"


int roll = 0;
int player = 0;
int choice = 0;

void getResources(vector<Player*> &players, vector<Tile*> &tiles, int i) {
    int tile_owner = tiles[i]->get_tile_owner();
    int tile_number = tiles[i]->get_tile_number();
    int num = 0;
    if (tiles[i]->getTileClass() == 2) {
        num = 1;
    } else {
        num = 2;
    }
    if (tile_number == roll) {
        int tile_type = tiles[i]->get_tile_type();
        if (tile_type == 0) {
            players[tile_owner - 1]->setWood(num);
        } else if (tile_type == 1) {
            players[tile_owner - 1]->setBrick(num);
        } else if (tile_type == 2) {
            players[tile_owner - 1]->setSheep(num);
        } else if (tile_type == 3) {
            players[tile_owner - 1]->setWheat(num);
        } else {
            players[tile_owner - 1]->setOre(num);
        }
    }
}
void rollDice(vector<Player*> &players, vector<Tile*> &tiles)
{
    int firstRoll = (rand() % 6) + 1;
    int secondRoll = (rand() % 6) + 1;
    roll = firstRoll + secondRoll;
    cout << endl;
    cout << "Dice roll: " << roll << endl;
    for (int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i]->get_tile_owner() != -100) {
            getResources(players, tiles, i);
        }
    }
}

void renderTiles(vector<Tile*> tiles, int size)
{
    for (int batchnum = 0; batchnum < size; batchnum++){
        vector<Tile*> curr_batch;
        for (int batch_idx = 0; batch_idx < size; batch_idx++){
            curr_batch.push_back(tiles[batchnum*size + batch_idx]);
        }
        for (int num_lines = 0; num_lines < 7; num_lines++){
            for(int num_squares = 0; num_squares < size; num_squares++){
                    cout << curr_batch[num_squares]->print(num_lines) << " ";
            }
            cout << "\n";
        }
    }
}

void setDevDeck(vector<Card*> &deck)
{
    for (int i = 0; i < 5; i++) { // VPs
        deck.push_back(new Card(0));
    }
    for (int i = 0; i < 2; i++) { // YOP, ROADBUILDING, MONOPOLY
        deck.push_back(new Card(1));
        deck.push_back(new Card(2));
        deck.push_back(new Card(3));
    }
    for (int i = 0; i < 14; i++) { // KNIGHTS
        deck.push_back(new Card(4));
    }
    
    random_device rd; // Shuffle Deck
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

void setTiles(vector<Tile*> &tiles, int size, int numPlayers) {
    for (int i = 0; i < (size * size) - numPlayers; i++)
    {
        TileType chosen_tile = (TileType)(rand() % 5);
        int chosen_number = rand() % 11 + 2;
        tiles.push_back(new UnclaimedTile(-100, chosen_number, chosen_tile));
    }
    for (int i = 1; i <= numPlayers; i++)
    {
        TileType chosen_tile = (TileType)(rand() % 5);
        int chosen_number = rand() % 11 + 2;
        tiles.push_back(new ClaimedTile(i, chosen_number, chosen_tile));
    }
    
    random_device rd; // Shuffle Tiles
    mt19937 g(rd());
    shuffle(tiles.begin(), tiles.end(), g);
}

void resources(vector<Player*> &players, int currPlayer)
{
    cout << "Victory Points: " << players[currPlayer]->getVPs() << "   ";
    cout << "Wood: " << players[currPlayer]->getWood() << "   ";
    cout << "Brick: " << players[currPlayer]->getBrick() << "   ";
    cout << "Sheep: " << players[currPlayer]->getSheep() << "   ";
    cout << "Wheat: " << players[currPlayer]->getWheat() << "   ";
    cout << "Ore: " << players[currPlayer]->getOre();
    cout << endl << endl;
}

void createPlayers(vector<Player*> &players, int numPlayers)
{
    string name;
    for (int i = 0; i < numPlayers; i++)
    {
        cout << "Enter Player " << (i + 1) << "'s name? ";
        cin >> name;
        players.push_back(new Player(name, 1, 1, 1, 1, 1, 1));
    }
    cout << endl << "Settlers of Catan!" << endl;
}

// void buyRoad() { // ADD LATER
    
// }

vector<int> getPlayerResources(vector<Player*> &players, int player) {
    vector<int> playerResources;
    int numWood = players[player - 1]->getWood();
    int numBrick = players[player - 1]->getBrick();
    int numSheep = players[player - 1]->getSheep();
    int numWheat = players[player - 1]->getWheat();
    int numOre = players[player - 1]->getOre();
    for (int i = 0; i < numWood; i++) {
        playerResources.push_back(0);
    }
    for (int i = 0; i < numBrick; i++) {
        playerResources.push_back(1);
    }
    for (int i = 0; i < numSheep; i++) {
        playerResources.push_back(2);
    }
    for (int i = 0; i < numWheat; i++) {
        playerResources.push_back(3);
    }
    for (int i = 0; i < numOre; i++) {
        playerResources.push_back(4);
    }
    return playerResources;
}

void buyDev(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    int type = deck[0]->getType();
    deck.erase(deck.begin());
    
    players[player]->setSheep(-1);
    players[player]->setOre(-1);
    players[player]->setWheat(-1);
    
    if (type == 0) { // VP
        cout << "\t\t" << players[player]->getName() << "drew a Victory Point!" << endl;
        players[player]->setVPs(1);
    } else if (type == 1) { // YOP
        cout << "\t\t" << players[player]->getName() << "drew a Year of Plenty!" << endl;
        cout << "\tOne of each resource was added to your hand!" << endl << endl;
        players.at(player)->setWood(1);
        players.at(player)->setBrick(1);
        players.at(player)->setWheat(1);
        players.at(player)->setSheep(1);
        players.at(player)->setOre(1);
    } else if (type == 2) { // TODO: ROADBUILDING
        players[player]->setVPs(1);
    } else if (type == 3) { // MONOPOLY
        players[player]->setVPs(1);
    } else { // KNIGHT
        cout << "\t\t" << players[player]->getName() << "drew a Knight!" << endl;
        cout << "\tChoose a player to steal random resource" << endl;
        for (int i = 0; i < players.size(); i++) {
            if (player != i)
                cout << i + 1 << ": " << players[i]->getName() << endl;
        }
        int playerToSteal = 0;
        cin >> playerToSteal;
        
        while(playerToSteal < 0 || playerToSteal > players.size() || playerToSteal == player) {
            cout << "\t\tInvalid choice" << endl;
            cout << "\tChoose a player to steal random resource" << endl;
            for (int i = 0; i < players.size(); i++)
            {
                if(player != i)
                {
                    cout << i + 1 << ": " << players[i]->getName() << endl;
                }
            }
            cin >> playerToSteal;
        }
        vector<int> playerToStealResources = getPlayerResources(players, playerToSteal);
        int resource = playerToStealResources[rand() % playerToStealResources.size()];
        if (resource == 0) {
            players[playerToSteal]->setWood(-1);
            cout << players[player]->getName() << "stole 1 wood from " << players[playerToSteal - 1]->getName() << endl;
            players[player]->setWood(1);
        } else if (resource == 1) {
            players[playerToSteal]->setBrick(-1);
            cout << players[player]->getName() << "stole 1 brick from " << players[playerToSteal - 1]->getName() << endl;
            players[player]->setBrick(1);
        } else if (resource == 2) {
            players[playerToSteal]->setSheep(-1);
            cout << players[player]->getName() << "stole 1 sheep from " << players[playerToSteal - 1]->getName() << endl;
            players[player]->setSheep(1);
        } else if (resource == 3) {
            players[playerToSteal]->setWheat(-1);
            cout << players[player]->getName() << "stole 1 wheat from " << players[playerToSteal - 1]->getName() << endl;
            players[player]->setWheat(1);
        } else {
            players[playerToSteal]->setOre(-1);
            cout << players[player]->getName() << "stole 1 ore from " << players[playerToSteal - 1]->getName() << endl;
            players[player]->setOre(1);
        }
    }
}

int calculateIndex(int row, int col, int size) {
    return (size * (row - 1)) + (col - 1);
}

void buySettle(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    int row;
    int col;
    int index;
    
    cout << "Buying Settlement" << endl;
    cout << "Enter row of settlement" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << "\t[" << i << "]" << endl;
    }
    cin >> row;
    while (row < 1 || row > size)
    {
        cout << "Invalid Choice: row is out of bounds" << endl;
        cout << "Enter row of settlement" << endl;
        for (int i = 1; i <= size; i++)
        {
            cout << "\t[" << i << "]" << endl;
        }
        cin >> row;
    }
    
    cout << "Enter column of settlement" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << "\t[" << i << "] " << endl;
    }
    cin >> col;
    while (col < 1 || col > size)
    {
        cout << "Invalid Choice: column is out of bounds." << endl;
        cout << "Enter column of settlement" << endl;
        for(int i = 1; i <= size; i++)
        {
            cout << "\t[" << i << "] ";
        }
        cout << endl;
        cin >> col;
    }
    
    index = calculateIndex(row, col, size);
    
    if (tiles[index]->get_tile_owner() != -100)
    {
        renderTiles(tiles, size);
        cout << endl << "Settlement already on tile." << endl;
        cout << "Please choose another tile." << endl << endl;
        buySettle(players, tiles, deck, player, size);
    } else {
        TileType tile_type = tiles[index]->get_tile_type();
        int tile_value = tiles[index]->get_tile_number();
        
        int upRow = row - 1;
        int downRow = row + 1;
        int leftCol = col - 1;
        int rightCol = col + 1;
        if ((upRow >= 1 && tiles[calculateIndex(upRow, col, size)]->get_tile_owner() == (player + 1)) ||
            (downRow <= size && tiles[calculateIndex(downRow, col, size)]->get_tile_owner() == (player + 1)) ||
            (leftCol >= 1 && tiles[calculateIndex(row, leftCol, size)]->get_tile_owner() == (player + 1)) ||
            (rightCol <= size && tiles[calculateIndex(row, rightCol, size)]->get_tile_owner() == (player + 1))) {
                
            tiles[index] = new ClaimedTile(player + 1, tile_value,tile_type);
            players[player]->setWood(-1);
            players[player]->setBrick(-1);
            players[player]->setWheat(-1);
            players[player]->setSheep(-1);
            players[player]->setVPs(1);
        } else {
            renderTiles(tiles, size);
            cout << endl << "No adjacent settlement";
            cout << endl << "Pick different tile" << endl << endl;
            buySettle(players, tiles, deck, player, size);
        }
        renderTiles(tiles, size);
        playTurn(players, tiles, deck, player, size);
    }
}

void buyCity(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    int row;
    int column;
    int index;
    
    cout << "Buying City" << endl;
    cout << "Enter row of city" << endl;
    for(int i = 1; i <= size; i++)
    {
        cout << "[" << i << "]" << endl;
    }
    
    cin >> row;
    
    while(row < 1 || row > size)
    {
        cout << "Invalid choice: row is out of bounds" << endl;
        cout << "Enter row" << endl;
        for(int i = 1; i <= size; i++)
        {
            cout << "[" << i << "]" << endl;
        }
        cin >> row;
    }
    
    cout << "Enter column" << endl;
    for(int i = 1; i <= size; i++)
    {
        cout << "[" << i << "] ";
    }
    cout << endl;
    cin >> column;
    
    while(column < 1 || column > size)
    {
        cout << "Invalid choice: column is out of bounds" << endl;
        cout << "Enter column" << endl;
        for(int i = 1; i <= size; i++)
        {
            cout << "[" << i << "] ";
        }
        cout << endl;
        cin >> column;
    }
    
    index = calculateIndex(row, column, size);
    
    if (tiles[index]->get_tile_owner() == (player + 1)) {
        if (tiles[index]->getTileClass() != 3) {
            TileType tile_type = tiles[index]->get_tile_type();
            int tile_number = tiles[index]->get_tile_number();
            int tile_owner = tiles[index]->get_tile_owner();
            
            tiles[index] = new UpgradedTile(tile_owner, tile_number, tile_type);
            players[player]->setWheat(-3);
            players[player]->setOre(-2);
            players[player]->setVPs(1);
            renderTiles(tiles, size);
            playTurn(players, tiles, deck, player, size);
        } else {
            cout << "You already own a city here." << endl;
            buyCity(players, tiles, deck, player, size);
        }
    } else {
        cout << endl << "You do not own a settlement on this tile";
        cout << endl << "Choose different tile" << endl << endl;
        buyCity(players, tiles, deck, player, size); 
    }
}

void buyInterface(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    while (choice != 4)
    {
        cout << "|1: Settlement (1 wood, 1 brick, 1 wheat, 1 sheep)|" << endl;
        cout << "|            2: City (2 wheat, 3 ore)            |" << endl;
        cout << "|  3: Development Card (1 sheep, 1 wheat, 1 ore)  |" << endl;
        cout << "|                    4: Back                     |" << endl;
        cin >> choice;
        
        while (choice < 1 || choice > 4)
        {
            cout << "|1: Settlement (1 wood, 1 brick, 1 wheat, 1 sheep)|" << endl;
            cout << "|            2: City (2 wheat, 3 ore)            |" << endl;
            cout << "|  3: Development Card (1 sheep, 1 wheat, 1 ore)  |" << endl;
            cout << "|                    4: Back                     |" << endl;
            cin >> choice;
        }
        
        if (choice == 1)
        {
            if (players[player]->getWood() >= 1 && players[player]->getBrick() >= 1 && players[player]->getWheat() >= 1 && players[player]->getSheep() >= 1) {
                buySettle(players, tiles, deck, player, size);
            } else {
                cout << "Insufficient resources to purchase settlement" << endl;
                playTurn(players, tiles, deck, player, size);
            }
        } else if (choice == 2) {
            if (players[player]->getWheat() >= 2 && players[player]->getOre() >= 3) {
                buyCity(players, tiles, deck, player, size);
            } else {
                cout << "Insufficient resources to purchase city" << endl;
                playTurn(players, tiles, deck, player, size);
            }
        } else if (choice == 3) {
            if (players[player]->getSheep() >= 1 && players[player]->getWheat() >= 1 && players[player]->getOre() >= 1) {
                buyDev(players, tiles, deck, player, size);
            } else {
                cout << "Insufficient resources to purchase development card" << endl;
                playTurn(players, tiles, deck, player, size);
            }
        } else {
            playTurn(players, tiles, deck, player, size);
        }
    }
}

void tradeBank(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    int tradeResource = 0;
    int receivingResource = 0;
    
    if (players[player]->getWood() < 4 &&
        players[player]->getBrick() < 4 &&
        players[player]->getSheep() < 4 &&
        players[player]->getWheat() < 4 &&
        players[player]->getOre() < 4)
    {
        cout << "Minimum four of a resource type to trade with bank" << endl << endl;
    } else {
        cout << "|Which resource would you like to trade in?|" << endl;
        cout << "|                 1: Wood                  |" << endl;
        cout << "|                 2: Brick                 |" << endl;
        cout << "|                 3: Sheep                 |" << endl;
        cout << "|                 4: Wheat                  |" << endl;
        cout << "|                 5: Ore                   |" << endl;
        cin >> tradeResource;
        
        if (tradeResource < 1 || tradeResource > 5){
            cout << "Invaild input" << endl;
            tradeBank(players, tiles, deck, player, size);
        }
        
        if (tradeResource == 1) {
            if (players[player]->getWood() >= 4){
                players[player]->setWood(-4);
            } else {
                cout << "Insufficient resource funds" << endl << endl;
                tradeBank(players, tiles, deck, player, size);
            }
        } else if (tradeResource == 2) {
            if(players[player]->getBrick() >= 4){
                players[player]->setBrick(-4);
            } else {
                cout << "Insufficient resource funds" << endl << endl;
                tradeBank(players, tiles, deck, player, size);
            }
        } else if (tradeResource == 3) {
            if (players[player]->getSheep() >= 4){
                players[player]->setSheep(-4);
            } else {
                cout << "Insufficient resource funds" << endl << endl;
                tradeBank(players, tiles, deck, player, size);
            }
        } else if (tradeResource == 4) {
            if(players[player]->getWheat() >= 4){
                players[player]->setWheat(-4);
            } else {
                cout << "Insufficient resource funds" << endl << endl;
                tradeBank(players, tiles, deck, player, size);
            }
        } else {
            if (players[player]->getOre() >= 4){
                players[player]->setOre(-4);
            } else {
                cout << "Insufficient resource funds" << endl << endl;
                tradeBank(players, tiles, deck, player, size);
            }
        }
        
        cout << "|           Receive which resource?       |" << endl;
        cout << "|                 1: Wood                 |" << endl;
        cout << "|                 2: Brick                |" << endl;
        cout << "|                 3: Sheep                |" << endl;
        cout << "|                 4: Wheat                 |" << endl;
        cout << "|                 5: Ore                  |" << endl;
        cin >> receivingResource;
        
        if (receivingResource < 1 || receivingResource > 5){
            cout << "Invalid input" << endl;
            tradeBank(players, tiles, deck, player, size);
        }
        
        if (receivingResource == 1) {
            players[player]->setWood(1);
        } else if (receivingResource == 2) {
            players[player]->setBrick(1);
        } else if (receivingResource == 3) {
            players[player]->setSheep(1);
        } else if (receivingResource == 4) {
            players[player]->setWheat(1);
        } else {
            players[player]->setOre(1);
        }
    }
}

void playTurn(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    while(players[player]->getVPs() < 10)
    {
        cout << players[player]->getName() << "'s turn." << endl << endl;
        resources(players, player);
        
        cout << "\t|What would you like to do?|" << endl;
        cout << "\t|         1: Buy           |" << endl;
        cout << "\t|         2: Swap          |" << endl;
        cout << "\t|        3: End Turn       |" << endl;
        cin >> choice;
        
        while (choice < 1 || choice > 3)
        {
            cout << "\t|Invalid Option|" << endl;
            cout << "\t|    1: Buy      |" << endl;
            cout << "\t|    2: Swap     |" << endl;
            cout << "\t|   3: End Turn  |" << endl;
            cin >> choice;
        }
    
        if (choice == 1) {
            choice = 0;
            buyInterface(players, tiles, deck, player, size);
        } else if (choice == 2) {
            choice = 0;
            tradeBank(players, tiles, deck, player, size);
        } else {
            choice = 0;
            player++;
            player = player % players.size();
            renderTiles(tiles, size);
            rollDice(players, tiles);
            playTurn(players, tiles, deck, player, size);
        }
    }
    cout << players[player]->getName() << " wins with " << players[player]->getVPs() << " victory points!" << endl;
}

int main() {
    srand(time(0));
    int numPlayers;
    int size;
    vector<Card*> deck;
    vector<Player*> players;
    vector<Tile*> tiles;

    cout << "Enter a value between 3 and 10 for board size: ";
    cin >> size;
    while (size < 3 || size > 10)
    {
        cout << "Invalid size" << endl;
        cout << "Enter a value between 3 and 10 for board size: ";
        cin >> size;
    }
    cout << endl;
    
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

    createPlayers(players, numPlayers);
    setTiles(tiles, size, numPlayers);
    setDevDeck(deck);
    renderTiles(tiles, size);
    rollDice(players, tiles);
    playTurn(players, tiles, deck, player, size);
    return 0;
}