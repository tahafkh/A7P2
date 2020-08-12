#include"StarFilter.hpp"
#include"Hotel.hpp"
using namespace std;
StarFilter::StarFilter(int min_star_,int max_star_){
    min_star = min_star_;
    max_star = max_star_;
}
void StarFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    for(int i=0;i<total_hotels.size();i++){
        if(min_star<=total_hotels[i]->get_star() && max_star>=total_hotels[i]->get_star()){
            filtered_hotels.push_back(total_hotels[i]);
        }
    }
}