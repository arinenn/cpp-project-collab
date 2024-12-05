#ifndef HESTON_MODEL_H
#define HESTON_MODEL_H

#include <complex>
#include <cmath>

struct HestonParams {
    double rho;             // correlation between brownian motions
    double kappa;           // speed of mean-reversion
    double theta;           // long-term mean
    double sigma;           // volatility of volatility
};

std::complex<double>
heston_log_price_cf(std::complex<double> u, double x, double v, double t, double T, HestonParams &params);

std::complex<double>
heston_exp_option_cf(std::complex<double> u, double x, double v, double alpha, double T, HestonParams &params);

#endif  // HESTON_MODEL_H