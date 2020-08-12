#ifndef USER_H
#define USER_H "USER_H"
#include<vector>
#include<string>
#include"Rating.hpp"
class Reserve;
class User{
public:
    User(std::string user_email,std::string user_password,std::string user_username);
    ~User();
    void make_reservation(Reserve* new_reserve);
    void cancel_reservation(int reserve_id);
    std::string get_email(){ return email;}
    std::string get_username(){ return username;}
    void increase_wallet_value(double amout);
    void show_wallets(int count);
    void show_reservations();
    void add_new_rating(Rating* new_rating);
    void activate_manual_weights(const std::vector<double>& weights);
    void deactivate_manual_weights();
    void show_manual_weights();
    void show_estimated_weights();
    double get_wallet(){ return wallet;}
    bool has_enough_reserves();
    double get_personal_rating(Hotel* selected_hotel);
    double calculate_reserves_average_price();
    double calculate_reserves_standard_deviation(double reserves_average_price);
    size_t get_password(){ return password;}
private:
    double truncate(double number);
    double calculate_weighted_mean(Rating* hotel_rating,const std::vector<double>& weights);
    double calculate_partial_derive(int weight_index,std::vector<double> weights,Rating* hotel_rating,double current_error_value);
    void update_weights(std::vector<double>& weights,const std::vector<double>& partial_derives_sum);
    std::vector<double> initialize_weights();
    std::vector<double> initialize_partial_derives_sum();
    double calculate_error_value(Rating* hotel_rating,double hotel_weighted_mean_rating);
    void estimate_weights();
    bool has_enough_ratings();
    int reservation_id;
    double wallet;
    std::vector<double> wallets;
    void add_wallet(){ wallets.push_back(wallet);}
    int generate_reservation_id(){ return reservation_id++;}
    std::string email;
    size_t password;
    std::string username;
    std::vector<Reserve*> reserves;
    std::vector<Rating*> ratings;
    bool has_activated_manual_weights;
    bool has_changes_in_ratings;
    std::vector<double> manual_weights;
    std::vector<double> estimated_weights; 
};
#endif