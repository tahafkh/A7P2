#include"Period.hpp"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define SPACE " "
#define MIN_DAY 1
#include<iostream>
using namespace std;
bool Period::operator==(const Period& second_period) const{
    if(check_in_day<=second_period.check_out_day && check_out_day >= second_period.check_in_day){
        return true;
    }
    return false;
}
Period::Period(int check_in,int check_out){
    check_in_day = check_in;
    check_out_day = check_out;
}
Period& Period::operator=(const Period& second_period){
    check_in_day = second_period.check_in_day;
    check_out_day = second_period.check_out_day;
    return *this;
}
Period::Period(){
    check_in_day = MIN_DAY;
    check_out_day = MIN_DAY;
}
void Period::print(){
    cout<<CHECK_IN<<SPACE<<check_in_day<<SPACE<<CHECK_OUT<<SPACE<<check_out_day;
}