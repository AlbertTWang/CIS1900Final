#include "unclaimedTile.hpp"
#include "tile.hpp"

UnclaimedTile::UnclaimedTile(int owner, int number, TileType tileType)
{
    tile_owner= -100;
    tile_number = number;
    tile_type = tileType;
};


std::string UnclaimedTile::print(int i) const
{
    if(i == 0){
        switch (tile_type){
            case WOOD:
                return "[// WOOD // ] " + std::to_string(tile_number);
            case BRICK:
                return "[// BRICK // ] " + std::to_string(tile_number);
            case SHEEP:
                return "[// SHEEP // ] " + std::to_string(tile_number);
            case WHEAT:
                return "[// WHEAT // ]" + std::to_string(tile_number);
            case ORE:
                return "[// ORE // ] " + std::to_string(tile_number);
            
        }
    }
    else if(i == 1 || i == 6)
    {
        return "[ ----------- ]";
    }
    else if(i == 2 || i == 3 || i == 4 || i == 5)
    {
        return "[             ]";
    }
    return "End case should not be reached";

}
int UnclaimedTile::getTileClass() const
{
    return UNCLAIMED_TILE;
}