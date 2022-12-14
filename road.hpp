#ifndef ROAD_HPP
#define ROAD_HPP

#include <iostream>
#include <memory>
#include <string>


class Road
{
    protected:
        int owner_number;
        std::string owner_name;
        bool isOwned;

    public:
        Road(int, std::string);
        Road();
        bool getIsOwned();
        int getOwnerNumber();
        std::string getOwnerName();
        void setIsOwned(bool is_owned);
        void setOwnerNumber(int owenrNumber);
        void setOwnerName(std::string ownerName);

};

#endif