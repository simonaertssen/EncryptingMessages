#include "encryption.hpp"


double gcd(double a, double h) {
    double temp;
    while (1) {
    	temp = a%h;
        if (temp == 0) return h;
        a = h;
        h = temp;
    }
}

double get_random_prime() {
	return 17;
}
