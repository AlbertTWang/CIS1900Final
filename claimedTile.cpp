#include "claimedTile.hpp"
#include "tile.hpp"

ClaimedTile::ClaimedTile(int owner, int number, TileType tileType, std::string ownerName, bool hasRobber)
{
    tile_owner = owner;
    tile_number = number;
    tile_type = tileType;
    owner_name = ownerName;
    hasRobber = false;

    upRoad = new Road();
    downRoad = new Road();
    leftRoad = new Road();
    rightRoad = new Road();
};

std::string ClaimedTile::print(int i) const
{
    if(i == 0){
        switch (tile_type){
            case WOOD:
                return "[** WOOD **]  " + std::to_string(tile_number);
            case BRICK:
                return "[** BRICK **] " + std::to_string(tile_number);
            case SHEEP:
                return "[** SHEEP **] " + std::to_string(tile_number);
            case WHEAT:
                return "[** WHEAT **] " + std::to_string(tile_number);
            case ORE:
                return "[** ORE **]   " + std::to_string(tile_number);
            
        }
    }
    else if(i == 1 || i == 10) {
        return "[ ----------- ]";
    } else if (i == 2) {
        if(upRoad->getIsOwned()){
            return "[      ||     ]";
        } else {
            return "[             ]";
        }
    } else if (i == 3) {
        std::string res = owner_name;
        while (res.length() < 12) {
            res = " " + res;
            res = res + " ";
        }
        if (res.length() == 12) {
            res = res + " ";
        }
        std::string to_return = "[" + res + "]";
        return to_return;
    } else if (i == 4 || i == 5 || i == 6) { // code is meh but does the job
        if (hasRobber) {
            if (i == 4) {
                if (leftRoad->getIsOwned() && rightRoad->getIsOwned()){
                    return "[-  @/       -]";
                } else if(leftRoad->getIsOwned()){
                    return "[-  @/        ]";
                } else if(rightRoad->getIsOwned()){
                    return "[   @/       -]";
                } else {
                    return "[   @/        ]";
                }
            } else if (i == 5) {
                if (leftRoad->getIsOwned() && rightRoad->getIsOwned()){
                    return "[- /|        -]";
                } else if(leftRoad->getIsOwned()){
                    return "[- /|         ]";
                } else if(rightRoad->getIsOwned()){
                    return "[  /|        -]";
                } else {
                    return "[  /|         ]";
                }
            } else if (i == 6) {
                if (leftRoad->getIsOwned() && rightRoad->getIsOwned()){
                    return "[- / \\       -]";
                } else if(leftRoad->getIsOwned()){
                    return "[- / \\        ]";
                } else if(rightRoad->getIsOwned()){
                    return "[  / \\       -]";
                } else {
                    return "[  / \\        ]";
                }
            } else {
                return "Should not be reached";
            }
        } else {
            if (leftRoad->getIsOwned() && rightRoad->getIsOwned()){
                return "[-           -]";
            } else if(leftRoad->getIsOwned()){
                return "[-            ]";
            } else if (rightRoad->getIsOwned()){
                return "[            -]";
            } else {
                return "[             ]";
            }
        }
    } else if (i == 7) {
        return "[     __      ]";
    } else if (i == 8) {
        return "[    /||\\     ]";
    } else if (i == 9){
        if(downRoad->getIsOwned()){
            return "[     |||     ]";
        } else {
            return "[             ]";
        }
    } else {
        return "End case should not be reached";
    }

}

int ClaimedTile::getTileClass() const
{
    return CLAIMED_TILE;
}