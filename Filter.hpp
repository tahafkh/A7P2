#ifndef FILTER_H
#define FILTER_H "FILTER_H"
#include<vector>
class Hotel;
class Filter{
public:
    virtual void apply(const std::vector<Hotel*>& total_hotels) = 0;
    std::vector<Hotel*> get_filtered_hotels(){ return filtered_hotels;}
protected:
    std::vector<Hotel*> filtered_hotels;
};
#endif