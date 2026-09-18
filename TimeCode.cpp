#include "TimeCode.h"
#include <stdexcept> // Gives us invalid_argument for throwing errors
#include <iostream>
#include <string>

using namespace std;

//changes hours, minute, and seconds into total seconds storing them in t.
unsigned long long TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
	unsigned long long t = 0;
	t = (3600ULL * hr) + (60ULL * min ) + sec;
	return t;
}

//this breaks teh seconds calculated above into hours and minutes again
void TimeCode::GetComponents(unsigned int& hr, unsigned int&min, unsigned int& sec) const{
	unsigned long long total = t;
	
	//Calculate full hrs 
	hr = total /3600;
	
	//Keep seconds after removing hours
	total = total % 3600;
	
	//Calculate minutes 
	min = total / 60;
	
	//the seconds left after calculating the minutes 
	sec = total % 60; 

}

//changes hours without changing minutes or seconds 
void TimeCode::SetHours(unsigned int hours) {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s); //calculate again total seconds with new hours
}

//just like the one above but instead of hours minutes
void TimeCode::SetMinutes(unsigned int minutes) {
	//if its more than sixty minutes (ex 71 given at the assignment prompt) then it throws an error
    if (minutes >= 60) {
        throw invalid_argument("Minutes must be less than 60");
    }
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

//same as the one above but instead of minutes seconds 
void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds >= 60) {
        throw invalid_argument("Seconds must be less than 60");
    }
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

void TimeCode::reset() {
    t = 0;
}

//constructor converts given hours, minutes, and seconds into total seconds t
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec) {
    t = ComponentsToSeconds(hr, min, sec);
}

//copy constructor copies total seconds from an existing TimeCode object into this new instance
//do this so it does not affect the initial t afetr changing it 
TimeCode::TimeCode(const TimeCode& tc) {
    t = tc.t;
}

//breaks t down into components and returns just the hours portion
unsigned int TimeCode::GetHours() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return h;
}

//breaks t down into components and returns just the leftover minutes
unsigned int TimeCode::GetMinutes() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return m;
}

//breaks t down into components and returns just the leftover minutes
unsigned int TimeCode::GetSeconds() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return s;
}

//makes teh components into a string
string TimeCode::ToString() const {
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return to_string(h) + ":" + to_string(m) + ":" + to_string(s);
}

//adds two timecodes togetehr
TimeCode TimeCode::operator+(const TimeCode& other) const {
    TimeCode result;
    result.t = t + other.t;
    return result;
}

//subtracts two timecodes
TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (t < other.t) {
		//throughs an error if it gives me a negative time 
        throw invalid_argument("TimeCode cannot be negative");
    }
    TimeCode result;
    result.t = t - other.t;
    return result;
}

//multiplies time code with a number
TimeCode TimeCode::operator*(double a) const {
    if (a < 0) {
		//again throws an error if the multiplier is negative 
        throw invalid_argument("Multiplier cannot be negative");
    }
    TimeCode result;
    result.t = (long long unsigned int)(t * a);
    return result;
}

//devides timecode with a number
TimeCode TimeCode::operator/(double a) const {
	//throws an error if that number is zero or negative
    if (a <= 0) {
        throw invalid_argument("Divisor must be greater than 0");
    }
    TimeCode result;
    result.t = (long long unsigned int)(t / a);
    return result;
}

bool TimeCode::operator==(const TimeCode& other) const { return t == other.t; }
bool TimeCode::operator!=(const TimeCode& other) const { return t != other.t; }
bool TimeCode::operator<(const TimeCode& other) const  { return t < other.t;  }
bool TimeCode::operator<=(const TimeCode& other) const { return t <= other.t; }
bool TimeCode::operator>(const TimeCode& other) const  { return t > other.t;  }
bool TimeCode::operator>=(const TimeCode& other) const { return t >= other.t; }


	
	
