#include <iostream>
#include "heston_pricing.h"

int main()
{
    // Set market state
    double r = 0.02;
    double s_0 = 1;
    double v_0 = 0.3;

    // Set rho, kappa, theta, sigma
    HestonParams params = {-0.2, 2, 0.1, 0.7};
    
    // Set calculator parameteres
    double alpha = 2.5;
    int N = std::pow(2, 14);     // 2^14 ~16000
    double d_u = 0.1;

    // Initiate calculator for given market of Heston model
    HestonEuropeanOptionCalculator HestonCalculator(r, s_0, v_0, params, alpha, N, d_u);

    // Set option by is_call, maturity, strike
    EuropeanOption option(true, 0.5, 1);  // strike doesn't matter... we get an output on grid of strikes

    // Print option prices to stdout for K from [K_lower, K_upper]
    HestonCalculator.calc_and_show(option, 0.65, 1.35);

    return 0;
}