/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Brandon Cao
 * Date        : September 28th, 2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<int> num_steps {1,2,3};
    vector<vector<int>> ways;
    vector<vector<int>> result;
    vector<int> steps;
    
    if(num_stairs <= 0) {
        ways.push_back(steps);
    }
    for(auto i : num_steps) {
        if (num_stairs >= i) {
            result = get_ways(num_stairs - i);
            for(unsigned int j = 0; j < result.size(); j++) {
                //result[j].push_back(i);
                result[j].insert(result[j].begin(), i);
                ways.push_back(result[j]);
            }
        }
    }
    return ways;
}

int num_digits(int num) {
    int count = 1;
    while(num/10 >= 1) {
        count++;
        num = num/10;
    }
    return count;
}

bool isNum(string steps ) {
    for(unsigned int i = 0; i < steps.size(); i++) {
        if (isdigit(steps[i]) == false) {
            return false;
        }
    }
    return true;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int count = 0;
    int spacing = num_digits(ways.size());

    for(unsigned int i = 0; i<ways.size(); i++) {
        count++;
        cout<<setw(spacing)<<count<<". [";
        for(unsigned int j = 0; j<ways[i].size(); j++) {
            if(j+1 < ways[i].size()) {
                cout<<ways[i][j]<<", ";
            } else {
                cout<<ways[i][j]<<"]"<<endl;
            } 
        }
    }
}

int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cout<<"Usage: ./stairclimber <number of stairs>";
        return 1;
    }
   
    string steps = argv[1];
    if(isNum(steps) == false ) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    if(atoi(argv[1]) <= 0) {
        cout<<"Error: Number of stairs must be a positive integer.";
        return 1;
    }

    else {
        int num_stairs = atoi(argv[1]);
        vector<vector<int> > ways;
        ways = get_ways(num_stairs);

        if(num_stairs == 1) {
            cout<<"1 way to climb 1 stair."<<endl;
        } else {
            cout<<ways.size()<<" ways to climb "<<argv[1]<<" stairs."<<endl;
        }
        display_ways(ways);
    }
}
