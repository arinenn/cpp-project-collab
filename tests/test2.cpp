#include "heston_pricing.h"
#include <iostream>

void test_2()
{
    double r = 0.02;
    double s_0 = 1;
    double v_0 = 0.3;
    // rho, kappa, theta, sigma
    HestonParams params = {-0.2, 2, 0.1, 0.7};
    double alpha = 2.5;
    int N = std::pow(2, 14);     // 2^14 ~16000
    double d_u = 0.1;

    HestonEuropeanOptionCalculator HestonCalculator(r, s_0, v_0, params, alpha, N, d_u);
    EuropeanOption option(true, 0.5, 0.5);  //strike doesn't matter... we get an output on grid of strikes

    // Eigen::RowVectorXd temp = HestonCalculator.calculate(option);
    // std::cout << temp << std::endl;
    HestonCalculator.calc_and_show(option, 0.65, 1.35);
}

int main()
{
    test_2();
    return 0;
}