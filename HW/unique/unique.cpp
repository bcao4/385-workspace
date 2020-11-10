/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Brandon Cao
 * Date        : September 18th, 2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // Returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.size(); i++) {
        if(isupper(s[i])) { 
            return false;
        }
        if(s[i]>122 || s[i]<97) { 
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // Returns true if all letters in string are unique (no duplicates are found), 
    // using only a single int for storage and working with bitwise
    // and bitshifting operators. Returns false otherwise.

    if(s.size() > 26) { 
        return false;
    }

    int checker = 0;
    for(unsigned int i = 0; i < s.size(); i++) {
        int index = s[i] - 97;

        if((checker & (1<<index))  > 0) {
            return false;
        } 
        checker = (checker ^ (1<<index));
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // Reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc == 1) {
        cout<<"Usage: ./unique <string>"<<endl;
    }

    else if(argc > 2) {
        cout<<"Usage: ./unique <string>"<<endl;
    }

    else if(is_all_lowercase(argv[1]) == true) {
        if(all_unique_letters(argv[1]) == true) {
            cout<<"All letters are unique."<<endl;
        } else {
            cout<<"Duplicate letters found."<<endl;
        }
    } else {
        cout<<"Error: String must contain only lowercase letters."<<endl;
    }
}
