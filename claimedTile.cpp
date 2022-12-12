#include "claimedTile.hpp"
#include "tile.hpp"

ClaimedTile::ClaimedTile(int owner, int number, TileType tileType)
{
    tile_owner = owner;
    tile_number = number;
    tile_type = tileType;
};

std::string ClaimedTile::print(int i) const
{
    if(i == 0){
        switch (tile_type){
            case WOOD:
                return "[** WOOD **] " + std::to_string(tile_number);
            case BRICK:
                return "[** BRICK **] " + std::to_string(tile_number);
            case SHEEP:
                return "[** SHEEP **] " + std::to_string(tile_number);
            case WHEAT:
                return "[** WHEAT **]" + std::to_string(tile_number);
            case ORE:
                return "[** ORE **] " + std::to_string(tile_number);
            
        }
    }
    else if(i == 1 || i == 6){
        return "[ ----------- ]";
    }
    else if(i == 2 || i == 4){
        return "[             ]";
    }
    else if(i == 3){
        std::string to_return = "[  Owned by:";
        to_return += std::to_string(tile_owner);
        to_return += "  ]";
        return to_return;

    }
    else if(i == 5){
        return "[     /||     ]";
    }       
    return "End case should not be reached";

}

int ClaimedTile::getTileClass() const
{
    return CLAIMED_TILE;
}