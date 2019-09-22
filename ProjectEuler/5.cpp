/* Smallest Multiple
(https://projecteuler.net/problem=5)

2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include <iostream>
#include <set>

int bruteForce(){
    for (int i = 1; i < 1000000000; i++) {
        for (int j = 1; j <= 20; j++) {
            // std::cout << i << '%' << j << " : " << (i % j != 0) << "\n";
            if (i % j != 0) {
                break;
            } else if (j == 20) {
                // std::cout << "returning: " << i << "\n";
                return i;
            }
        }
    }
}

std::set<int> findPrimes(int n){
    int current = 0;
    std::set<int> primes;
    while (n % 2 == 0){
        n = n/2;
        if (current < 2) {
            current = 2;
            primes.insert(2);
        }
    }
    for (int j = 3; j <= n; j++){
        for (int i = 3; i <= n; i += 2){
            while (j % i == 0){
                j = j/i;
                if (current < i) {
                    current = i;
                    primes.insert(i);
                }
            }
        }
    }
    
    return primes;
}


int betterApproach(int n){
    std::set<int> primes = findPrimes(n);
    int answer = 1;
    for (int n : primes) {
        std::cout << n << "\n";
        answer *= n;
    }
    return answer;
}

int main(){
    // std::cout << bruteForce() << std::endl;
    std::cout << betterApproach(20) << std::endl;
}