#include"Utrip.hpp"
using namespace std;
#include<fstream>
#include<iostream>
#include<algorithm>
#include<functional>
#include"Hotel.hpp"
#include"User.hpp"
#include"Comment.hpp"
#include"BadRequest.hpp"
#include"NotFound.hpp"
#include"PermissionDenied.hpp"
#include"CityFilter.hpp"
#include"RoomFilter.hpp"
#include"StarFilter.hpp"
#include"SameType.hpp"
#define COMMA_SEPERATOR ','
#define QUESTION_MARK "?"
#define EMAIL "email"
#define SPACE ' '
#define USERNAME "username"
#define PASSWORD "password"
#define MIN_WALLET_INCREASEMENT 0
#define MIN_NUMS 0
#define FIRST_FILTER_INDEX 0
#define EMPTY "Empty"
#define OK "OK"
#define POST "POST"
#define GET "GET"
#define DELETE "DELETE"
#define SIGNUP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define WALLET "wallet"
#define HOTELS "hotels"
#define FILTERS "filters"
#define RESERVES "reserves"
#define COMMENTS "comments"
#define RATINGS "ratings"
#define ID "id"
#define COUNT "count"
#define AMOUNT "amount"
#define HOTEL "hotel"
#define TYPE "type"
#define QUANTITY "quantity"
#define CHECK_IN "check_in"
#define CHECK_OUT "check_out"
#define CITY "city"
#define MIN_PRICE_ "min_price"
#define MIN_PRICE 0
#define MAX_PRICE "max_price"
#define MIN_STAR_ "min_star"
#define MIN_STAR 1
#define MAX_STAR_ "max_star"
#define MAX_STAR 5
#define COMMENT "comment"
#define LOCATION "location"
#define CLEANLINESS "cleanliness"
#define STAFF "staff"
#define FACILITIES "facilities"
#define VALUE_FOR_MONEY "value_for_money"
#define OVERALL_RATING "overall_rating"
#define DEFAULT_PRICE_FILTER "default_price_filter"
#define ACTIVE "active"
#define TRUE "true"
#define FALSE "false"
#define ASCENDING "ascending"
#define DESCENDING "descending"
#define SORT "sort"
#define PROPERTY "property"
#define ORDER "order"
#define NAME "name"
#define STAR_RATING "star_rating"
#define STANDARD_ROOM_PRICE "standard_room_price"
#define DELUXE_ROOM_PRICE "deluxe_room_price"
#define LUXURY_ROOM_PRICE "luxury_room_price"
#define PREMIUM_ROOM_PRICE "premium_room_price"
#define AVERAGE_ROOM_PRICE "average_room_price"
#define RATING_PERSONAL "rating_personal"
#define MANUAL_WEIGHTS "manual_weights"
#define ESTIMATED_WEIGHTS "estimated_weights"
#define ROOM_KEY_INDEX 0
#define MIN_WEIGHTS 1.0
#define MAX_WEIGHTS 5.0
Utrip::Utrip(){
    logged_in_user = NULL;
    has_activated_default_price_filter = true;
    has_activated_price_filter = false;
    has_activated_personal_rating_sort = false;
    default_price_filter = new DefaultPriceFilter;
    set_orders();
}
void Utrip::set_orders(){
    int_orders[ASCENDING] = less<int>();
    int_orders[DESCENDING] = greater<int>();
    string_orders[ASCENDING] = less<string>();
    string_orders[DESCENDING] = greater<string>();
    double_orders[ASCENDING] = less<double>();
    double_orders[DESCENDING] = greater<double>();
}
void Utrip::sort_hotels_by_default(){
    sort(total_hotels.begin(),total_hotels.end(),[](Hotel* first,Hotel* second){ return (first->get_id() < second->get_id());});
}
void Utrip::sort_hotels_by_personal_rating(){
    auto comparison = double_orders[personal_rating_order];
    User* user = logged_in_user;
    stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel* first,Hotel* second){
        double first_personal_rating = user->get_personal_rating(first) , second_personal_rating = user->get_personal_rating(second);
        if(first_personal_rating == second_personal_rating){
            return first->get_id() < second->get_id();
        }
        return comparison(first_personal_rating,second_personal_rating);
    });
}
void Utrip::save_hotels_informations(string hotels_file_path){
    ifstream hotels_file(hotels_file_path);
    string temperory,hotels_info,unique_id,property_name,hotel_star_rating,hotel_overview,property_amenities,city,latitude,longitude,image_url;
    getline(hotels_file,temperory);
    while(getline(hotels_file,hotels_info)){
        stringstream hotel_info(hotels_info);
        getline(hotel_info,unique_id,COMMA_SEPERATOR);
        getline(hotel_info,property_name,COMMA_SEPERATOR);
        getline(hotel_info,hotel_star_rating,COMMA_SEPERATOR);
        getline(hotel_info,hotel_overview,COMMA_SEPERATOR);
        getline(hotel_info,property_amenities,COMMA_SEPERATOR);
        getline(hotel_info,city,COMMA_SEPERATOR);
        getline(hotel_info,latitude,COMMA_SEPERATOR);
        getline(hotel_info,longitude,COMMA_SEPERATOR);
        getline(hotel_info,image_url,COMMA_SEPERATOR);
        vector<int> rooms_numbers = save_rooms_numbers(hotel_info);
        vector<int> rooms_prices = save_rooms_prices(hotel_info);
        total_hotels.push_back(new Hotel(unique_id,property_name,stoi(hotel_star_rating),hotel_overview,property_amenities,city,stod(latitude),stod(longitude),image_url,rooms_numbers,rooms_prices));        
    }
    sort_hotels_by_default();
}
vector<int> Utrip::save_rooms_numbers(stringstream& hotel_info){
    vector<int> hotel_rooms_numbers;
    string room_numbers;
    getline(hotel_info,room_numbers,COMMA_SEPERATOR);
    hotel_rooms_numbers.push_back(stoi(room_numbers));
    getline(hotel_info,room_numbers,COMMA_SEPERATOR);
    hotel_rooms_numbers.push_back(stoi(room_numbers));
    getline(hotel_info,room_numbers,COMMA_SEPERATOR);
    hotel_rooms_numbers.push_back(stoi(room_numbers));
    getline(hotel_info,room_numbers,COMMA_SEPERATOR);
    hotel_rooms_numbers.push_back(stoi(room_numbers));
    return hotel_rooms_numbers;
}
vector<int> Utrip::save_rooms_prices(stringstream& hotel_info){
    vector<int> hotel_rooms_prices;
    string room_price;
    getline(hotel_info,room_price,COMMA_SEPERATOR);
    hotel_rooms_prices.push_back(stoi(room_price));
    getline(hotel_info,room_price,COMMA_SEPERATOR);
    hotel_rooms_prices.push_back(stoi(room_price));
    getline(hotel_info,room_price,COMMA_SEPERATOR);
    hotel_rooms_prices.push_back(stoi(room_price));
    getline(hotel_info,room_price,COMMA_SEPERATOR);
    hotel_rooms_prices.push_back(stoi(room_price));
    return hotel_rooms_prices;
}
bool Utrip::is_unique(string user_data,string data_type){
    if(data_type == EMAIL){
        for(int i = 0;i<total_users.size();i++){
            if(user_data == total_users[i]->get_email()){
                return false;
            }
        }
        return true;
    }
    else if(data_type == USERNAME){
        for(int i=0;i<total_users.size();i++){
            if(user_data == total_users[i]->get_username()){
                return false;
            }
        }
        return true;
    }
}
void Utrip::sign_up(string user_email,string username,string password){
    if(!is_unique(user_email,EMAIL) || !is_unique(username,USERNAME)){
        throw BadRequest();
    }
    total_users.push_back(new User(user_email,password,username));
    logged_in_user = total_users.back();
    has_activated_default_price_filter = true;
    cout<<OK<<endl;
}
void Utrip::check_completeness(const vector<string>& command_parts){
    for(int i=0;i<command_parts.size();i++){
        if(command_parts[i].empty()){
            throw BadRequest();
        }
    }
}
User* Utrip::find_user(string user_email,string user_password){
    hash<string> hashed_password;
    auto selected_user = find_if(total_users.begin(),total_users.end(),[=](User* user){return user->get_email() == user_email 
    && user->get_password() == hashed_password(user_password);});
    if(selected_user != total_users.end()){
        return *selected_user;
    }
    return NULL;
}
void Utrip::login(string user_email,string user_password){
    if(logged_in_user != NULL){
        throw BadRequest();
    }
    User* chosen_user = find_user(user_email,user_password);
    if(chosen_user == NULL){
        throw BadRequest();
    }
    logged_in_user = chosen_user;
    has_activated_default_price_filter = true;
    cout<<OK<<endl;
}
void Utrip::logout(){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    clear_filters();
    logged_in_user->deactivate_manual_weights();
    logged_in_user = NULL;
    sort_hotels_by_default();
    cout<<OK<<endl;
}
void Utrip::increase_wallet_value(double amount){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    if(amount <= MIN_WALLET_INCREASEMENT){
        throw BadRequest();
    }
    logged_in_user->increase_wallet_value(amount);
    cout<<OK<<endl;
}
void Utrip::show_wallets(int count){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    logged_in_user->show_wallets(count);
}
void Utrip::show_total_hotels(){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    if(has_activated_personal_rating_sort){
        sort_hotels_by_personal_rating();
        has_activated_personal_rating_sort = false;
    }
    vector<Hotel*> to_be_shown_hotels;
    if(total_filters.size()==0){
        to_be_shown_hotels = apply_default_price_filter();
    }
    else{
        for(int i=0;i<total_filters.size();i++){
            if(i==FIRST_FILTER_INDEX){
                total_filters[i]->apply(apply_default_price_filter());
            }
            else{
                total_filters[i]->apply(total_filters[i-1]->get_filtered_hotels());
            }
        }
        to_be_shown_hotels = total_filters.back()->get_filtered_hotels();
    }
    for(int i=0;i<to_be_shown_hotels.size();i++){
        to_be_shown_hotels[i]->print_general_informations();
    }
    if(to_be_shown_hotels.size()==MIN_NUMS){
        cout<<EMPTY<<endl;
    }
}
Hotel* Utrip::find_hotel(string hotel_id){
    auto selected_hotel = find_if(total_hotels.begin(),total_hotels.end(),[=](Hotel* hotel){ return hotel->get_id() == hotel_id;});
    if(selected_hotel != total_hotels.end()){
        return *selected_hotel;
    }
    return NULL;
}
void Utrip::show_specific_hotel(string hotel_id){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    Hotel* chosen_hotel =find_hotel(hotel_id);
    if(chosen_hotel == NULL){
        throw NotFound();
    }
    chosen_hotel->print_specific_informations();
}
void Utrip::make_reservation(string hotel_id,string room_type,int quantity,int check_in,int check_out){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    Hotel* chosen_hotel = find_hotel(hotel_id);
    if(chosen_hotel == NULL){
        throw NotFound();
    }
    logged_in_user->make_reservation(chosen_hotel->make_reservation(room_type,quantity,check_in,check_out,logged_in_user->get_wallet()));
}
void Utrip::cancel_reservation(int reserve_id){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    logged_in_user->cancel_reservation(reserve_id);
    cout<<OK<<endl;
}
void Utrip::clear_filters(){
    for(int i=0;i<total_filters.size();i++){
        delete total_filters[i];
    }
    total_filters.clear();
    has_activated_price_filter = false;
}
void Utrip::show_reservations(){
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    logged_in_user->show_reservations();
}
void Utrip::check_commands(string command_){
    try{
        stringstream command(command_);
        string command_type;
        getline(command,command_type,SPACE);
        if(command_type == POST){
            check_post_command(command);
        }
        else if(command_type == GET){
            check_get_command(command);
        }
        else if(command_type == DELETE){
            check_delete_command(command);
        }
        else{
            throw BadRequest();
        }
    }catch(exception& except){
        cout<<except.what()<<endl;
    }
}
void Utrip::check_post_command(stringstream& command){
    string post_command_type;
    getline(command,post_command_type,SPACE);
    if(post_command_type == SIGNUP){
        check_post_signup_command(command);
    }
    else if(post_command_type == LOGIN){
        check_post_login_command(command);
    }
    else if(post_command_type == LOGOUT){
        check_post_logout_command(command);
    }
    else if(post_command_type == WALLET){
        check_post_wallet_command(command);
    }
    else if(post_command_type == FILTERS){
        check_post_filter_command(command);
    }
    else if(post_command_type == RESERVES){
        check_post_reserve_command(command);
    }
    else if(post_command_type == COMMENTS){
        check_post_comment_command(command);
    }
    else if(post_command_type == RATINGS){
        check_post_rating_command(command);
    }
    else if(post_command_type == DEFAULT_PRICE_FILTER){
        check_post_default_price_filter_command(command);
    }
    else if(post_command_type == SORT){
        check_post_sort_command(command);
    }
    else if(post_command_type == MANUAL_WEIGHTS){
        check_post_manual_weights_command(command);
    }
    else{
        throw NotFound();
    }
}
void Utrip::check_post_signup_command(stringstream& command){
    string mark,command_section,email,username,password;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == USERNAME){
            getline(command,username,SPACE);
        }
        else if(command_section == PASSWORD){
            getline(command,password,SPACE);
        }
        else if(command_section == EMAIL){
            getline(command,email,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{email,username,password});
    check_completeness(command_parts);
    sign_up(email,username,password);
}
void Utrip::check_post_login_command(stringstream& command){
    string mark,command_section,email,password;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == EMAIL){
            getline(command,email,SPACE);
        }
        else if(command_section == PASSWORD){
            getline(command,password,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{email,password});
    check_completeness(command_parts);
    login(email,password);
}
void Utrip::check_post_logout_command(stringstream& command){
    string command_section;
    getline(command,command_section,SPACE);
    if(!command_section.empty()){
        throw BadRequest();
    }
    logout();
}
void Utrip::check_post_wallet_command(stringstream& command){
    string mark,command_section,amount;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == AMOUNT){
            getline(command,amount,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{amount});
    check_completeness(command_parts);
    increase_wallet_value(stod(amount));
}
void Utrip::check_post_reserve_command(stringstream& command){
    string mark,command_section,hotel_id,room_type,quantity,check_in,check_out;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == HOTEL){
            getline(command,hotel_id,SPACE);
        }
        else if(command_section == TYPE){
            getline(command,room_type,SPACE);
        }
        else if(command_section == QUANTITY){
            getline(command,quantity,SPACE);
        }
        else if(command_section == CHECK_IN){
            getline(command,check_in,SPACE);
        }
        else if(command_section == CHECK_OUT){
            getline(command,check_out,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{hotel_id,room_type,quantity,check_in,check_out});
    check_completeness(command_parts);
    make_reservation(hotel_id,room_type,stoi(quantity),stoi(check_in),stoi(check_out));
}
void Utrip::check_post_filter_command(stringstream& command){
    string mark,command_section;
    getline(command,mark,SPACE);
    if(mark!= QUESTION_MARK){
        throw BadRequest();
    }
    auto position =command.tellg();
    getline(command,command_section,SPACE);
    if(command_section == MIN_PRICE_ || command_section == MAX_PRICE){
        command.seekg(position);
        check_post_price_filter_command(command);
    }
    else if(command_section == MIN_STAR_ || command_section == MAX_STAR_){
        command.seekg(position);
        check_post_star_filter_command(command);
    }
    else if(command_section == CITY){
        check_post_city_filter_command(command);
    }
    else if(command_section == TYPE || command_section == QUANTITY || command_section == CHECK_IN || command_section == CHECK_OUT){
        command.seekg(position);
        check_post_room_filter_command(command);
    }
    else{
        throw BadRequest();
    }
}
void Utrip::check_post_city_filter_command(stringstream& command){
    string city;
    vector<string> command_parts;
    getline(command,city);
    command_parts.push_back(city);
    check_completeness(command_parts);
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    add_new_filter(new CityFilter(city));
}
void Utrip::check_post_price_filter_command(stringstream& command){
    string min_price,max_price,command_section;
    double min_price_,max_price_;
    vector<string> command_parts;
    while(getline(command,command_section,SPACE)){
        if(command_section == MIN_PRICE_){
            getline(command,min_price,SPACE);
        }
        else if(command_section == MAX_PRICE){
            getline(command,max_price,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{min_price,max_price});
    check_completeness(command_parts);
    min_price_ = stod(min_price);
    max_price_ = stod(max_price);
    if(min_price_ < MIN_PRICE || max_price_ < min_price_){
        throw BadRequest();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    add_new_filter(new PriceFilter(min_price_,max_price_));
    has_activated_price_filter = true;
}
void Utrip::check_post_star_filter_command(stringstream& command){
    string min_star,max_star,command_section;
    int min_star_,max_star_;
    vector<string> command_parts;
    while(getline(command,command_section,SPACE)){
        if(command_section == MIN_STAR_){
            getline(command,min_star,SPACE);
        }
        else if(command_section == MAX_STAR_){
            getline(command,max_star,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{min_star,max_star});
    check_completeness(command_parts);
    min_star_ = stoi(min_star);
    max_star_ = stoi(max_star);
    if(min_star_ < MIN_STAR || max_star_ > MAX_STAR || min_star_ > max_star_){
        throw BadRequest();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    add_new_filter(new StarFilter(min_star_,max_star_));
}
void Utrip::check_post_room_filter_command(stringstream& command){
    string type,quantity,check_in,check_out,command_section;
    vector<string> command_parts;
    while(getline(command,command_section,SPACE)){
        if(command_section == TYPE){
            getline(command,type,SPACE);
        }
        else if(command_section == QUANTITY){
            getline(command,quantity,SPACE);
        }
        else if(command_section == CHECK_IN){
            getline(command,check_in,SPACE);
        }
        else if(command_section == CHECK_OUT){
            getline(command,check_out,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{type,quantity,check_in,check_out});
    check_completeness(command_parts);
    Period chosen_period(stoi(check_in),stoi(check_out));
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    add_new_filter(new RoomFilter(type,stoi(quantity),chosen_period));
}
void Utrip::check_post_comment_command(stringstream& command){
    string mark,hotel_id,comment,command_section;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == HOTEL){
            getline(command,hotel_id,SPACE);
        }
        else if(command_section == COMMENT){
            getline(command,comment,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{hotel_id,comment});
    check_completeness(command_parts);
    Hotel* selected_hotel = find_hotel(hotel_id);
    if(selected_hotel == NULL){
        throw NotFound();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    selected_hotel->add_new_comment(new Comment(comment,logged_in_user));
    cout<<OK<<endl;
}
void Utrip::check_post_rating_command(stringstream& command){
    string hotel_id,location,cleanliness,staff,facilities,value_for_money,overall_rating,mark,command_section;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == HOTEL){
            getline(command,hotel_id,SPACE);
        }
        else if(command_section == LOCATION){
            getline(command,location,SPACE);
        }
        else if(command_section == CLEANLINESS){
            getline(command,cleanliness,SPACE);
        }
        else if(command_section == STAFF){
            getline(command,staff,SPACE);
        }
        else if(command_section == FACILITIES){
            getline(command,facilities,SPACE);
        }
        else if(command_section == VALUE_FOR_MONEY){
            getline(command,value_for_money,SPACE);
        }
        else if(command_section == OVERALL_RATING){
            getline(command,overall_rating,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{hotel_id,location,cleanliness,staff,facilities,value_for_money,overall_rating});
    check_completeness(command_parts);
    Hotel* selected_hotel = find_hotel(hotel_id);
    if(selected_hotel == NULL){
        throw NotFound();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    vector<double> new_ratings;
    new_ratings.insert(new_ratings.end(),{stod(location),stod(cleanliness),stod(staff),stod(facilities),stod(value_for_money),stod(overall_rating)});
    auto new_rating = new Rating(new_ratings,logged_in_user,selected_hotel);
    selected_hotel->add_new_rating(new_rating);
    logged_in_user->add_new_rating(new_rating);
    cout<<OK<<endl;
}
void Utrip::check_post_default_price_filter_command(stringstream& command){
    string mark,command_section,activation_state;
    getline(command,mark,SPACE);
    if(mark!=QUESTION_MARK){
        throw BadRequest();
    }
    getline(command,command_section,SPACE);
    if(command_section!=ACTIVE){
        throw BadRequest();
    }
    getline(command,activation_state);
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    if(activation_state == TRUE){
        has_activated_default_price_filter = true;
    }
    else if(activation_state == FALSE){
        has_activated_default_price_filter = false;
    }
    else{
        throw BadRequest();
    }
    cout<<OK<<endl;
}
void Utrip::check_post_sort_command(stringstream& command){
    string mark,command_section,property,order;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark!=QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == PROPERTY){
            getline(command,property,SPACE);
        }
        else if(command_section == ORDER){
            getline(command,order,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{property,order});
    check_completeness(command_parts);
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    if(order!=ASCENDING && order!=DESCENDING){
        throw BadRequest();
    }
    apply_new_sort(property,order);
}
void Utrip::apply_new_sort(string property,string order){
    if(property == ID){
        auto comparison = string_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel* first,Hotel* second){ return comparison(first->get_id(),second->get_id()); });
    }
    else if(property == NAME){
        auto comparison = string_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel* first,Hotel* second){ if(first->get_name() == second->get_name()){ return first->get_id() < second->get_id();}
            return comparison(first->get_name(),second->get_name()); });
    }
    else if(property == CITY){
        auto comparison = string_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel*first,Hotel* second){ if(first->get_city() == second->get_city()){ return first->get_id() < second->get_id();}
            return comparison(first->get_city(),second->get_city()); });
    }
    else if(property == STAR_RATING){
        auto comparison = int_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel*first , Hotel* second){ if(first->get_star() == second->get_star()) { return first->get_id() < second->get_id();}
            return comparison(first->get_star(),second->get_star()); });
    }
    else if(property == STANDARD_ROOM_PRICE || property == DELUXE_ROOM_PRICE || property == LUXURY_ROOM_PRICE || property == PREMIUM_ROOM_PRICE){
        auto comparison = int_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel* first,Hotel* second){ if(first->get_room_price(property[ROOM_KEY_INDEX])==second->get_room_price(property[ROOM_KEY_INDEX])){
            return first->get_id() < second->get_id();
        }
            return comparison(first->get_room_price(property[ROOM_KEY_INDEX]),second->get_room_price(property[ROOM_KEY_INDEX])); });
    }
    else if(property == AVERAGE_ROOM_PRICE){
        auto comparison = double_orders[order];
        stable_sort(total_hotels.begin(),total_hotels.end(),[=](Hotel* first, Hotel* second){ if(first->get_average_price() == second->get_average_price()){ return first->get_id() < second->get_id();}
            return comparison(first->get_average_price(),second->get_average_price()); });
    }
    else if(property == RATING_PERSONAL){
        has_activated_personal_rating_sort = true;
        personal_rating_order = order;
    }
    else{
        throw BadRequest();
    }
    cout<<OK<<endl;
}
void Utrip::check_post_manual_weights_command(stringstream& command){
    string mark,command_section,active_state,location,cleanliness,staff,facilities,value_for_money;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == ACTIVE){
            getline(command,active_state,SPACE);
        }
        else if(command_section == LOCATION){
            getline(command,location,SPACE);
        }
        else if(command_section == CLEANLINESS){
            getline(command,cleanliness,SPACE);
        }
        else if(command_section == STAFF){
            getline(command,staff,SPACE);
        }
        else if(command_section == FACILITIES){
            getline(command,facilities,SPACE);
        }
        else if(command_section == VALUE_FOR_MONEY){
            getline(command,value_for_money,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    if(active_state == FALSE){
        logged_in_user->deactivate_manual_weights();
    }
    else if(active_state == TRUE){
        command_parts.insert(command_parts.end(),{location,cleanliness,staff,facilities,value_for_money});
        check_completeness(command_parts);
        vector<double> weights;
        transform(command_parts.begin(),command_parts.end(),back_inserter(weights),[](string command_part){ return stod(command_part);});
        check_weights_validity(weights);
        if(logged_in_user == NULL){
            throw PermissionDenied();
        }
        logged_in_user->activate_manual_weights(weights);
    }
    else{
        throw BadRequest();
    }
    cout<<OK<<endl;
}
void Utrip::check_weights_validity(const vector<double>& weights){
    auto invalid_weight_iterator = find_if(weights.begin(),weights.end(),[](double weight) { return weight > MAX_WEIGHTS || weight < MIN_WEIGHTS;});
    if(invalid_weight_iterator != weights.end()){
        throw BadRequest();
    }
}
void Utrip::check_get_command(stringstream& command){
    string get_command_type;
    getline(command,get_command_type,SPACE);
    if(get_command_type == WALLET){
        check_get_wallet_command(command);
    }
    else if(get_command_type == HOTELS){
        check_get_hotel_command(command);
    }
    else if(get_command_type == RESERVES){
        check_get_reserve_command(command);
    }
    else if(get_command_type == RATINGS){
        check_get_rating_command(command);
    }
    else if(get_command_type == COMMENTS){
        check_get_comment_command(command);
    }
    else if(get_command_type == MANUAL_WEIGHTS){
        check_get_manual_weights_command(command);
    }
    else if(get_command_type == ESTIMATED_WEIGHTS){
        check_get_estimated_weights_command(command);
    }
    else{
        throw NotFound();
    }
}
void Utrip::check_get_wallet_command(stringstream& command){
    string mark,command_section,count;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark!=QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == COUNT){
            getline(command,count,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{count});
    check_completeness(command_parts);
    show_wallets(stoi(count));
}
void Utrip::check_get_hotel_command(stringstream& command){
    string mark,command_section;
    getline(command,mark,SPACE);
    if(mark == QUESTION_MARK){
        string id;
        vector<string> command_parts;
        while(getline(command,command_section,SPACE)){
            if(command_section == ID){
                getline(command,id,SPACE);
            }
            else{
                throw BadRequest();
            }
        }
        command_parts.insert(command_parts.end(),{id});
        check_completeness(command_parts);
        show_specific_hotel(id);
    }
    else if(mark.empty()){
        show_total_hotels();
    }
    else{
        throw BadRequest();
    }
}
void Utrip::check_get_reserve_command(stringstream& command){
    string command_section;
    getline(command,command_section);
    if(!command_section.empty()){
        throw BadRequest();
    }
    show_reservations();
}
void Utrip::check_get_comment_command(stringstream& command){
    string hotel_id,command_section,mark;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == HOTEL){
            getline(command,hotel_id,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.push_back(hotel_id);
    check_completeness(command_parts);
    Hotel* selected_hotel = find_hotel(hotel_id);
    if(selected_hotel == NULL){
        throw NotFound();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    selected_hotel->show_comments();
}
void Utrip::check_get_rating_command(stringstream& command){
    string mark,hotel_id,command_section;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if( mark!=QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == HOTEL){
            getline(command,hotel_id,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.push_back(hotel_id);
    check_completeness(command_parts);
    Hotel* selected_hotel = find_hotel(hotel_id);
    if(selected_hotel == NULL){
        throw NotFound();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    selected_hotel->show_rating();
}
void Utrip::check_get_manual_weights_command(stringstream& command){
    string temperory;
    getline(command,temperory);
    if(!temperory.empty()){
        throw BadRequest();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    logged_in_user->show_manual_weights();
}
void Utrip::check_get_estimated_weights_command(stringstream& command){
    string temperory;
    getline(command,temperory);
    if(!temperory.empty()){
        throw BadRequest();
    }
    if(logged_in_user == NULL){
        throw PermissionDenied();
    }
    logged_in_user->show_estimated_weights();
}
void Utrip::check_delete_command(stringstream& command){
    string delete_command_type;
    getline(command,delete_command_type,SPACE);
    if(delete_command_type == RESERVES){
        check_delete_reserve_command(command);
    }
    else if(delete_command_type == FILTERS){
        check_delete_filter_command(command);
    }
    else{
        throw NotFound();
    }
}
void Utrip::check_delete_reserve_command(stringstream& command){
    string mark,command_section,id;
    vector<string> command_parts;
    getline(command,mark,SPACE);
    if(mark != QUESTION_MARK){
        throw BadRequest();
    }
    while(getline(command,command_section,SPACE)){
        if(command_section == ID){
            getline(command,id,SPACE);
        }
        else{
            throw BadRequest();
        }
    }
    command_parts.insert(command_parts.end(),{id});
    check_completeness(command_parts);
    cancel_reservation(stoi(id));
}
void Utrip::check_delete_filter_command(stringstream& command){
    string command_section;
    getline(command,command_section);
    if(!command_section.empty()){
        throw BadRequest();
    }
    clear_filters();
    cout<<OK<<endl;
}
Utrip::~Utrip(){
    for(int i=0;i<total_users.size();i++){
        delete total_users[i];
    }
    for(int i=0;i<total_hotels.size();i++){
        delete total_hotels[i];
    }
    clear_filters();
    delete default_price_filter;
}
void Utrip::add_new_filter(Filter* new_filter){
    auto same_filter_iterator = find_if(total_filters.begin(),total_filters.end(),SameFilterType(new_filter));
    if(same_filter_iterator != total_filters.end()){
        delete (*same_filter_iterator);
        total_filters.erase(same_filter_iterator);
    }
    total_filters.push_back(new_filter);
    cout<<OK<<endl;
}
void Utrip::save_ratings_informations(string ratings_file_path){
    ifstream ratings_file(ratings_file_path);
    string temperory,ratings_info,hotel_id;
    getline(ratings_file,temperory);
    while(getline(ratings_file,ratings_info)){
        stringstream rating_info(ratings_info);
        getline(rating_info,hotel_id,COMMA_SEPERATOR);
        Hotel* selected_hotel = find_hotel(hotel_id);
        if(selected_hotel == NULL){
            throw NotFound();
        }
        selected_hotel->save_average_rating(rating_info);
    }
}
vector<Hotel*> Utrip::apply_default_price_filter(){
    if(!has_activated_price_filter && has_activated_default_price_filter && logged_in_user->has_enough_reserves()){
        double reserves_average_price = logged_in_user->calculate_reserves_average_price();
        default_price_filter->set_datas(reserves_average_price,logged_in_user->calculate_reserves_standard_deviation(reserves_average_price));
        default_price_filter->apply(total_hotels);
        return default_price_filter->get_filtered_hotels();
    }
    else{
        return total_hotels;
    }
}