#include "european_options.h"

EuropeanOption::EuropeanOption(const std::string &type, double maturity, double strike):
        type(type), maturity(maturity), strike(strike) {};

void EuropeanOption::set_maturity(double m) {
    if (m <= 0) {
        throw std::invalid_argument("Time to maturity must be non-negative.");
    }
    maturity = m;
}

double EuropeanOption::get_maturity() {
    return maturity;
}

void EuropeanOption::set_strike(double s) {
    if (s <= 0) {
        throw std::invalid_argument("Strike must be non-negative.");
    }
    strike = s;
}

double EuropeanOption::get_strike() {
    return strike;
}