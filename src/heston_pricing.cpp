#include "heston_pricing.h"
#include <iostream>

HestonEuropeanOptionCalculator::HestonEuropeanOptionCalculator(
    double r,
    double s_0,
    double v_0,
    HestonParams &params
): r(r), s_0(s_0), v_0(v_0), params(params) {};

double HestonEuropeanOptionCalculator::df(double T) {
    return std::exp(-r * T);
};

void HestonEuropeanOptionCalculator::set_calculator_params(
    double alph, 
    int n, 
    double delta
) {
    // assume that d_u > 0, alpha > 0, N > 0
    d_u = delta;
    N = n;
    alpha = alph;
    d_k = 2 * M_PI / (d_u * N);
};

double HestonEuropeanOptionCalculator::calculate(EuropeanOption &option)
{
    // for loop by log strike grid
    Eigen::RowVectorXd log_strikes = Eigen::RowVectorXd::LinSpaced(N, -N * d_k / 2, (N / 2 - 1) * d_k);
    std::cout << (N / 2 - 1) * d_k << std::endl;
    std::cout << log_strikes << std::endl;
    return 0;
}