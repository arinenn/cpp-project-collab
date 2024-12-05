#ifndef HESTON_PRICING_H
#define HESTON_PRICING_H

#include "fft.h"
#include "heston_model.h"
#include "european_options.h"

class HestonEuropeanOptionCalculator {
private:
    double r;               // market parameteres
    double s_0;
    double v_0;
    HestonParams params;    // model parameteres
    double alpha;           // calculator parameteres
    int N;      // count of exponents in integral approximation
    double d_u; // u grid step
    double d_k; // log strike grid step
public:
    HestonEuropeanOptionCalculator(double r, double s_0, double v_0, HestonParams &params);
    double df(double T);
    double calculate(EuropeanOption &option);
    void set_calculator_params(double alpha, int N, double d_u);
};

#endif  // HESTON_PRICING_H