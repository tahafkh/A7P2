#ifndef CITYFILTER_H
#define CITYFILTER_H "CITYFILTER_H"
#include"Filter.hpp"
#include<string>
class CityFilter : public Filter{
public:
    CityFilter(std::string city){ city_name = city;}
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    std::string city_name;
};
#endif