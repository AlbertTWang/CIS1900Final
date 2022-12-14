#include "road.hpp"


Road::Road(int ownerNumber, std::string ownerName)
{
    owner_name = ownerName;
    owner_number = ownerNumber;
    isOwned = true;
}

Road::Road()
{
    owner_name = -1;
    owner_name = "";
    isOwned = false;
}

bool Road::getIsOwned()
{
    return isOwned;
}

int Road::getOwnerNumber()
{
    return owner_number;
}

std::string Road::getOwnerName()
{
    return owner_name;
}

void Road::setIsOwned(bool is_owned)
{
    isOwned = is_owned;
}

void Road::setOwnerNumber(int ownerNumber)
{
    owner_number = ownerNumber;
}

void Road::setOwnerName(std::string ownerName)
{
    owner_name = ownerName;
}

