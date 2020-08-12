#ifndef HOTEL_H
#define HOTEL_H "HOTEL_H"
#include<string>
#include<vector>
#include<map>
#include"Rating.hpp"
class Reserve;
class Room;
class Period;
class Comment; 
class Hotel{
public:
    Hotel(std::string id,std::string name,int rating,std::string hotel_overview,std::string amenities,std::string hotel_city,double hotel_latitude,double hotel_longitude,std::string hotel_image_url,std::vector<int> rooms_numbers,std::vector<int> rooms_prices);
    ~Hotel();
    void print_general_informations();
    void print_specific_informations();
    Reserve* make_reservation(std::string room_type,int quanitity,int check_in,int check_out,double user_wallet);
    std::string get_id(){ return unique_id;}
    Rating* get_average_rating(){ return average_rating;}
    std::string get_city(){ return city;}
    std::string get_name(){ return property_name;}
    int get_room_price(char key){ return total_rooms_prices[key];}
    void add_new_comment(Comment* new_comment);
    void show_comments();
    void add_new_rating(Rating* new_rating);
    void show_rating();
    void save_average_rating(std::stringstream& rating_informations);
    int get_star(){ return star_rating;}
    double get_average_price(){ return average_price;}
    bool has_enough_room(std::string room_type,const Period& chosen_period,int quantity,std::vector<Room*>& selected_rooms);
private:
    void compute_average_price();
    int compute_total_rooms();
    void determine_rooms(std::vector<int> rooms_numbers);
    void determine_prices(std::vector<int> rooms_prices);
    void print_rooms_numbers();
    void print_rooms_prices();
    std::string generate_id(char room_key,int index);
    std::string unique_id;
    int calculate_reserve_cost(std::string room_type,const Period& chosen_period,int quantity);
    std::string property_name;
    int star_rating;
    std::string overview;
    std::string property_amenities;
    std::string city;
    double latitude;
    double longitude;
    std::string image_url;
    std::vector<std::vector<Room*>> total_rooms;
    std::vector<Rating*> total_ratings;
    std::vector<Comment*> total_comments;
    Rating* average_rating;
    std::vector<char> total_rooms_keys;
    std::map<char,int> total_rooms_prices;
    std::map<char,int> total_rooms_indexes;
    double average_price;
};
#endif