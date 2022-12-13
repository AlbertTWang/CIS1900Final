#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>

#include "claimedTile.hpp"
#include "unclaimedTile.hpp"
#include "upgradedTile.hpp"
#include "game.hpp"


int roll = 0;
int player = 0;
int choice = 0;
int points = 0;

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
                    cout << curr_batch[num_squares]->print(num_lines) << "       " << setw(5);
            }
            cout << "\n";
        }
        cout << endl;
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
    random_device rd;
    mt19937 g(rd());
    vector<int> tileNums {0, 1, 2, 3, 4};
    vector<int> nums {2,2, 3,3,3, 4,4,4, 5,6,8,9, 10,10,10, 11,11,11, 12,12};
    int tileNumsArr[] = {0, 1, 2, 3, 4};
    int numsArr[] = {2,2, 3,3,3, 4,4,4, 5,6,8,9, 10,10,10, 11,11,11, 12,12};
    shuffle(tileNums.begin(), tileNums.end(), g);
    shuffle(nums.begin(), nums.end(), g);
    for (int i = 0; i < (size * size) - numPlayers * 2; i++) {
        TileType chosen_tile = (TileType)(tileNums[0]);
        tileNums.erase(tileNums.begin());
        if (tileNums.size() == 0) {
            tileNums.insert(tileNums.begin(), tileNumsArr, tileNumsArr + 5);
            shuffle(tileNums.begin(), tileNums.end(), g);
        }

        int chosen_number = nums[0];
        nums.erase(nums.begin());
        if (nums.size() == 0) {
            nums.insert(nums.begin(), numsArr, numsArr + 5);
            shuffle(nums.begin(), nums.end(), g);
        }
        tiles.push_back(new UnclaimedTile(-100, chosen_number, chosen_tile));
    }

    vector<int> firstNums {6, 8};
    vector<int> secondNums {5, 9};
    for (int i = 1; i <= numPlayers; i++) {
        TileType chosen_tile = (TileType)(rand() % 5);
        int chosen_number = firstNums[rand() % 2];
        tiles.push_back(new ClaimedTile(i, chosen_number, chosen_tile));
    }
    for (int i = 1; i <= numPlayers; i++) {
        TileType chosen_tile = (TileType)(rand() % 5);
        int chosen_number = secondNums[rand() % 2];
        tiles.push_back(new ClaimedTile(i, chosen_number, chosen_tile));
    }
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
        players.push_back(new Player(name, 1, 1, 1, 1, 1, 2));
    }
    cout << endl << "\t\t\tLet's Play Catan!" << endl << endl;
}

// void buyRoad() { // ADD LATER
    
// }

