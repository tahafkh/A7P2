#ifndef INSUFFICIENTRATINGS_H
#define INSUFFICIENTRATINGS_H "BADREQUEST_H"
#include<exception>
class InsufficientRatings : public std::exception{
public:
    const char* what() const throw();
};
#endif