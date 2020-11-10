#include <iostream>

using namespace std;

void display_array(int array[], const int length) {
    cout<<"[";
    if (length > 0) {
        cout<<array[0];
    }
    for (int i = 1; i<length; i++) {
        cout<<", "<<array[i];
    }
    cout<<"]"<<endl;
}

void display_array_ptr(int array[], const int length) {
    cout<<"[";
    for(int * ptr = array, *end = array + length; ptr < end; ++ptr) {
        if(ptr != array) {
            cout<<", ";
        }
        cout<< *ptr;
    }
    cout<<"]"<<endl;
}

void pass_by_value(int x) {
    x = 10;
}

void pass_by_pointer(int *x) {
    *x = 10;
}

void pass_by_reference(int &x) {
    x = 10;
}

int main() {
    int x = 5, y = 6, *z = &x;
    // * declares a pointer. Also deferrences a pointer
    // & address of operator

    cout<< "z = " << z << endl;
    cout<< "*z = " << *z << endl;
    cout<< "x = "<< x << endl<< "y = "<< y << endl;

    *z = 7;
    cout << "x = "<< x <<", y = "<< y <<endl;

    z = &y;
    *z = 7;
    cout << "x = "<< x <<", y = "<< y <<endl;

    int *values = new int[y];
    for(int i = 0; i<y; i++) {
        values[i] = i;
    }

    display_array(values, y);
    display_array_ptr(values, y);
    delete [] values;

    x = 5;
    pass_by_value(x);
    cout<<"x = "<<x<<endl;

    x = 5;
    pass_by_pointer(&x);
    cout<<"x = "<<x<<endl;

    x = 5;
    pass_by_reference(x);
    cout<<"x = "<<x<<endl;

    


    //cout<< ++z << endl; //Bad idea. We're not sure what z points to now.
    //cout<< *z << endl;

    //z += 30000;         //Terrible idea: z points outside the address space of this process.
    //*z = 30;            //Assisgning a new value to z will cause a segmentation fault.

    
}