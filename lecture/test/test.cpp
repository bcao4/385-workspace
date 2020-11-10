#include <iostream>
using namespace std;

int main() {
  int arr[14]= {1025, 3, 1234567, 8, 64, 128, 127, 126, 125, 54321, 1, 99, 100};
  int sum = 0;

  for(int i = 0; i<=14; i++){
    sum = sum + arr[i];
  }
  if(sum%2 == 0){
    cout<<"The sum is even";
  } else {
    cout<<"The sum is odd";
  }
  cout<<sum;
}