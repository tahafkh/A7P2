#include"NotEnough.hpp"
using namespace std;
#include<sstream>
#include<iostream>
const char* NotEnough::what() const throw(){
    return type.c_str();
}
NotEnough::NotEnough(string type_){
    type = "Not Enough " + type_;
}