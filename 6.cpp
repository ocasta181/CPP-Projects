/* Sum Square Difference
(https://projecteuler.net/problem=6)

The sum of the squares of the first ten natural numbers is,

	1^2 + 2^2 + ... + 10^2 = 385

The square of the sum of the first ten natural numbers is,

	(1 + 2 + ... + 10)^2 = 55^2 = 3025

Hence the difference between the sum of the squares of the first ten natural numbers 
and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
*/

#include <iostream>

int main(){
	int sum_of_squares = 0;
	int square_of_sums = 0;

	for (int x = 0; x <= 100; x++) {
		std::cout << "adding x : " << x << "\n";
		sum_of_squares = sum_of_squares + x*x;
		std::cout << "sum_of_squares: " << sum_of_squares << "\n";
		square_of_sums = square_of_sums + x;
		std::cout << "square_of_sums: " << square_of_sums << "\n";
	}

	square_of_sums *= square_of_sums;
	std::cout << "square_of_sums: " << square_of_sums << "\n";

	int answer = square_of_sums - sum_of_squares;

	std::cout << "answer is: " << answer << std::endl;
}