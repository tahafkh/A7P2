#include"Reserve.hpp"
#include"Room.hpp"
using namespace std;
#include<iostream>
Reserve::Reserve(int reserve_cost,string hotel_id_,string reserved_room_type,const Period& period_,vector<Room*> rooms){
    cost = reserve_cost;
    hotel_id = hotel_id_;
    room_type = reserved_room_type;
    reserve_period = period_;
    reserved_rooms = rooms;
}
void Reserve::cancel_reservation(){
    for(int i=0;i<reserved_rooms.size();i++){
        reserved_rooms[i]->cancel_reservation(this);
    }
}
void Reserve::print(){
    cout<<"id: "<<id<<" hotel: "<<hotel_id<<" room: "<<room_type<<" quantity: "<<reserved_rooms.size()<<" cost: "<<cost<<" ";
    reserve_period.print();
    cout<<endl;
}