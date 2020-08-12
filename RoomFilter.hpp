#ifndef ROOMFILTER_H
#define ROOMFILTER_H "ROOMFILTER_H"
#include"Filter.hpp"
#include"Period.hpp"
#include<string>
class RoomFilter : public Filter{
public:
    RoomFilter(std::string type,int room_quantity,Period period);
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    std::string room_type;
    int quantity;
    Period chosen_period;
};
#endif