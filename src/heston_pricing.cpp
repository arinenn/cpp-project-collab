/**
 * @file
 * @brief Class of european options Heston model calculator.
 */
#include "heston_pricing.h"

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

double HestonEuropeanOptionCalculator::df(double t, double T)
{
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
    if ((_N <= 0) || (_N % 2 == 1)) {
        throw std::invalid_argument("Grid size must be non-negative and even.");
    }
    if (_d_u <= 0) {
        throw std::invalid_argument("Grid step must be non-negative.");
    }
    d_u = _d_u;
    N = _N;
    alpha = _alpha;

    // Set strikes grid step for FFT usage
    d_k = 2 * M_PI / (d_u * N);
};

double HestonEuropeanOptionCalculator::get_alpha()
{
    return alpha;
}

double HestonEuropeanOptionCalculator::get_N()
{
    return N;
}

double HestonEuropeanOptionCalculator::get_d_u()
{
    return d_u;
}

double HestonEuropeanOptionCalculator::get_d_k()
{
    return d_k;
}

Eigen::RowVectorXd HestonEuropeanOptionCalculator::get_log_strike_grid()
{
    return Eigen::RowVectorXd::LinSpaced(N, -N * d_k / 2, (N / 2 - 1) * d_k);
}


std::pair<bool, double> HestonEuropeanOptionCalculator::integrate_condition(double T)
{
    // Calculate discriminant
    double k = alpha * (alpha + 1) / 2;
    double sigma_2 = params.sigma * params.sigma;
    double b = 2 * k / sigma_2;
    double a = (2 * params.rho * (alpha + 1) - params.kappa) / sigma_2;
    double D = a * a - 4 * b;
    double gamma = std::sqrt(std::abs(D)) / 2;

    // Resulting pair
    std::pair<bool, double> result(true, 0);

    // Calculate T*
    if (D >= 0) {
        if (a < 0) {
            // T* = +infty
            return result;
        } else {
            result.second = sigma_2 * std::log(
                (a/2 + gamma) / (a/2 - gamma)
            ) / gamma;
        }
    } else {
        if (a < 0) {
            result.second = 2 * sigma_2 * (
                M_PI + std::atan(2 * gamma / a)
            ) / gamma;
        } else {
            result.second = 2 * sigma_2 * (
                std::atan(2 * gamma / a)
            ) / gamma;
        }
    }

    // Calculate the flag
    if (T >= result.second) {
        // Moment is infinite
        result.first = false;
    }
    return result;
}

Eigen::RowVectorXd HestonEuropeanOptionCalculator::calculate(EuropeanOption &option)
{
    // Check Andersen-Piterbarg condition
    std::pair<bool, double> flag = integrate_condition(option.get_maturity());
    if (!flag.first) {
        throw std::invalid_argument("Andersen-Piterbarg condition is false.");
    }

    // Get u, log strikes grids
    Eigen::RowVectorXd log_strikes = get_log_strike_grid();
    Eigen::RowVectorXcd u_grid = Eigen::RowVectorXd::LinSpaced(N, 0, (N-1) * d_u);

    // Calculate characteristic function of undistounted call option price, multiplied by exp(-alpha*lnK)
    Eigen::RowVectorXcd exp_option_cf(N);
    double T = option.get_maturity();
    double x = std::log(s_0 * df(T, 0));
    for (int i=0; i<N; i++) {
        std::complex<double> mult((-1 + 2*((i+1)%2)), 0);
        exp_option_cf[i] = mult * heston_exp_option_cf(u_grid[i], x, v_0, alpha, T, params);
    }

    // Approximate continous Fourier transform by discrete using FFT algorithm
    Eigen::RowVectorXcd integr_appr = fft(exp_option_cf);

    // Result call option prices
    Eigen::RowVectorXd result(N);

    // Calculate resulting call option prices
    Eigen::RowVectorXd temp;
    temp = (-alpha * log_strikes).array().exp();
    result = integr_appr.real();
    result = result.cwiseProduct(temp);
    result = (df(0, T) * d_u / M_PI) * result;
    
    if (option.is_call()) {
        return result;
    }

    // If option is of put type, use the Put-Call parity
    return result.array() + log_strikes.array().exp() * df(0, T) - s_0;
}
