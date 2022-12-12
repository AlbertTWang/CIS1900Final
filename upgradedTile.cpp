#include "upgradedTile.hpp"
#include "tile.hpp"

UpgradedTile::UpgradedTile(int owner, int number, TileType tileType)
{
    tile_owner = owner;
    tile_number = number;
    tile_type = tileType;
};

std::string UpgradedTile::print(int i) const
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
    else if (i == 1 || i == 6){
        return "[ ----------- ]";
    } else if (i == 2) {
        std::string to_return = "[      " + std::to_string(tile_owner) + "      ]";
        return to_return;
    }
    else if (i == 3) {
        return "[      _      ]";
    } else if (i == 4) {
        return "[     /|\\     ]";
    } else if (i == 5){
        return "[    /|||\\    ]";
    }       
    return "End case should not be reached";

}

int UpgradedTile::getTileClass() const
{
    return UPGRADED_TILE;
}