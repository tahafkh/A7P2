#include"NotFound.hpp"
using namespace std;
#define ERROR_MESSAGE "Not Found"
const char* NotFound::what() const throw(){
    return ERROR_MESSAGE;
}