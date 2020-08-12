#ifndef PERMISIIONDENIED_H
#define PERMISSIONDENIED_H "PERMISSIONdENIED_H"
#include<exception>
class PermissionDenied : public std::exception{
public:
    const char* what() const throw();
};
#endif