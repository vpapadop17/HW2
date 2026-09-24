#include <fstream> 
//for fstream used this to figure out how to properly read a csv file: https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad 
#include <iostream>
#include <vector>
#include <string>
#include "TimeCode.h"
#include <stdexcept> //use this for invalid argument

//Did not know where to put this comment but i did read the comment 3/note 3 in the assignment file 

using namespace std; 

TimeCode parse_line(string line) {
    size_t colonPos = line.find(':');

    if (colonPos == string::npos) {
        throw invalid_argument("No time found in line");
    }//this is for when there is no time npos allows me to see if the parameter I am searchign for doesn't exist

    unsigned int hr = stoi(line.substr(colonPos - 2, 2));
    unsigned int min = stoi(line.substr(colonPos + 1, 2));

    return TimeCode(hr, min, 0); // seconds not given in the file, use 0
}


vector<string> split(string s, char delimeter) {
    vector<string> pieces;
    string current;

    for (char c : s) {
        if (c == delimeter) {
            pieces.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    pieces.push_back(current); // push the last piece (no delimiter after it)

    return pieces;
}

int main() {
    ifstream file("Space_Corrected.csv");

    if (!file.is_open()) {
        cout << "Could not open file!" << endl;
        return 1;
    }
	
	vector<TimeCode> times;
    string line;
    getline(file, line);
    
	while (getline(file, line)) {
		try {
			TimeCode tc = parse_line(line);
			cout << tc.ToString() << endl;
			times.push_back(tc);
		} catch (const invalid_argument& e) {
			// no time in this row, skip it and move to the next line
		}
	}
	
	file.close();

    return 0;
}
	


