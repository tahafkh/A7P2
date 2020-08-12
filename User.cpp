#include"User.hpp"
#include"Reserve.hpp"
#include"NotFound.hpp"
#include"Hotel.hpp"
#include"InsufficientRatings.hpp"
using namespace std;
#include<iostream>
#include<cmath>
#include<functional>
#include<algorithm>
#include<iomanip>
#include<numeric>
#include<random>
#define FIRST_RESERVE_ID 1
#define INITAL_WALLET 0
#define INITIAL_SUM 0
#define INITIAL_DOUBLE_SUM 0.0
#define EMPTY "Empty"
#define MIN_RESERVES 0
#define MIN_RESERVES_FOR_DEFAULT_PRICE_FILTER 10
#define MIN_RATINGS_FOR_ESTIMATION 5
#define OVERALL_RATING_INDEX 5
#define LOGICAL_LOOP_REPETITION 1000
#define EPSILON 0.0001
#define STEP_SIZE 1
#define WEIGHTS_NUMS 5
#define MIN_WEIGHTS 1.0
#define MAX_WEIGHTS 5.0
#define PRECISION 2
#define LOCATION_WEIGHT_INDEX 0
#define CLEANLINESS_WEIGHT_INDEX 1
#define STAFF_WEIGHT_INDEX 2
#define FACILITIES_WEIGHT_INDEX 3
#define VALUE_FOR_MONEY_WEIGHT_INDEX 4
#define TENS_FOR_TRUNCATE 100
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define TRUE "true"
#define FALSE "false"
#define ACTIVE "active"
User::User(string user_email,string user_password,string user_username){
    hash<string> hashed_password;
    email = user_email;
    password = hashed_password(user_password);
    username = user_username;
    reservation_id = FIRST_RESERVE_ID;
    wallet = INITAL_WALLET;
    has_changes_in_ratings = true;
    has_activated_manual_weights = false;
    add_wallet();
}
void User::make_reservation(Reserve* new_reserve){
    new_reserve->set_id(generate_reservation_id());
    wallet -= new_reserve->get_cost();
    add_wallet();
    reserves.push_back(new_reserve);
}
void User::cancel_reservation(int reserve_id){
    for(int i=0;i<reserves.size();i++){
        if(reserve_id == reserves[i]->get_id()){
            reserves[i]->cancel_reservation();
            wallet += (double)(reserves[i]->get_cost())/2;
            add_wallet();
            delete reserves[i];
            reserves.erase(reserves.begin() + i);
            return;
        }
    }
    throw NotFound();
}
void User::increase_wallet_value(double amount){
    wallet+=amount;
    add_wallet();
}
void User::show_wallets(int count){
    int wallet_nums = count > wallets.size() ? wallets.size() : count;
    for(int i=0;i<wallet_nums;i++){
        cout<<(int)round(wallets[wallets.size()-1-i])<<endl;
    }
}
void User::show_reservations(){
    for(int i=0;i<reserves.size();i++){
        reserves[reserves.size() - i -1]->print();
    }
    if(reserves.size() == MIN_RESERVES){
        cout<<EMPTY<<endl;
    }
}
User::~User(){
    for(int i=0;i<reserves.size();i++){
        delete reserves[i];
    }
}
double User::calculate_reserves_average_price(){
    vector<int> raw_reserves_prices;
    transform(reserves.begin(),reserves.end(),back_inserter(raw_reserves_prices),[](Reserve* reserve){ return reserve->get_total_raw_cost();});
    int total_prices_sum = accumulate(raw_reserves_prices.begin(),raw_reserves_prices.end(),INITIAL_SUM);
    vector<int> reserves_rooms_nums;
    transform(reserves.begin(),reserves.end(),back_inserter(reserves_rooms_nums),[](Reserve* reserve){ return reserve->get_room_nums();});
    int total_rooms = accumulate(reserves_rooms_nums.begin(),reserves_rooms_nums.end(),INITIAL_SUM);
    return (double)total_prices_sum/total_rooms;
}
double User::calculate_reserves_standard_deviation(double reserves_average_price){
    vector<double> square_price_differences;
    transform(reserves.begin(),reserves.end(),back_inserter(square_price_differences),[=](Reserve* reserve){
        return (double)(reserve->get_room_price() - reserves_average_price)*(reserve->get_room_price() - reserves_average_price)*(reserve->get_room_nums());
    });
    double square_price_differences_sum = accumulate(square_price_differences.begin(),square_price_differences.end(),INITIAL_DOUBLE_SUM);
    vector<int> reserves_rooms_nums;
    transform(reserves.begin(),reserves.end(),back_inserter(reserves_rooms_nums),[](Reserve* reserve){ return reserve->get_room_nums();});
    int total_rooms = accumulate(reserves_rooms_nums.begin(),reserves_rooms_nums.end(),INITIAL_SUM);
    total_rooms--;
    return sqrt(square_price_differences_sum/total_rooms);
}
bool User::has_enough_reserves(){
    return reserves.size() >= MIN_RESERVES_FOR_DEFAULT_PRICE_FILTER;
}
void User::add_new_rating(Rating* new_rating){
    auto same_rating_iterator = find_if(ratings.begin(),ratings.end(),[=](Rating* rating){ return new_rating->hotel == rating->hotel;});
    if(same_rating_iterator != ratings.end()){
        ratings.erase(same_rating_iterator);
    }
    ratings.push_back(new_rating);
    has_changes_in_ratings =  true;
}
bool User::has_enough_ratings(){
    return ratings.size() >= MIN_RATINGS_FOR_ESTIMATION;
}
double User::calculate_weighted_mean(Rating* hotel_rating,const vector<double>& weights){
    vector<double> weighted_sums;
    transform(weights.begin(),weights.end(),hotel_rating->ratings.begin(),back_inserter(weighted_sums),[](double weight,double rating){ return weight*rating ;});
    double weighted_sum = accumulate(weighted_sums.begin(),weighted_sums.end(),INITIAL_DOUBLE_SUM);
    double weights_sum = accumulate(weights.begin(),weights.end(),INITIAL_DOUBLE_SUM);
    return weighted_sum/weights_sum;
}
double User::get_personal_rating(Hotel* selected_hotel){
    auto selected_hotel_rating_iterator = find_if(ratings.begin(),ratings.end(),[=](Rating* rating){ return rating->hotel == selected_hotel ;});
    if(selected_hotel_rating_iterator != ratings.end()){
        return (*selected_hotel_rating_iterator)->ratings[OVERALL_RATING_INDEX];
    }
    if(has_activated_manual_weights){
        return calculate_weighted_mean(selected_hotel->get_average_rating(),manual_weights);        
    }
    if(!has_enough_ratings()){
        throw InsufficientRatings();
    }
    if(has_changes_in_ratings){
        estimate_weights();
    }
    return calculate_weighted_mean(selected_hotel->get_average_rating(),estimated_weights);
}
vector<double> User::initialize_weights(){
    vector<double> weights(WEIGHTS_NUMS);
    random_device random_seed;
    mt19937 engine(random_seed());
    uniform_real_distribution<double> random_maker(MIN_WEIGHTS,MAX_WEIGHTS);
    generate(weights.begin(),weights.end(),[&](){ return random_maker(engine);});
    return weights;
}
vector<double> User::initialize_partial_derives_sum(){
    vector<double> partial_derives_sum(WEIGHTS_NUMS,INITIAL_DOUBLE_SUM);
    return partial_derives_sum;
}
double User::calculate_error_value(Rating* hotel_rating,double hotel_weighted_mean_rating){
    return (hotel_weighted_mean_rating - hotel_rating->ratings[OVERALL_RATING_INDEX])*(hotel_weighted_mean_rating - hotel_rating->ratings[OVERALL_RATING_INDEX]);
}
double User::calculate_partial_derive(int weight_index,vector<double> weights,Rating* hotel_rating,double current_error_value){
    weights[weight_index]+=EPSILON;
    return (calculate_error_value(hotel_rating,calculate_weighted_mean(hotel_rating,weights)) - current_error_value)/EPSILON;
}
void User::update_weights(vector<double>& weights,const vector<double>& partial_derives_sum){
    transform(weights.begin(),weights.end(),partial_derives_sum.begin(),weights.begin(),[](double weight,double sum){ 
        double new_weight = weight - STEP_SIZE*sum;
        if(new_weight > MAX_WEIGHTS){
            new_weight = MAX_WEIGHTS;
        }
        else if(new_weight < MIN_WEIGHTS){
            new_weight = MIN_WEIGHTS;
        }
        return new_weight;
    });
}
void User::estimate_weights(){
    estimated_weights.clear();
    vector<double> weights = initialize_weights();
    vector<double> partial_derives_sum;
    double current_error_value;
    for(int i=0;i<LOGICAL_LOOP_REPETITION;i++){
        partial_derives_sum = initialize_partial_derives_sum();
        for(int j=0;j<ratings.size();j++){
            current_error_value = calculate_error_value(ratings[j],calculate_weighted_mean(ratings[j],weights));
            for(int k=0;k<weights.size();k++){
                partial_derives_sum[k] += calculate_partial_derive(k,weights,ratings[j],current_error_value);
            }
        }
        update_weights(weights,partial_derives_sum);
    }
    estimated_weights = weights;
    has_changes_in_ratings = false;
}
void User::activate_manual_weights(const vector<double>& weights){
    has_activated_manual_weights = true;
    manual_weights = weights;
}
void User::deactivate_manual_weights(){
    has_activated_manual_weights = false;
    manual_weights.clear();
}
double User::truncate(double number){
    return floor(number*TENS_FOR_TRUNCATE)/TENS_FOR_TRUNCATE;
}
void User::show_manual_weights(){
    if(!has_activated_manual_weights){
        cout<<ACTIVE<<" "<<FALSE<<endl;
        return;
    }
    cout<<ACTIVE<<" "<<TRUE<<" ";
    cout<<LOCATION<<" "<<fixed<<setprecision(PRECISION)<<truncate(manual_weights[LOCATION_WEIGHT_INDEX])<<" ";
    cout<<CLEANLINESS<<" "<<fixed<<setprecision(PRECISION)<<truncate(manual_weights[CLEANLINESS_WEIGHT_INDEX])<<" ";
    cout<<STAFF<<" "<<fixed<<setprecision(PRECISION)<<truncate(manual_weights[STAFF_WEIGHT_INDEX])<<" ";
    cout<<FACILITIES<<" "<<fixed<<setprecision(PRECISION)<<truncate(manual_weights[FACILITIES_WEIGHT_INDEX])<<" ";
    cout<<VALUE_FOR_MONEY<<" "<<fixed<<setprecision(PRECISION)<<truncate(manual_weights[VALUE_FOR_MONEY_WEIGHT_INDEX])<<endl;
}
void User::show_estimated_weights(){
    if(!has_enough_ratings()){
        throw InsufficientRatings();
    }
    if(has_changes_in_ratings){
        estimate_weights();
    }
    cout<<LOCATION<<" "<<fixed<<setprecision(PRECISION)<<truncate(estimated_weights[LOCATION_WEIGHT_INDEX])<<" ";
    cout<<CLEANLINESS<<" "<<fixed<<setprecision(PRECISION)<<truncate(estimated_weights[CLEANLINESS_WEIGHT_INDEX])<<" ";
    cout<<STAFF<<" "<<fixed<<setprecision(PRECISION)<<truncate(estimated_weights[STAFF_WEIGHT_INDEX])<<" ";
    cout<<FACILITIES<<" "<<fixed<<setprecision(PRECISION)<<truncate(estimated_weights[FACILITIES_WEIGHT_INDEX])<<" ";
    cout<<VALUE_FOR_MONEY<<" "<<fixed<<setprecision(PRECISION)<<truncate(estimated_weights[VALUE_FOR_MONEY_WEIGHT_INDEX])<<endl;
}