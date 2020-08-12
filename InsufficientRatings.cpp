#include"InsufficientRatings.hpp"
using namespace std;
#define ERROR_MESSAGE "Insufficient Ratings"
const char* InsufficientRatings::what() const throw(){
    return ERROR_MESSAGE;
}