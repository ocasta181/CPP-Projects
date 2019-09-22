/* Largest Palindrome Product
(https://projecteuler.net/problem=4)

A palindromic number reads the same both ways. 
The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#include <iostream>
#include <vector>

int find_magnitude(int number) {
	int magnitude = 0;

	while (number > 0) {
		number /= 10;
		++magnitude;
	}

	return magnitude;
}

std::vector<int> decompose_int(int number) {
	std::vector<int> digits;

	while (number > 0) {
		digits.push_back(number % 10);
		number /= 10;
	}

	return digits;
}

bool is_palindrome(std::vector<int> digits){
	int length = digits.size();
	for (int i = 0; i < length/2; i++){
		if (digits[i] != digits[length-(i+1)]){
			return false;
		}
	}
	return true;
}


int main() {

	std::vector<int> digits;
	int largest;

	for(int x = 100; x < 1000; ++x){
		for(int y = 100; y < 1000; ++y){
			int product = x*y;
			digits = decompose_int(product);

			if (is_palindrome(digits)) {
				std::cout << product << " is the product of " << x << " and " << y << "\n";
				if (product > largest) {
					largest = product;
				}
			}
		}
	}
	std::cout << "largest: " << largest << std::endl;

}