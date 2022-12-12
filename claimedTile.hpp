#ifndef CLAIMED_HPP
#define CLAIMED_HPP

#include "tile.hpp"

class ClaimedTile: public Tile
{
    public:
        ClaimedTile(int, int, TileType);
        std::string print(int i) const override;
        int getTileClass() const override;

};

#endif