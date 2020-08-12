#ifndef RATING_H
#define RATING_H "RATING_H"
#include<vector>
class User;
class Hotel;
struct UserRating{
    UserRating(){};
    UserRating(const std::vector<double>& ratings_,User* user_,Hotel* hotel_){
        ratings = ratings_;
        user = user_;
        hotel = hotel_;
    }
    std::vector<double> ratings;
    User* user;
    Hotel* hotel;
};
typedef struct UserRating Rating;
#endif