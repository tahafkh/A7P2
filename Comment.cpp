#include"Comment.hpp"
#include"User.hpp"
using namespace std;
#include<iostream>
Comment::Comment(string comment_,User* user_){
    comment = comment_;
    user = user_;
}
void Comment::print(){
    cout<<user->get_username()<<": "<<comment<<endl;
}
