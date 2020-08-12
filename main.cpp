#include"Utrip.hpp"
#include<iostream>
using namespace std;
#define HOTELS_FILE_PATH_INDEX 1
#define RATINGS_FILE_PATH_INDEX 2
int main(int argc,char* argv[]){
    Utrip utrip;
    utrip.save_hotels_informations(argv[HOTELS_FILE_PATH_INDEX]);
    utrip.save_ratings_informations(argv[RATINGS_FILE_PATH_INDEX]);
    string command;
    while(getline(cin,command)){
        utrip.check_commands(command);
    }
    return 0;
}