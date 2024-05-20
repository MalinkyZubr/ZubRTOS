#include <utils.h>


float modular_exponent(float base, int exponent) {
    if(exponent < 0) {
        return 1 / exp_by_square(base, -exponent);
    }
    else if(exponent == 0) {
        return 1;
    }
    else if(exponent % 2 == 0) {
        return exp_by_square(base * base, (exponent - 1) / 2);
    }
    else if(exponent % 2 == 1) {
        return base * exp_by_square(base * base, (exponent - 1) / 2);
    }
}