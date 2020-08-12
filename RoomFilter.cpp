#include"RoomFilter.hpp"
#include"Hotel.hpp"
using namespace std;
RoomFilter::RoomFilter(string type,int room_quantity,Period period){
    room_type = type;
    quantity = room_quantity;
    chosen_period = period;
}
void RoomFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    vector<Room*> selected_rooms;
    for(int i=0;i<total_hotels.size();i++){
        if(total_hotels[i]->has_enough_room(room_type,chosen_period,quantity,selected_rooms)){
            filtered_hotels.push_back(total_hotels[i]);
        }
    }
}