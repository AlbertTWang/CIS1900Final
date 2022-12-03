#ifndef CARD_H
#define CARD_H

class Card
{
    private:
        int type;
        
    public:
        Card(int);
        void setType(int);
        int getType();
};

#endif