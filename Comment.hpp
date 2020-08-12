#ifndef COMMENT_H
#define COMMENT_H "COMMENT_H"
#include<string>
class User;
class Comment{
public:
    Comment(std::string comment_,User* user_);
    void print();
private:
    std::string comment;
    User* user;
};
#endif