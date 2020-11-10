/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Brandon Cao
 * Date        : October 10th, 2019
 * Description : Water jug problem with three jugs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue> 

using namespace std;

static int capA = 0, capB = 0, capC = 0;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

static bool repeat(State cap, vector<State> jug_values) {
    for(auto i = jug_values.begin(); i != jug_values.end(); i++) {
        State val = *i;
        if(val.a == cap.a && val.b == cap.b && val.c == cap.c) {
            return true;
        } 
    }
    return false;
}

static vector<State> pour(State jug, vector<State> jug_values) {
    State new_amts = jug;
    vector <State> vec;

    if(jug.a != capA && jug.c != 0) { //Can pour from C to A
        int to_pour1 = min(jug.c, capA - jug.a); //C to A
        new_amts.c = new_amts.c - to_pour1;
        new_amts.a = new_amts.a + to_pour1;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }

    if(jug.a != capA && jug.b != 0) { //Can pour from B to A
        int to_pour2 = min(jug.b, capA - jug.a); //B to A
        new_amts.b = new_amts.b - to_pour2;
        new_amts.a = new_amts.a + to_pour2;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }

    if(jug.b != capB && jug.c != 0) { //Can pour from C to B
        int to_pour3 = min(jug.c, capB - jug.b);; //C to B
        new_amts.c = new_amts.c - to_pour3;
        new_amts.b = new_amts.b + to_pour3;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }

    if(jug.b != capB && jug.a != 0) { //Can pour from A to B
        int to_pour4 = min(jug.a, capB - jug.b);; //A to B
        new_amts.a = new_amts.a - to_pour4;
        new_amts.b = new_amts.b + to_pour4;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }

    if(jug.c != capC && jug.b != 0) { //Can pour from B to C
        int to_pour5 = min(jug.b, capC - jug.c); //B to C
        new_amts.b = new_amts.b - to_pour5;
        new_amts.c = new_amts.c + to_pour5;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }

    if(jug.c != capC && jug.a != 0) { //Can pour from A to C
        int to_pour6 = min(jug.a, capC - jug.c); //A to C
        new_amts.a = new_amts.a - to_pour6;
        new_amts.c = new_amts.c + to_pour6;
        if(repeat(new_amts, jug_values) == false) {
            vec.push_back(new_amts);
        }
        new_amts = jug;
    }
    return vec;
}

static vector<State> get_direction(vector<State> jug_values) { //Removes pours that do not lead to the goal
    vector<State> direction;
    int diffA = 0, diffB = 0, diffC = 0; 
    State all_last(0,0,0), direction_last(0,0,0);

    while(!jug_values.empty()) {
        all_last = jug_values.back();
        if(!direction.empty()) {
            direction_last = direction.back(); 
            diffA = all_last.a - direction_last.a;
            diffB = all_last.b - direction_last.b;
            diffC = all_last.c - direction_last.c;
            if(diffA != 0 && diffB != 0 && diffC !=0) { //Checks if one jug remains the same each pour
                jug_values.pop_back();
                continue;
            }
            else if(diffA + diffB + diffC != 0) { //One jug gains what other pours. Other is zero.
                jug_values.pop_back();
                continue;
            }
            else if(diffA > 0 && diffA != all_last.a && diffA != capA ) {
                if( (diffB < 0 && abs(diffB) + all_last.b != capB) || (diffC < 0 && abs(diffC) + all_last.c != capC) ) {
                    jug_values.pop_back();
                    continue;
                }
            }
            else if(diffB > 0 && diffB != all_last.b && diffB != capB ) {
                if( (diffA < 0 && abs(diffA) + all_last.a != capA) || (diffC < 0 && abs(diffC) + all_last.c != capC) ) {
                    jug_values.pop_back();
                    continue;
                }
            }
            else if(diffC > 0 && diffC != all_last.c && diffC != capC ) {
                if( (diffA < 0 && abs(diffA) + all_last.a != capA) || (diffB < 0 && abs(diffB) + all_last.b != capB) ) {
                    jug_values.pop_back();
                    continue;
                }
            }
            
            direction.push_back(all_last);
        } else {
            direction.push_back(all_last);
        }
        jug_values.pop_back();
    }
    return direction;
}

void print_direction(vector<State> result, State s) {
    State prev (0,0,0);
    
    if(!result.empty()) {
        cout << "Initial state. " << s.to_string() << endl;

        while(!result.empty()) {
            State current = result.back();

            if(prev.a == 0 && prev.b == 0 && prev.c == 0) {
                prev = current;
                result.pop_back();
                continue;
            }
            
            int diffA = prev.a - current.a;
            int diffB = prev.b - current.b;
            int diffC = prev.c - current.c;
            
            if(diffA > 0) {
                if( diffA == 1 )
                    cout << "Pour " << diffA << " gallon from A to ";
                else
                    cout << "Pour " << diffA << " gallons from A to ";
            }
            else if(diffB > 0) {
                if( diffB == 1 )
                   cout << "Pour " << diffB << " gallon from B to ";
                else
                   cout << "Pour " << diffB << " gallons from B to ";
            }
            else if(diffC > 0) {
                if( diffC == 1 )
                    cout << "Pour " << diffC << " gallon from C to ";
                else
                    cout << "Pour " << diffC << " gallons from C to ";
            }
            
            if(diffA < 0) {
               cout << "A. " << current.to_string(); 
            }
            else if(diffB < 0) {
                cout << "B. " << current.to_string();
            }
            else if(diffC < 0) {
                cout << "C. " << current.to_string();
            }
            cout << endl; 
            
            prev = current;    
            result.pop_back();
        }
    }
    else {
        cout << "No solution." << endl;
    }
}

