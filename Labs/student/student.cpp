/*******************************************************************************
 * Name    : student.cpp
 * Author  : Brandon Cao
 * Version : 1.0
 * Date    : September 4th, 2019
 * Description : Student class with names, gpa, and id. Lists all students and finds students with a GPA lower than 1.0.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
public:
    Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {};

    //Methods
    string full_name() const {
        return first_ + " " + last_;
    }

    int id() const {
        return id_;
    }

    float gpa() const {
        return gpa_;
    }

    void set_gpa(float gpa) {
        gpa_ = gpa;
    }

    void set_id(int id) {
        id_ = id;
    }

    void print_info() const {
        cout<<full_name()<<", GPA: "<<fixed<<setprecision(2)<<gpa_<<", ID: "<<id_<<endl;
    }


private:
    string first_;
    string last_;
    float gpa_;
    int id_;

};

/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
vector<Student> failing_students;

vector<Student> find_failing_students(const vector<Student> &students) {

    // Iterates through the students vector, appending each student whose gpa is
    // less than 1.0 to the failing_students vector.
     for(size_t i = 0; i < students.size(); i++) {
        if(students[i].gpa() < 1.0) {
            failing_students.push_back(students[i]);
        }
        
       }
        return failing_students;

}


/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    // Iterates through the students vector, calling print_info() for each student.
    for(size_t i = 0; i < students.size(); i++) {
        students[i].print_info();
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen.
*/
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;
    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    if(find_failing_students(students).size() == 0) {
        cout<<" None"<<endl;
    } else {
        cout<<endl;
        print_students(failing_students);
    }
    return 0;
}