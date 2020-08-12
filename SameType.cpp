#include"SameType.hpp"
#include<typeinfo>
using namespace std;
SameFilterType::SameFilterType(Filter* filter_){
    filter = filter_;
}
bool SameFilterType::operator()(Filter* another_filter){
    return (typeid(*filter) == typeid(*another_filter));
}
SameRatingType::SameRatingType(Rating* rating_){
    rating = rating_;
}
bool SameRatingType::operator()(Rating* another_rating){
    return (rating->user == another_rating->user);
}