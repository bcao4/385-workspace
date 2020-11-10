/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Brandon Cao
 * Date        : September 6th, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // Displays the primes in the format specified in the requirements document.
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);

    cout<<endl<<"Number of primes found: "<<num_primes_<<endl;
    cout<<"Primes up to " <<limit_<<":"<<endl;

    if(num_primes_ <= primes_per_row) { //fits in one line
        for(int i = 2; i < limit_ + 1; i++) {
            if(is_prime_[i] == true) {
                if(i != max_prime_) {
                    cout<<i<<" ";
                } else {
                    cout<<i<<endl;
                }
            }
        }
    }
    else if(num_primes_ > primes_per_row) { //for multiple lines
        int count = 0;

        for(int i = 2; i < limit_ + 1; i++) {
            cout<<setw(max_prime_width);
            if(is_prime_[i] == true) {
                if(count < primes_per_row - 1) {
                    if( i != max_prime_) {
                        cout<<i<<" ";
                        count++;
                    } else {
                        cout<<i<<endl;
                    }
                } else {
                    cout<<i<<endl;
                    count = 0;
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // Counts the number of primes found
    int count = 0;

    for(int i = 2; i < limit_ + 1; i++) {
        if(is_prime_[i] == true) {
            count++;
        }
    }
        return count;
}

void PrimesSieve::sieve() {

    // Sets all values of the array up to limit to true
    for(int i = 2; i < limit_+1; i++) {
        is_prime_[i] = true;
    }

    // Sets all values that are not prime to false
    for(int i = 2; i <= sqrt(limit_); i++) {
        if(is_prime_[i] == true) {
            for(int j = (i*i); j<=limit_; j = j+i) {
                is_prime_[j] = false;
            }
        }
    }

    num_primes_ = count_num_primes();

    // Finds the max prime value
    for(int i = limit_; i >= 2; i--) {
        if(is_prime_[i] == true) {
            max_prime_ = i;
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // Determines how many digits are in an integer
    int digits = 0;
    while(num >= 1){
        num = num/10;
        digits++;
    }
    return digits;
}


int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Produces the desired output.

    PrimesSieve n(limit);
    n.display_primes();

    return 0;
}
