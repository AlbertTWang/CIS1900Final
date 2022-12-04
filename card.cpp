#include "card.h"

Card::Card(CardType type)
{
    setType(type);
}

void Card::setType(CardType c)
{
    type = c;
}

CardType Card::getType()
{
    return type;
}