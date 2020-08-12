#ifndef PRICEFILTER_H
#define PRICEFILTER_H "PRICEFILTER_H"
#include"Filter.hpp"
class PriceFilter : public Filter{
public:
    PriceFilter(double min_price_,double max_price_);
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    double min_price;
    double max_price;
};
class DefaultPriceFilter : public Filter{
public:
    void set_datas(double reserves_average_price,double reserves_standard_deviation);
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    double average_price;
    double standard_deviation;
};
#endif