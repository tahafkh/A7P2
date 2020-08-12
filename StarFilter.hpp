#ifndef STARFILTER_H
#define STARFILTER_H "STARFILTER_H"
#include"Filter.hpp"
class StarFilter : public Filter{
public:
    StarFilter(int min_star_,int max_star_);
    void apply(const std::vector<Hotel*>& total_hotels);
private:
    int min_star;
    int max_star;
};
#endif