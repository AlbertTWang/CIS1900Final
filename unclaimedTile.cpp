#include "unclaimedTile.hpp"
#include "tile.hpp"


UnclaimedTile::UnclaimedTile(int owner, int number, TileType tileType, std::string ownerName, bool hasRobber)
{
    tile_owner = -100;
    tile_number = number;
    tile_type = tileType;
    owner_name = ownerName;
    hasRobber = false;

    upRoad = new Road();
    downRoad = new Road();
    leftRoad = new Road();
    rightRoad = new Road();
};


std::string UnclaimedTile::print(int i) const
{
    if (i == 0) {
        switch (tile_type) {
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
    else if (i == 1 || i == 10) {
        return "[ ----------- ]";
    }
    else {
        if (hasRobber) {
            if (i == 2 || i == 3 || i == 7 || i == 8 || i == 9) {
                return "[             ]";
            } else if (i == 4) {
                return "[   @/        ]";
            } else if (i == 5) {
                return "[  /|         ]";
            } else if (i == 6) {
                return "[  / \\        ]";
            } else {
                return "Should not be reached";
            }
        } else {
            return "[             ]";
        }
    }
}
int UnclaimedTile::getTileClass() const
{
    return UNCLAIMED_TILE;
}