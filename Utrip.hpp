#ifndef UTRIP_H
#define UTRIP_H "UTRIP_H"
#include"PriceFilter.hpp"
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<functional>
class Hotel;
class User;
class Filter;
class Utrip{
public:
    Utrip();
    ~Utrip();
    void save_hotels_informations(std::string hotels_file_path);
    void save_ratings_informations(std::string ratings_file_path);
    void check_commands(std::string command);
private:
    User* logged_in_user;
    void check_post_command(std::stringstream& command_);
    void check_get_command(std::stringstream& command_);
    void check_delete_command(std::stringstream& command_);
    void check_delete_reserve_command(std::stringstream& command);
    void check_delete_filter_command(std::stringstream& command);
    void check_get_wallet_command(std::stringstream& command);
    void check_get_hotel_command(std::stringstream& command);
    void check_get_reserve_command(std::stringstream& command);
    void check_get_rating_command(std::stringstream& command);
    void check_get_comment_command(std::stringstream& command);
    void check_get_manual_weights_command(std::stringstream& command);
    void check_get_estimated_weights_command(std::stringstream& command);
    void check_post_signup_command(std::stringstream& command);
    void check_post_login_command(std::stringstream& command);
    void check_post_logout_command(std::stringstream& command);
    void check_post_wallet_command(std::stringstream& command);
    void check_post_filter_command(std::stringstream& command);
    void check_post_city_filter_command(std::stringstream& command);
    void check_post_star_filter_command(std::stringstream& command);
    void check_post_price_filter_command(std::stringstream& command);
    void check_post_room_filter_command(std::stringstream& command);
    void check_post_reserve_command(std::stringstream& command);
    void check_post_comment_command(std::stringstream& command);
    void check_post_rating_command(std::stringstream& command);
    void check_post_default_price_filter_command(std::stringstream& command);
    void check_post_sort_command(std::stringstream& command);
    void check_post_manual_weights_command(std::stringstream& command);
    void apply_new_sort(std::string property,std::string order);
    bool is_unique(std::string user_data,std::string data_type);
    void check_weights_validity(const std::vector<double>& weights);
    void logout();
    std::vector<Hotel*> apply_default_price_filter();
    void increase_wallet_value(double amount);
    void show_wallets(int count);
    void sort_hotels_by_default();
    void sort_hotels_by_personal_rating();
    void clear_filters();
    void add_new_filter(Filter* new_filter);
    void show_total_hotels();
    void show_reservations();
    void show_specific_hotel(std::string hotel_id);
    void check_completeness(const std::vector<std::string>& command_parts);
    void sign_up(std::string user_email,std::string username,std::string password);
    void login(std::string user_email,std::string user_password);
    User* find_user(std::string user_email,std::string user_password);
    Hotel* find_hotel(std::string hotel_id);
    void make_reservation(std::string hotel_id,std::string room_type,int quantity,int check_in,int check_out);
    void cancel_reservation(int reserve_id);
    void set_orders();
    std::vector<Hotel*> total_hotels;
    std::vector<Filter*> total_filters;
    std::vector<User*> total_users;
    DefaultPriceFilter* default_price_filter;
    bool has_activated_price_filter;
    bool has_activated_default_price_filter;
    bool has_activated_personal_rating_sort;
    std::string personal_rating_order;
    std::vector<int> save_rooms_numbers(std::stringstream& hotel_info);
    std::vector<int> save_rooms_prices(std::stringstream& hotel_info);
    std::map<std::string,std::function<bool(int , int)>> int_orders;
    std::map<std::string,std::function<bool(std::string,std::string)>> string_orders;
    std::map<std::string,std::function<bool(double,double)>> double_orders;
};
#endif