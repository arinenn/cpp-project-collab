#ifndef EUROPEAN_OPTIONS_H
#define EUROPEAN_OPTIONS_H

#include <stdexcept>

class EuropeanOption {
private:
    bool _is_call;
    double maturity;
    double strike;
public:
    EuropeanOption(bool _is_call, double m, double s);
    bool is_call();
    void set_maturity(double);
    double get_maturity();
    void set_strike(double);
    double get_strike();
};

#endif  // EUROPEAN_OPTIONS_H