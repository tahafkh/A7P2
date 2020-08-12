#include"PermissionDenied.hpp"
using namespace std;
#define ERROR_MESSAGE "Permission Denied"
const char* PermissionDenied::what() const throw(){
    return ERROR_MESSAGE;
}