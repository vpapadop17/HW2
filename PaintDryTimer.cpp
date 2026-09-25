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
	//This way i get the current clock time in seconds right now using time(0)
    time_t current_time = time(0); 
    //I find how many seconds have passed since the batch started drying
    long long int elapsed_seconds = current_time - dss.startTime;
    //I need to change the time to seconds so i use teh pointer to use the function from TimeCode.cpp
    long long int total_seconds = dss.timeToDry->GetTimeCodeAsSeconds();
    //The time its supposed to take initially minus the time we have now been waiting to see the remaining time
    long long int remaining = total_seconds - elapsed_seconds;
    //If time is up or negative, return 0 so we don't show negative seconds
    if (remaining < 0) {
        return 0;
    }
    
    //Return the actual seconds remaining
    return remaining;
}


string drying_snap_shot_to_string(DryingSnapShot dss){

    long long int remaining_sec = get_time_remaining(dss);
    string result = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) ";
    
    // 3. Check if the drying process is finished
    if (remaining_sec <= 0) {
        //If remaining time is 0 or less mark it and add to string "DONE!"
        result += "DONE!";
    } else {
        //Create a temporary TimeCode object out of remaining seconds
        TimeCode remaining_tc(0, 0, remaining_sec);
        result += "time remaining: " + remaining_tc.ToString();
    }
    
    return result;
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
	
	DryingSnapShot dss2;
	dss2.startTime = time(0) - 100;
	TimeCode tc_expired = TimeCode(0, 0, 10);
	dss2.timeToDry = &tc_expired;
	long long int ans2 = get_time_remaining(dss2);
	assert(ans2 == 0);
	
	DryingSnapShot dss3;
	dss3.startTime = time(0);
	TimeCode tc_long = TimeCode(0, 2, 0); //2 minutes is 120 seconds
	dss3.timeToDry = &tc_long;
	long long int ans3 = get_time_remaining(dss3);
	assert(ans3 > 119 && ans3 < 121);
	
	DryingSnapShot dss4;
	dss4.startTime = time(0) - 190; // Started 190 seconds ago
	TimeCode tc_expireddd = TimeCode(0, 0, 11); //Only needs 11 seconds
	dss4.timeToDry = &tc_expireddd;
	long long int ans4 = get_time_remaining(dss2);
	assert(ans4 == 0);
	


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	
	double sa_zero = get_sphere_sa(0.0);
	assert(sa_zero == 0.0);
	
	double sa_five = get_sphere_sa(5.0);
	assert(314.159 < sa_five && sa_five < 314.160);
	
	double sa_ten = get_sphere_sa(10.0);
	assert(1256.63 < sa_ten && sa_ten < 1256.64);
	
	double sa_three_point_six = get_sphere_sa(3.6);
	assert(162.860 < sa_three_point_six && sa_three_point_six < 162.861);
	
	double sa_one = get_sphere_sa(1.0);
	assert(12.5663 < sa_one && sa_one < 12.5664);
	
	double sa_neg = get_sphere_sa(-2.0);
	assert(50.2654 < sa_neg && sa_neg < 50.2655);


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	TimeCode *tc3 = compute_time_code(3661.0);
	assert(tc3->GetTimeCodeAsSeconds() == 3661);
	assert(tc3->ToString() == "1:1:1");
	delete tc3;
	
	TimeCode *tc4 = compute_time_code(137.2);
	assert(tc4->GetTimeCodeAsSeconds() == 137);
	//didnt work when i had it as 137.2 because decmal turns into integer and gets chopped off
	assert(tc4->ToString() == "0:2:17");
	delete tc4;
	
	TimeCode *tc5 = compute_time_code(10000);
	assert(tc5->GetTimeCodeAsSeconds() == 10000);
	assert(tc5->ToString() == "2:46:40");
	delete tc5;


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	
	tests();
	
	vector<DryingSnapShot> batches;
	char choice;//this will hold teh users selection
	while (true) {//this will run continuously until the user wants to quit
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		
		//how to get user input from terminal i searched on google and gave me this: https://www.w3schools.com/cpp/cpp_user_input.asp
		cin >> choice;
		
		//deals with the situation if teh user typed capital or lowercase 
		if (choice == 'A'||choice == 'a') {
			double radius;
            cout << "radius: ";
            cin >> radius;
            double sa = get_sphere_sa(radius);
            
            DryingSnapShot batch;
            batch.name = "Batch-" + to_string(rand());
            
            //when a new batch is created we set its time equal to zero to know the specific time it was placed in the drier basically in the get remaining it would be the time it is inside that we then subtract from current time 
            batch.startTime = time(0);
            batch.timeToDry = compute_time_code(sa);
            
            cout << batch.name << " (takes " << batch.timeToDry->ToString() << " to dry)" << endl;
            batches.push_back(batch);
            
        } else if (choice == 'V' || choice == 'v') {
			
			//counting backwards works better because if an item finishes, it gets deleted, the next item gets moved to the left and will be skipped
			//backwards works because removing position one only moves the items above and i have already checked that  
			for (int i = batches.size() - 1; i >= 0; i--) {
				cout << drying_snap_shot_to_string(batches[i]) << endl;
				if (get_time_remaining(batches[i]) <= 0) {
					
					//this prevents memory leak if the time is less than 0 meaning it has dried  
					delete batches[i].timeToDry;
					batches.erase(batches.begin() + i);
				}
			}
			
			cout << batches.size() << " batches being tracked." << endl;
				
		} else if (choice == 'Q' || choice == 'q') {
			for (int i = 0; i < batches.size(); i++) {
				delete batches[i].timeToDry;
			}
            batches.clear();
            
            break; 
        }
	}
	
	return 0;
}
