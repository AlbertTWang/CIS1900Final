#ifndef CARD_H
#define CARD_H

enum CardType{KNIGHT, YOP, ROADBUILDING, MONOPOLY, VP};

class Card
{
    private:
        CardType type;
        
    public:
        Card(int);
        void setType(CardType);
        CardType getType();
};

#endif