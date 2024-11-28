#ifndef EUROPEAN_OPTIONS_H
#define EUROPEAN_OPTIONS_H

#include <stdexcept>
#include <string>

class EuropeanOption {
private:
    std::string type;
    double maturity;
    double strike;
public:
    EuropeanOption(const std::string &, double, double);
    void set_maturity(double);
    double get_maturity();
    void set_strike(double);
    double get_strike();
};

#endif  // EUROPEAN_OPTIONS_H