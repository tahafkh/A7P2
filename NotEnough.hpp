#ifndef NOTENOUGH_H
#define NOTENOUGH_H "NOTENOUGH_H"
#include<exception>
#include<string>
class NotEnough : public std::exception{
public:
    NotEnough(std::string type_);
    const char* what() const throw();
private:
    std::string type;
};
#endif