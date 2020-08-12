#ifndef SAMETYPE_H 
#define SAMETYPE_H "SAMETYPE_H"
#include"Filter.hpp"
#include"Rating.hpp"
class SameFilterType{
public:
    SameFilterType(Filter* filter_);
    bool operator()(Filter* another_filter);
private:
    Filter* filter;
};
class SameRatingType{
public:
    SameRatingType(Rating* rating_);
    bool operator()(Rating* another_rating);
private:
    Rating* rating;
};
#endif