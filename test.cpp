#include <iostream>
#include <complex>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>

// Eigen::RowVectorXcd <- complex dynamic vector

struct MarketParams
{
    double s;               // initial underlying price
    double r;               // risk-free interest rate
    Eigen::RowVectorXcd times;  // arbitrary size double vector
};

struct HestonParams
{
    // double v;               // initial variance
    double rho;             // correlation between brownian motions
    double kappa;           // speed of mean-reversion
    double theta;           // long-term mean
    double sigma;           // volatility of volatility
};

void test_Eigen()
{
    Eigen::MatrixXd m(2,2); // arbitrary size, double matrix
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;
}

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

Eigen::RowVectorXcd
fft(Eigen::RowVectorXcd &vector)
{
    std::cout << vector.cols() << std::endl;
    int vector_size = vector.cols();
    if (vector_size % 2 == 1) {
        throw std::runtime_error("Vector must be of even size.");
    }
    return vector;
}

int main()
{
    // test_Eigen();

    HestonParams params = {0.5, 0.5, 0.5, 0.5};
    std::complex<double> res = heston_log_price_cf(0.5, 0, 0.5, 0.5, 1, params); // (0.96895,-0.0613529) CORRECT
    // std::complex<double> res = heston_log_price_cf(0.5, 1, 0.5, 0.5, 1, params); // (0.879748,0.410697)  CORRECT
    std::cout << res << std::endl;

    std::complex<double> a(1.5, 5.5);
    std::cout << a << std::endl;
    Eigen::RowVectorXcd vector(6);
    vector << std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5);
    std::cout << vector << std::endl;
    try {
        fft(vector);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}