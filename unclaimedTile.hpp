#ifndef UNCLAIMED_HPP
#define UNCLAIMED_HPP

#include "tile.hpp"

class UnclaimedTile : public Tile
{
    public:
        UnclaimedTile(int, int, TileType, std::string);
        std::string print(int i) const override;
        int getTileClass() const override;
};

#endif