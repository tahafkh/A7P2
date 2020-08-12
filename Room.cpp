#include"Room.hpp"
#include"Reserve.hpp"
using namespace std;
bool Room::is_reserved(const Period& chosen_period) const{
    for(int i=0;i<reserves.size();i++){
        if(reserves[i]->get_period() == chosen_period){
            return true;
        }
    }
    return false;
}
Room::Room(string room_id,Hotel* hotel_){
    id = room_id;
    hotel = hotel_;
}
void Room::cancel_reservation(Reserve* chosen_reserve){
    for(int i=0;i<reserves.size();i++){
        if(chosen_reserve->get_id() == reserves[i]->get_id()){
            reserves.erase(reserves.begin() + i);
            return;
        }
    }
}