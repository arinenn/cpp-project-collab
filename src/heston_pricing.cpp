#include "heston_pricing.h"
#include <iostream>

HestonEuropeanOptionCalculator::HestonEuropeanOptionCalculator(
    double r,
    double s_0,
    double v_0,
    HestonParams &pars,
    double alph,
    int N,
    double delta_u
) {
    if (r <= 0) {
        throw std::invalid_argument("Risk-free rate must be non-negative.");
    }
    if (s_0 <= 0) {
        throw std::invalid_argument("Starting spot price must be non-negative.");
    }
    if (v_0 <= 0) {
        throw std::invalid_argument("Starting volatility must be non-negative.");
    }
    r = r; s_0 = s_0; v_0 = v_0; params = pars;
    set_calculator_params(alph, N, delta_u);
};

double HestonEuropeanOptionCalculator::df(double t, double T) {
    return std::exp(-r * (T-t));
};

void HestonEuropeanOptionCalculator::set_calculator_params(
    double alph, 
    int n, 
    double delta_u
) {
    if (alph <= 0) {
        throw std::invalid_argument("Parameter alpha must be non-negative.");
    }
    if (n <= 0) {
        throw std::invalid_argument("Grid size must be non-negative.");
    }
    if (delta_u <= 0) {
        throw std::invalid_argument("Grid step must be non-negative.");
    }
    d_u = delta_u;
    N = n;
    alpha = alph;
    d_k = 2 * M_PI / (d_u * N);
};

Eigen::RowVectorXd HestonEuropeanOptionCalculator::get_log_strike_grid()
{
    return Eigen::RowVectorXd::LinSpaced(N, -N * d_k / 2, (N / 2 - 1) * d_k);
}

Eigen::RowVectorXd HestonEuropeanOptionCalculator::calculate(EuropeanOption &option)
{
    // for loop by log strike grid
    Eigen::RowVectorXd log_strikes = get_log_strike_grid();
    Eigen::RowVectorXcd u_grid = Eigen::RowVectorXd::LinSpaced(N, 0, (N-1) * d_u);
    Eigen::RowVectorXcd exp_option_cf(N);
    double T = option.get_maturity();
    double factor = df(T, 0);
    // double x = std::log(s_0 * factor);
    double x = std::log(s_0);
    for (int i=0; i<N; i++) {
        std::complex<double> mult((-1 + 2*((i+1)%2)), 1);
        exp_option_cf[i] = mult * heston_exp_option_cf(u_grid[i], x, v_0, alpha, T, params);
    }
    // std::cout <<"u_grid:   " << u_grid << std::endl;
    // std::cout <<"k_grid:   " << log_strikes << std::endl;
    std::cout << "(-1)^npsi_n:  " << exp_option_cf << std::endl;
    Eigen::RowVectorXcd integr_appr = fft(exp_option_cf);
    std::cout << "int_appr:   " << integr_appr << std::endl;
    Eigen::RowVectorXd result(N);
    Eigen::RowVectorXd temp;
    temp = (-alpha * log_strikes).array().exp();
    result = integr_appr.real();
    result = result.cwiseProduct(temp);
    result = (df(0, T) * d_u / M_PI) * result;
    return result;
}