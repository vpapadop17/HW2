#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;


struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	// Replace with your code
	return 0;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	// Replace with your code
	return "";
}


double get_sphere_sa(double rad){
    return 4 * M_PI * rad * rad;
}


//this function takes the surface area and computes how long it needs to dry 
//it returns a pointer because we said that timecodes must not leak and we need 
//a pointer on teh heap that gets deleted specifically when we ask it to not after the function is executed 
TimeCode *compute_time_code(double surfaceArea){
	//needed to convert surface area from double to unisgned long long 
	unsigned long long sec = (unsigned long long)surfaceArea;
    return new TimeCode(0, 0, sec);
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	tests();
	return 0;
}
