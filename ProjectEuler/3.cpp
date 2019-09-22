/* Largest prime factor
(https://projecteuler.net/problem=3)

The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143?
*/

#include <iostream>
#include <cmath>

int main(){
    long int n = 600851475143;
    int largest = 0;
    while (n % 2 == 0){
        n = n/2;
        largest = 2;
    }
    std::cout << largest << "\n";

    for (int i = 3; i <= n; i += 2){
        while (n % i == 0){
            n = n/i;
            if (largest < i){
                std::cout << largest << "\n";
            }
            largest = i;
        }
        
    }

    std::cout << largest << std::endl;
}