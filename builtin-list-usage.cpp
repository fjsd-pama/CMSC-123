#include <list>
#include <iostream>
#include <cstdlib>

using namespace std;

//Check if a given number is prime
bool prime( int num ){
    for (int i = 2; i < num; i++ ){
        if ( num % i == 0 ){
            return false;
        }
    }

    return true;
}

//Reverses a given integer num
int reverseNum( int num ){
    int numCopy = num;
    int result = 0;
    while ( numCopy > 0 ){
        result = (result * 10) + (numCopy % 10);
        numCopy /= 10;
    }

    return result;
}

//Traverses a given list and prints "YES" if a given element in the list and
//its reversed are both primes otherwise prints "NO"
void checkEmirp( list<int> given ){
    list<int>:: iterator it;
    for ( it = given.begin(); it != given.end(); it++ ){
        if ( prime(*it) && prime(reverseNum(*it)) ){
            cout<<"YES"<<endl;
        } else{
            cout<<"NO"<<endl;
        }
    }
}

int main(){
    list<int> list1; //declare list

    int x; //var to represent numbers of elements in the list
    cin >> x;
    int y; //var to hold number being scanned

    for (int i = 0; i < x; i++){
        cin >> y; //scan number
        list1.push_back(y);
    }

    checkEmirp( list1 );

    return 0;

}

