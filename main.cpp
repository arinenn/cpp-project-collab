#include "heston_pricing.h"

int main()
{
    double r = 1;
    double s_0 = 1;
    double v_0 = 1;
    HestonParams params = {0.5, 0.5, 0.5, 0.5};
    HestonEuropeanOptionCalculator HestonCalculator(r, s_0, v_0, params);
    EuropeanOption option(true, 1.25, 0.9);
    HestonCalculator.set_calculator_params(1, 10, 0.1);
    HestonCalculator.calculate(option);
    return 0;
}