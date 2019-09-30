/* Prime Digit Replacement
(https://projecteuler.net/problem=51)

By replacing the 1st digit of the 2-digit number x3, 
it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56xx3 with the same digit, 
this 5-digit number is the first example having seven primes among the ten generated numbers, 
yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. 
Consequently 56003, being the first member of this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) 
with the same digit, is part of an eight prime value family.
*/

// Will need a list of known primes
// function that checks if a number is prime
// starting at 56003, increments by 2 and checks if the resultant number is prime
// if number is prime, replace part of the number and check if the resultant number is prime
// check the next digit in sequence and increment counter with each prime value.
// if counter == 8 return true, else continue

#include <iostream>
#include <algorithm>


bool is_prime(int n){
    if(n % 2 == 0){
        return false;
    }
    for (int i = 3; i < n; i += 2){
        if (n % i == 0){
            return false;
        }
    }
    return true;
}


bool test_replace(std::string base, std::vector<int> to_replace) {
    int primes = 0;
    for (int x = 0; x <= 9; x++){
        for (auto replace : to_replace){
            base[replace] = x;
        }
        if(is_prime(stoi(base))){
            primes++;
        }
    }
    if (primes >= 8){
        return true;
    }
    return false;
}


int main (){
    int base = 56003;
    bool solved = false;

    while (!solved){
        base += 2;
        std::string strung = std::to_string(base);
        // how to handle an arbitrary number of ptrs into the string?
        // check with 1,2,3,..n-1 replacements
        for (int i = 0; i < strung.length - 1; i++){

            for (int j = i+1; j <= strung.length; j++){

            }
        }
    }
}