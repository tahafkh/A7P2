#ifndef PERIOD_H
#define PERIOD_H "PERIOD_H"
class Period{
public:
    Period();
    bool operator==(const Period& second_period) const;
    Period& operator=(const Period& second_period);
    Period(int check_in,int check_out);
    void print();
    int calculate_days() const{ return check_out_day - check_in_day +1;}
private:
    int check_in_day;
    int check_out_day;
};
#endif