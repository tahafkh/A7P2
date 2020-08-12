#include"CityFilter.hpp"
#include"Hotel.hpp"
using namespace std;
void CityFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    for(int i=0;i<total_hotels.size();i++){
        if(city_name == total_hotels[i]->get_city()){
            filtered_hotels.push_back(total_hotels[i]);
        }
    }
}