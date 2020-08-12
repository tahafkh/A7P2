#include"BadRequest.hpp"
using namespace std;
#define ERROR_MESSAGE "Bad Request"
const char* BadRequest::what() const throw(){
    return ERROR_MESSAGE;
}