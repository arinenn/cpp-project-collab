#include "european_options.h"

EuropeanOption::EuropeanOption(bool is_call, double m, double s): _is_call(is_call)
{
    set_maturity(m);
    set_strike(s);
};

bool EuropeanOption::is_call() {
    return _is_call;
}

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