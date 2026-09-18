
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"

//for me: Makes sure that the formula to convert hours, minutes and seconds into total seconds works.
void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
	assert(TimeCode::ComponentsToSeconds(1, 0, 0) == 3600);
	assert(TimeCode::ComponentsToSeconds(1, 20, 0) == 4800);
	assert(TimeCode::ComponentsToSeconds(3, 20, 40) == 12040);
	
	cout << "PASSED!" << endl << endl;
}

//for me: checks whether creating a blank TimeCode defaults to zero time 
void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	//for me: creates an empty time object
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	//for me:checks if the two string function returns the exact string
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	TimeCode tc2 = TimeCode(1, 40, 22);
	assert(tc2.ToString() == "1:40:22");
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	TimeCode tc4 = TimeCode(6, 80, 400);
	assert(tc4.ToString() == "7:26:40");
	
	TimeCode tc5 = TimeCode(14, 289, 7821);
	assert(tc5.ToString() == "20:59:21");
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	TimeCode tc2 = TimeCode(9, 30, 14);
	tc2.GetComponents(h, m, s);
	assert(h == 9 && m == 30 && s == 14);
	
	TimeCode tc3 = TimeCode(0, 0, 0);
	tc3.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);	
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	TimeCode tc6 = TimeCode(2, 2, 0) - TimeCode(1, 0, 0);
	assert(tc6.ToString() == "1:2:0");
	
	TimeCode tc7 = TimeCode(4, 2, 1) - TimeCode(3, 1, 0);
	assert(tc7.ToString() == "1:1:1");
	
	TimeCode tc8 = TimeCode(124, 45, 30) - TimeCode(89, 12, 15);
	assert(tc8.ToString() == "35:33:15");
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}


// Many More Tests...

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	
	TestSubtract();
    TestSetMinutes();
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
