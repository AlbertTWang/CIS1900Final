#ifndef UPGRADEDTILE_HPP
#define UPGRADEDTILE_HPP

#include "tile.hpp"

class UpgradedTile: public Tile
{
    public:
        UpgradedTile(int, int, TileType, std::string);
        std::string print(int i) const override;
        int getTileClass() const override;
};

#endif