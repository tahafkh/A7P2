#ifndef BADREQUEST_H
#define BADREQUEST_H "BADREQUEST_H"
#include<exception>
class BadRequest : public std::exception{
public:
    const char* what() const throw();
};
#endif