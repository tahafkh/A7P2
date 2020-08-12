#ifndef NOTFOUND_H
#define NOTFOUND_H "NOTFOUND_H"
#include<exception>
class NotFound : public std::exception{
public:
    const char* what() const throw();
};
#endif