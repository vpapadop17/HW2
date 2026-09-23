#include <fstream> 
#include <iostream>
#include <string>
//for fstream used this to figure out how to properly read a csv file: https://medium.com/@ryan_forrester_/reading-csv-files-in-c-how-to-guide-35030eb378ad 

//Did not know where to put this comment but i did read the comments/notes in the assignment file 

using namespace std; 

int main() {
    ifstream file("Space_Corrected.csv");

    if (!file.is_open()) {
        cout << "Could not open file!" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
    return 0;
}
	


