#include "encryption.hpp"


unsigned long get_random_prime() {
	return 17;
}


unsigned long lcm(unsigned long a, unsigned long b) {
    return a * b / gcd(a, b);
}


unsigned long gcd(unsigned long a, unsigned long b) {
    unsigned long temp;
    while (1) {
    	temp = a%b;
        if (temp == 0) return b;
        a = b;
        b = temp;
    }
}
