#include "heston_pricing.h"
#include <iostream>
#include <iomanip>


HestonEuropeanOptionCalculator::HestonEuropeanOptionCalculator(
    double _r,
    double _s_0,
    double _v_0,
    HestonParams &_params,
    double alpha,
    int N,
    double d_u
) {
    if (_r <= 0) {
        throw std::invalid_argument("Risk-free rate must be non-negative.");
    }
    if (_s_0 <= 0) {
        throw std::invalid_argument("Starting spot price must be non-negative.");
    }
    if (_v_0 <= 0) {
        throw std::invalid_argument("Starting volatility must be non-negative.");
    }
    r = _r; s_0 = _s_0; v_0 = _v_0; params = _params;
    set_calculator_params(alpha, N, d_u);
};

double HestonEuropeanOptionCalculator::df(double t, double T) {
    return std::exp(-r * (T-t));
};

void HestonEuropeanOptionCalculator::set_calculator_params(
    double _alpha, 
    int _N, 
    double _d_u
) {
    if (_alpha <= 0) {
        throw std::invalid_argument("Parameter alpha must be non-negative.");
    }
    if (_N <= 0) {
        throw std::invalid_argument("Grid size must be non-negative.");
    }
    if (_d_u <= 0) {
        throw std::invalid_argument("Grid step must be non-negative.");
    }
    d_u = _d_u;
    N = _N;
    alpha = _alpha;
    d_k = 2 * M_PI / (d_u * N);
};

Eigen::RowVectorXd HestonEuropeanOptionCalculator::get_log_strike_grid()
{
    return Eigen::RowVectorXd::LinSpaced(N, -N * d_k / 2, (N / 2 - 1) * d_k);
}

Eigen::RowVectorXd HestonEuropeanOptionCalculator::calculate(EuropeanOption &option)
{
    Eigen::RowVectorXd log_strikes = get_log_strike_grid();
    Eigen::RowVectorXcd u_grid = Eigen::RowVectorXd::LinSpaced(N, 0, (N-1) * d_u);
    Eigen::RowVectorXcd exp_option_cf(N);
    double T = option.get_maturity();
    double x = std::log(s_0 * df(T, 0));
    for (int i=0; i<N; i++) {
        std::complex<double> mult((-1 + 2*((i+1)%2)), 0);
        exp_option_cf[i] = mult * heston_exp_option_cf(u_grid[i], x, v_0, alpha, T, params);
    }
    Eigen::RowVectorXcd integr_appr = fft(exp_option_cf);
    Eigen::RowVectorXd result(N);
    Eigen::RowVectorXd temp;
    temp = (-alpha * log_strikes).array().exp();
    result = integr_appr.real();
    result = result.cwiseProduct(temp);
    result = (df(0, T) * d_u / M_PI) * result;
    if (option.is_call()) {
        return result;
    }
    // if option is of put type
    return result.array() + log_strikes.array().exp() * df(0, T) - s_0;
}

void HestonEuropeanOptionCalculator::calc_and_show(EuropeanOption &option, double K_lower, double K_upper)
{
    Eigen::RowVectorXd strikes = get_log_strike_grid().array().exp();
    Eigen::RowVectorXd prices = calculate(option);
    for (int i=0; i < strikes.cols(); i++) {
        if ((strikes[i] >= K_lower) && (strikes[i] <= K_upper)) {
            std::cout << std::setprecision(7) << "K=" << strikes[i] << "\tC=" << prices[i] << std::endl;
        } else if (strikes[i] > K_upper) {
            break;
        }
    }
    // print_results(strikes, prices);
}

void HestonEuropeanOptionCalculator::print_results(Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices)
{
    std::ofstream fout("plot/output.csv"); 
    fout<<"K,C"<<std::endl;
    for (int i=0; i < strikes.cols(); i++) {
        fout<<strikes[i]<<','<<prices[i]<<std::endl;
    }
    fout.close();
}

