#include <iostream>
#include <iomanip>
#include "tile.hpp"
#include "player.hpp"

Tile::Tile(int owner, int number, TileType tileType, std::string ownerName)
{
    tile_owner = owner;
    tile_number = number;
    tile_type = tileType;
    owner_name = ownerName;
};

Tile::Tile()
{
}

Tile::~Tile(){};

int Tile::get_tile_owner()
{
    return tile_owner;
}
int Tile::get_tile_number()
{
    return tile_number;
}
TileType Tile::get_tile_type()
{
    return tile_type;
}

std::string Tile::get_owner_name()
{
    return owner_name;
}
void Tile::set_tile_number(int tileNumber)
{
    tile_number = tileNumber;
}

void Tile::set_tile_owner(int tileOwner)
{
    tile_owner = tileOwner;
}

void Tile::set_tile_type(TileType tileType)
{
    tile_type = tileType;
}

void Tile::set_owner_name(std::string ownerName)
{
    owner_name = ownerName;
}

std::string print(int i)
{
    return "Weird";
}

int getTileClass(){
    return -1;
}