vector<int> getPlayerResources(vector<Player*> &players, int player) {
    vector<int> playerResources;
    int numWood = players[player]->getWood();
    int numBrick = players[player]->getBrick();
    int numSheep = players[player]->getSheep();
    int numWheat = players[player]->getWheat();
    int numOre = players[player]->getOre();
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
        cout << "\t\t" << players[player]->getName() << " drew a Victory Point!" << endl;
        players[player]->setVPs(1);
    } else if (type == 1) { // YOP
        cout << "\t\t" << players[player]->getName() << " drew a Year of Plenty!" << endl;
        cout << "\tOne of each resource was added to your hand!" << endl << endl;
        players.at(player)->setWood(1);
        players.at(player)->setBrick(1);
        players.at(player)->setWheat(1);
        players.at(player)->setSheep(1);
        players.at(player)->setOre(1);
    } else if (type == 2) { // TODO: ROADBUILDING
        cout << "\t\t" << players[player]->getName() << " drew a Road Building!" << endl;
        players[player]->setVPs(1);
    } else if (type == 3) { // MONOPOLY
        cout << "\t\t" << players[player]->getName() << " drew a Monopoly!" << endl;
        cout << "Choose a resource to completely empty from everyone's hand" << endl;
        for (int i = 0; i < 5; i++) {
            cout << "[" << i + 1 << "] " << players[i]->getName() << endl;
        }
        players[player]->setVPs(1);
    } else { // KNIGHT
        cout << players[player]->getName() << " drew a Knight!" << endl << endl;
        cout << "Choose a player to steal a random resource from" << endl;
        for (int i = 0; i < players.size(); i++) {
            if (player != i)
                cout << "[" << i + 1 << "] " << players[i]->getName() << endl;
        }
        int playerToSteal;
        cin >> playerToSteal;
        playerToSteal -= 1;
        while (playerToSteal < 0 || playerToSteal > players.size() || playerToSteal == player) {
            cout << "Invalid choice" << endl;
            cout << "Choose a player to steal a random resource from" << endl;
            for (int i = 0; i < players.size(); i++) {
                if (player != i)
                    cout << "[" << i + 1 << "] " << players[i]->getName() << endl;
            }
            cin >> playerToSteal;
            playerToSteal -= 1;
        }
        vector<int> playerToStealResources = getPlayerResources(players, playerToSteal);
        int resource = playerToStealResources[rand() % playerToStealResources.size()];
        if (resource == 0) {
            players[playerToSteal]->setWood(-1);
            cout << players[player]->getName() << " stole 1 wood from " << players[playerToSteal]->getName() << endl;
            players[player]->setWood(1);
        } else if (resource == 1) {
            players[playerToSteal]->setBrick(-1);
            cout << players[player]->getName() << " stole 1 brick from " << players[playerToSteal]->getName() << endl;
            players[player]->setBrick(1);
        } else if (resource == 2) {
            players[playerToSteal]->setSheep(-1);
            cout << players[player]->getName() << " stole 1 sheep from " << players[playerToSteal]->getName() << endl;
            players[player]->setSheep(1);
        } else if (resource == 3) {
            players[playerToSteal]->setWheat(-1);
            cout << players[player]->getName() << " stole 1 wheat from " << players[playerToSteal]->getName() << endl;
            players[player]->setWheat(1);
        } else {
            players[playerToSteal]->setOre(-1);
            cout << players[player]->getName() << " stole 1 ore from " << players[playerToSteal]->getName() << endl;
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
    cout << "\t[" << size + 1 << "] (Cancel)" << endl;
    cin >> row;
    while (row < 1 || row > size) {
        if (row == size + 1) {
            playTurn(players, tiles, deck, player, size);
        } else {
            cout << "Invalid Choice: row is out of bounds" << endl;
            cout << "Enter row of settlement" << endl;
            for (int i = 1; i <= size; i++)
            {
                cout << "\t[" << i << "]" << endl;
            }
            cin >> row;
        }
    }
    
    cout << "Enter column of settlement" << endl;
    for (int i = 1; i <= size; i++)
    {
        cout << "\t[" << i << "] " << endl;
    }
    cout << "\t[" << size + 1 << "] (Cancel)" << endl;
    cin >> col;
    while (col < 1 || col > size)
    {
        if (col == size + 1) {
            playTurn(players, tiles, deck, player, size);
        } else {
            cout << "Invalid Choice: column is out of bounds." << endl;
            cout << "Enter column of settlement" << endl;
            for(int i = 1; i <= size; i++)
            {
                cout << "\t[" << i << "] ";
            }
            cout << endl;
            cin >> col;
        }
    }
    
    index = calculateIndex(row, col, size);
    
    if (tiles[index]->get_tile_owner() != -100)
    {
        renderTiles(tiles, size);
        cout << endl << "Settlement already on tile." << endl;
        cout << "Please choose another tile." << endl << endl;
        playTurn(players, tiles, deck, player, size);
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
            playTurn(players, tiles, deck, player, size);
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
        for (int i = 1; i <= size; i++) {
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
            players[player]->setWheat(-2);
            players[player]->setOre(-3);
            players[player]->setVPs(1);
            renderTiles(tiles, size);
            playTurn(players, tiles, deck, player, size);
        } else {
            cout << "You already own a city here." << endl;
            playTurn(players, tiles, deck, player, size);
        }
    } else {
        cout << endl << "You do not own a settlement on this tile";
        cout << endl << "Choose different tile" << endl << endl;
        playTurn(players, tiles, deck, player, size); 
    }
}

void buyInterface(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    cout << "\t\t| [1] Settlement (1 wood, brick, wheat, sheep) |" << endl;
    cout << "\t\t|            [2] City (2 wheat, 3 ore)         |" << endl;
    cout << "\t\t|  [3] Development Card (1 sheep, wheat, ore)  |" << endl;
    cout << "\t\t|                    [4] Back                  |" << endl;
    cin >> choice;
    
    while (choice < 1 || choice > 4)
    {
        cout << "\t\t|                  Invalid Option              |" << endl;
        cout << "\t\t| [1] Settlement (1 wood, brick, wheat, sheep) |" << endl;
        cout << "\t\t|            [2] City (2 wheat, 3 ore)         |" << endl;
        cout << "\t\t|  [3] Development Card (1 sheep, wheat, ore)  |" << endl;
        cout << "\t\t|                    [4] Back                  |" << endl;
        cin >> choice;
    }
    
    if (choice == 1)
    {
        if (players[player]->getWood() >= 1 && players[player]->getBrick() >= 1 && players[player]->getWheat() >= 1 && players[player]->getSheep() >= 1) {
            buySettle(players, tiles, deck, player, size);
        } else {
            cout << endl << "\t\t!!! Insufficient resources to purchase settlement !!!" << endl;
            playTurn(players, tiles, deck, player, size);
        }
    } else if (choice == 2) {
        if (players[player]->getWheat() >= 2 && players[player]->getOre() >= 3) {
            buyCity(players, tiles, deck, player, size);
        } else {
            cout << endl << "\t\t!!! Insufficient resources to purchase city !!!" << endl;
            playTurn(players, tiles, deck, player, size);
        }
    } else if (choice == 3) {
        if (players[player]->getSheep() >= 1 && players[player]->getWheat() >= 1 && players[player]->getOre() >= 1) {
            buyDev(players, tiles, deck, player, size);
        } else {
            cout << endl << "\t\t!!! Insufficient resources to purchase development card !!!" << endl;
            playTurn(players, tiles, deck, player, size);
        }
    } else {
        playTurn(players, tiles, deck, player, size);
    }
}

std::string choiceHelper(int choice)
{
    switch(choice)
    {
        case 1:
            return "Wood";
            break;
        case 2:
            return "Brick";
            break;
        case 3:
            return "Sheep";
            break;
        case 4:
            return "Wheat";
            break;
        case 5:
            return "Ore";
            break;
        default:
            return "";
            break;
    }
}

bool checkIfAmtViable(int amount, int resource, vector<Player*> & players, int player)
{
    switch(resource)
    {
        case 1:
            return players[player]->getWood() >= amount;
            break;
        case 2:
            return players[player]->getBrick() >= amount;
            break;
        case 3:
            return players[player]->getSheep() >= amount;
            break;
        case 4:
            return players[player]->getWheat() >= amount;
            break;
        case 5:
            return players[player]->getOre() >= amount;
            break;
        default:
            return false;
            break;
    }
}

void giveResource(int amount, int resource, int giver, int receiver, vector<Player*> & players)
{
    switch(resource)
    {
        case 1:
            players[giver]->setWood(-1*amount);
            players[receiver]->setWood(amount);
            break;
        case 2:
            players[giver]->setBrick(-1*amount);
            players[receiver]->setBrick(amount);
            break;
        case 3:
            players[giver]->setSheep(-1*amount);
            players[receiver]->setSheep(amount);
            break;
        case 4:
            players[giver]->setWheat(-1*amount);
            players[receiver]->setWheat(amount);
            break;
        case 5:
            players[giver]->setOre(-1*amount);
            players[receiver]->setOre(-1*amount);
            break;
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
        cout << "Minimum 4 of same resource type to trade with bank" << endl << endl;
    } else {
        cout << endl << "|Which resource would you like to trade in?|" << endl;
        cout << "|                 [1] Wood                 |" << endl;
        cout << "|                 [2] Brick                |" << endl;
        cout << "|                 [3] Sheep                |" << endl;
        cout << "|                 [4] Wheat                |" << endl;
        cout << "|                 [5] Ore                  |" << endl << endl;
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
        cout << "|                [1] Wood                 |" << endl;
        cout << "|                [2] Brick                |" << endl;
        cout << "|                [3] Sheep                |" << endl;
        cout << "|                [4] Wheat                |" << endl;
        cout << "|                [5] Ore                  |" << endl;
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

void tradePlayer(vector<Player*> & players, int player, int size)
{
    int playerToTradeWith;
    int playerOneTradeResource;
    int playerOneTradeAmt;
    int playerTwoTradeResource;
    int playerTwoTradeAmt;
    int totalPlayers = players.size();
    cout << endl << "|Which player would you like to trade with?|" << endl;
    for (int i = 0; i < players.size(); i++) {
        if (player != i)
            cout << "[" << i + 1 << "] " << players[i]->getName() << endl;
    }
    cin >> playerToTradeWith;
    if (playerToTradeWith < 0 || playerToTradeWith - 1 == player || playerToTradeWith > totalPlayers)
    {
       cout << endl << "|INVALID PLAYER CHOICE: Please choose a valid player number|" << endl; 
       tradePlayer(players, player, size);
    }
    cout << endl << "|Player " + players[player]->getName() + ", " << "Which resource would you like to trade?|" << endl;
    cout << "|                [1] Wood                 |" << endl;
    cout << "|                [2] Brick                |" << endl;
    cout << "|                [3] Sheep                |" << endl;
    cout << "|                [4] Wheat                |" << endl;
    cout << "|                [5] Ore                  |" << endl;
    cin >> playerOneTradeResource;
    if(playerOneTradeResource <= 0 || playerOneTradeResource > 5)
    {
        cout << endl << "INVALID INPUT FOR AMOUNT OF RESOURCES REQUESTED" << endl;
        tradePlayer(players, player, size);
    } 
    std::string resourceToTrade = choiceHelper(playerOneTradeResource);
    if(resourceToTrade != "")
    {
        cout << endl << "How much " + resourceToTrade + " are you willing to put up?" << endl;
    }
    else
    {
        cout << endl << "Weird we should not have gotten here....." << endl;
        tradePlayer(players, player, size);
    }
    cin >> playerOneTradeAmt;
    if(!checkIfAmtViable(playerOneTradeAmt, playerOneTradeResource, players, player))
    {
        cout << endl << "Insufficient amount to trade!" << endl;
        tradePlayer(players, player, size);
    }
    cout << endl << "|Player " + std::to_string(playerToTradeWith) + ", " << "Which resource would you like to trade?|" << endl;
    cout << "|                [1] Wood                 |" << endl;
    cout << "|                [2] Brick                |" << endl;
    cout << "|                [3] Sheep                |" << endl;
    cout << "|                [4] Wheat                |" << endl;
    cout << "|                [5] Ore                  |" << endl;
    cin >> playerTwoTradeResource;

    if(playerTwoTradeResource <= 0 || playerTwoTradeResource > 5)
    {
        cout << endl << "INVALID INPUT FOR AMOUNT OF RESOURCES REQUESTED" << endl;
        tradePlayer(players, player, size);
    } 
    std::string resourceToTradeP2 = choiceHelper(playerTwoTradeResource);
    if(resourceToTradeP2 != "")
    {
        cout << endl << "How much " + resourceToTradeP2 + " are you willing to put up?" << endl;
    }
    else
    {
        cout << endl << "Weird we should not have gotten here....." << endl;
        tradePlayer(players, player, size);
    }
    cin >> playerTwoTradeAmt;
    if(!checkIfAmtViable(playerTwoTradeAmt, playerTwoTradeResource, players, playerToTradeWith - 1))
    {
        cout << endl << "Insufficient amount to trade!" << endl;
        tradePlayer(players, player, size);
    }
    giveResource(playerOneTradeAmt, playerOneTradeResource, player, playerToTradeWith - 1, players);
    giveResource(playerTwoTradeAmt, playerTwoTradeResource, playerToTradeWith - 1, player, players);
}

int playTurn(vector<Player*> &players, vector<Tile*> &tiles, vector<Card*> &deck, int player, int size)
{
    while(players[player]->getVPs() < points)
    {
        renderTiles(tiles, size);
        cout << endl << "\t\t\t\t" << players[player]->getName() << "'s turn." << endl;
        resources(players, player);
        
        cout << endl;
        cout << "|        What would you like to do?        |" << endl;
        cout << "|        [1] Buy                           |" << endl;
        cout << "|        [2] Bank                          |" << endl;
        cout << "|        [3] Trade                         |" << endl;
        cout << "|        [4] End Turn                      |" << endl << endl;
        cin >> choice;
        
        while (choice < 1 || choice > 4)
        {
            cout << endl;
            cout << "|              Invalid Option              |" << endl;
            cout << "|              [1] Buy                     |" << endl;
            cout << "|              [2] Bank                    |" << endl;
            cout << "|              [3] Trade                   |" << endl;
            cout << "|              [4] End Turn                |" << endl << endl;
            cin >> choice;
        }
    
        if (choice == 1) {
            choice = 0;
            buyInterface(players, tiles, deck, player, size);
        } else if (choice == 2) {
            choice = 0;
            tradeBank(players, tiles, deck, player, size);
        } else if (choice == 3){
            choice = 0;
            tradePlayer(players, player, size);

        } else if (choice == 4) {
            choice = 0;
            player++;
            player = player % players.size();
            rollDice(players, tiles);
            playTurn(players, tiles, deck, player, size);
        }
    }
    return player;
}

int main() {
    srand(time(0));
    int numPlayers;
    int size;
    vector<Card*> deck;
    vector<Player*> players;
    vector<Tile*> tiles;

    cout << endl << "\t\t\tWelcome to Catan!" << endl;
    cout << "How big will your board be? Enter a value between 3 and 10: ";
    cin >> size;
    while (size < 3 || size > 10)
    {
        cout << "Invalid size" << endl;
        cout << "How big will your board be? Enter a value between 3 and 10: ";
        cin >> size;
    }
    cout << endl;

    cout << "How many points needed for victory? Enter a value between 3 and 12: ";
    cin >> points;
    while (points < 3 || points > 12)
    {
        cout << "Invalid input" << endl;
        cout << "How many points needed for victory? Enter a value between 3 and 12: ";
        cin >> points;
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
    int winner = playTurn(players, tiles, deck, player, size);
    cout << players[winner]->getName() << " wins with " << players[player]->getVPs() << " victory points!" << endl;
    return 0;
}