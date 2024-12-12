#include "heston_pricing.h"
#include "print.h"

int main()
{
    // Set market state
    double r = 0.05;
    double s_0 = 100;
    double v_0 = 0.2;

    // Set rho, kappa, theta, sigma
    HestonParams params = {-0.5, 10, 0.2, 0.7};

    // Set calculator parameteres
    double alpha = 2.5;
    int N = 8192;               // 2^13
    double d_u = 0.1;

    // Initiate calculator for given market of Heston model
    HestonEuropeanOptionCalculator HestonCalculator(r, s_0, v_0, params, alpha, N, d_u);

    // Set option by is_call, maturity, strike
    double T = 1; double K = 80;
    EuropeanOption option(false, T, K);

    // Calculate option prices for grid of strikes
    Eigen::RowVectorXd prices = HestonCalculator.calculate(option);
    Eigen::RowVectorXd strikes = HestonCalculator.get_log_strike_grid().array().exp();

    // Initiate printer for strikes K from [K_lower, K_upper]
    double K_lower = 65; double K_upper = 135;
    PricesPrinter printer(65, 135);

    // Show desired put option price K=80
    double d_K = std::exp(HestonCalculator.get_d_k());
    printer.set_bounds(K - d_K, K + d_K);
    printer.to_out(strikes, prices);

    // Print option prices to .csv file for K from [K_lower, K_upper]
    printer.set_bounds(K_lower, K_upper);
    printer.to_csv("plot/example-2", strikes, prices);

    return 0;
}