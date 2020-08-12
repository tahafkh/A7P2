#include"PriceFilter.hpp"
#include"Hotel.hpp"
#include<cmath>
#include<iostream>
#define DEFAULT_PRICE_FILTER_MESSAGE "* Results have been filtered by the default price filter."
using namespace std;
PriceFilter::PriceFilter(double min_price_,double max_price_){
    min_price = min_price_;
    max_price = max_price_;
}
void PriceFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    double hotel_average_price;
    for(int i=0;i<total_hotels.size();i++){
        hotel_average_price = total_hotels[i]->get_average_price();
        if(hotel_average_price >= min_price && hotel_average_price <= max_price){
            filtered_hotels.push_back(total_hotels[i]);
        }
    }
}
void DefaultPriceFilter::set_datas(double reserves_average_price,double reserves_standard_deviation){
    average_price = reserves_average_price;
    standard_deviation = reserves_standard_deviation;
}
void DefaultPriceFilter::apply(const vector<Hotel*>& total_hotels){
    filtered_hotels.clear();
    cout<<DEFAULT_PRICE_FILTER_MESSAGE<<endl;
    for(auto hotel : total_hotels){
        if(abs(hotel->get_average_price() - average_price) <= 2*standard_deviation){
            filtered_hotels.push_back(hotel);
        }
    }
}