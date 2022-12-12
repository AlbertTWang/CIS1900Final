#ifndef TILE_HPP
#define TILE_HPP

#define UNCLAIMED_TILE 1
#define CLAIMED_TILE 2
#define UPGRADED_TILE 3
#define PRINTING_LINE_NUMBERS 6

#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

enum TileType{WOOD, BRICK, WHEAT, SHEEP, ORE};

class Tile
{
    protected:
        int tile_owner;
        int tile_number;
        TileType tile_type;
    public:
        Tile(int, int, TileType);
        Tile();
        virtual ~Tile() = 0;
        int get_tile_owner();
        TileType get_tile_type();
        int get_tile_number();
        void set_tile_owner(int);
        void set_tile_number(int);
        void set_tile_type(TileType tile_type);
        virtual std::string print(int i) const = 0;
        virtual int getTileClass() const = 0;

};

#endif


