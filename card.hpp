#ifndef CARD_HPP
#define CARD_HPP

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