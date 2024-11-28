#include "heston_model.h"

std::complex<double>
heston_log_price_cf(std::complex<double> u, double x, double v, double t, double T, HestonParams &params)
{
    std::complex<double> i(0.0, 1.0);
    std::complex<double> one(1.0, 0.0);
    std::complex<double> two(2.0, 0.0);
    std::complex<double> d = std::sqrt(
        std::pow(params.rho * params.sigma * i * u - params.kappa, 2) +
        std::pow(params.sigma, 2) * (i * u + std::pow(u, 2))
        );
    std::complex<double> g = 
        (params.rho * params.sigma * i * u - params.kappa + d) / 
        (params.rho * params.sigma * i * u - params.kappa - d);
    double tau = T - t;
    std::complex<double> D = 
        ((params.kappa - params.rho * params.sigma * i * u - d) / std::pow(params.sigma, 2)) *
        ((one - std::exp(-d * tau)) / (one - g * std::exp(-d * tau)));
    std::complex<double> C = 
        ((params.kappa * params.theta) / std::pow(params.sigma, 2)) * 
        ((params.kappa - params.rho * params.sigma * i * u - d) * tau - two * std::log(
            (one - g * std::exp(-d * tau)) / (one - g)
        ));
    return std::exp(C + D * v + i * u * x);
}

std::complex<double>
heston_exp_option_cf(double u, double x, double v, double alpha, double T, HestonParams &params)
{
    std::complex<double> i(0.0, 1.0);
    std::complex<double> one(1.0, 0.0);
    std::complex<double> two(2.0, 0.0);
    return 
        heston_log_price_cf(u - (alpha + one) * i, x, v, 0, T, params) / 
        (std::pow(alpha, 2) + alpha - std::pow(u, 2) + i * (two * alpha + one) * u);
}
