#include "card.hpp"

Card::Card(int type)
{
    setType(type);
}

void Card::setType(int c)
{
    type = c;
}

int Card::getType()
{
    return type;
}