vector <State> BFS(State s, State t) {
    queue<State> bfsQ;
    vector<State> bfsVisited;
    bool bFound = false;
    vector <State> printList;

    if(t.c == s.c) {
        printList.push_back(t);
        return printList;
    }
    // push inital state (0, 0, 8) into queue
    bfsQ.push(s);
    
    while (!bfsQ.empty()) {
        State bfsCurrent = bfsQ.front();
        bfsQ.pop();
        
        if(repeat(bfsCurrent, bfsVisited) == false) {    
            bfsVisited.push_back(bfsCurrent);
        } 
        
        vector<State> getNextJugs = pour(bfsCurrent, bfsVisited);
        for(auto i = getNextJugs.begin(); i != getNextJugs.end(); ++i) {
            if((*i).a == t.a && (*i).b == t.b && (*i).c == t.c) {
                bfsVisited.push_back((*i));
                bFound = true;
                if(bFound) {
                    printList = get_direction(bfsVisited);
                }
            }
            bfsQ.push(*i);
        }
    }
    return printList;
}

int main(int argc, char * const argv[]) {
    if(argc != 7) {
        cout<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>";
        return 1;
    }
    int cap_a = atoi(argv[1]), cap_b = atoi(argv[2]), cap_c = atoi(argv[3]);
    int goal_a = atoi(argv[4]), goal_b = atoi(argv[5]), goal_c = atoi(argv[6]);
    istringstream str1(argv[1]), str2(argv[2]), str3(argv[3]), str4(argv[4]), str5(argv[5]), str6(argv[6]);
    int jug1, jug2, jug3, jug4, jug5, jug6;

    if(cap_a < 0) {
        cout<<"Error: Invalid capacity '"<<cap_a<<"' for jug A.";
        return 1;
    }

    else if(cap_b < 0) {
        cout<<"Error: Invalid capacity '"<<cap_b<<"' for jug B.";
        return 1;
    }

    else if(cap_c < 0) {
        cout<<"Error: Invalid capacity '"<<cap_c<<"' for jug C.";
        return 1;
    }

    else if(!(str1>>jug1)) {
        cout<<"Error: Invalid capacity '"<<str1.str()<<"' for jug A.";
        return 1;
    }

    else if(!(str2>>jug2)) {
        cout<<"Error: Invalid capacity '"<<str2.str()<<"' for jug B.";
        return 1;
    }

    else if(!(str3>>jug3)) {
        cout<<"Error: Invalid capacity '"<<str3.str()<<"' for jug C.";
        return 1;
    }

    else if(!(str4>>jug4)) {
        cout<<"Error: Invalid goal '"<<str4.str()<<"' for jug A.";
        return 1;
    }

    else if(!(str5>>jug5)) {
        cout<<"Error: Invalid goal '"<<str5.str()<<"' for jug B.";
        return 1;
    }

    else if(!(str6>>jug6)) {
        cout<<"Error: Invalid goal '"<<str6.str()<<"' for jug C.";
        return 1;
    }

    else if(cap_a == 0) {
        cout<<"Error: Invalid capacity '0' for jug A.";
        return 1;
    }

    else if(cap_b == 0) {
        cout<<"Error: Invalid capacity '0' for jug B.";
        return 1;
    }

    else if(cap_c == 0) {
        cout<<"Error: Invalid capacity '0' for jug C.";
        return 1;
    }

    else if(goal_a < 0) {
        cout<<"Error: Invalid goal '"<<goal_a<<"' for jug A.";
        return 1;
    }

    else if(goal_b < 0) {
        cout<<"Error: Invalid goal '"<<goal_b<<"' for jug B.";
        return 1;
    }

    else if(goal_c < 0) {
        cout<<"Error: Invalid goal '"<<goal_c<<"' for jug C.";
        return 1;
    }
    
    else if(goal_a > cap_a) {
        cout<<"Error: Goal cannot exceed capacity of jug A.";
        return 1;
    }

    else if(goal_b > cap_b) {
        cout<<"Error: Goal cannot exceed capacity of jug B.";
        return 1;
    }

    else if(goal_c > cap_c) {
        cout<<"Error: Goal cannot exceed capacity of jug C.";
        return 1;
    }

    else if((goal_a + goal_b + goal_c) != cap_c) {
        cout<<"Error: Total gallons in goal state must be equal to the capacity of jug C.";
        return 1;
    }

    vector <State> result; 
    capA = atoi(argv[1]);
    capB = atoi(argv[2]);
    capC = atoi(argv[3]);
    
    State intial(0, 0, cap_c);
    State goal(goal_a, goal_b, goal_c);
    result = BFS(intial, goal);
    print_direction(result, intial);
    
}
