#ifndef ROOM_H
#define ROOM_H "ROOM_H"
#include<vector>
#include<string>
#include"Period.hpp"
class Reserve;
class Hotel;
class Room{
public:
   Room(std::string room_id,Hotel* hotel_);
   bool is_reserved(const Period& chosen_period) const;
   void cancel_reservation(Reserve* chosen_reserve);
   void add_reservation(Reserve* new_reserve){ reserves.push_back(new_reserve);}
   std::string get_id(){ return id;} 
private:
    std::vector<Reserve*> reserves;
    std::string id;
    Hotel* hotel;
};
#endif