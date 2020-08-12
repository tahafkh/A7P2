#ifndef RESERVE_H 
#define RESERVE_H "RESERVE_H"
#include"Period.hpp"
#include<vector>
#include<string>
class Room;
class Reserve{
public:
    Reserve(int reserve_cost,std::string hotel_id_,std::string reserved_room_type,const Period& period_,std::vector<Room*> rooms);
    void cancel_reservation();
    void set_id(int reserve_id){ id = reserve_id;}
    int get_id(){return id;}
    void print();
    int get_cost(){ return cost;}
    int get_total_raw_cost(){ return cost/reserve_period.calculate_days();}
    int get_room_price(){ return (cost/reserve_period.calculate_days())/reserved_rooms.size();}
    int get_room_nums(){ return reserved_rooms.size();}
    Period get_period(){ return reserve_period;}
private:
    int cost;
    std::string hotel_id;
    std::string room_type;
    Period reserve_period;
    std::vector<Room*> reserved_rooms;
    int id;
};
#endif