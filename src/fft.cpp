#include "fft.h"

Eigen::RowVectorXcd
fft(Eigen::RowVectorXcd &vector)
{
    // check if length is even
    if (vector.cols() % 2 == 1) {
        throw std::runtime_error("Vector must be of even size.");
    }

    // result vector
    Eigen::RowVectorXcd result(vector.cols());

    // calculate complex exponents
    int vector_size = vector.cols();
    int half_size = vector.cols() >> 1;
    std::complex<double> i(0.0, 1.0);
    Eigen::RowVectorXcd exponents(half_size);
    exponents = (-2 * M_PI * i / (double)half_size) * Eigen::RowVectorXcd::LinSpaced(half_size, 0, half_size - 1);
    exponents = exponents.array().exp();

    // calculate the spectrum
    Eigen::RowVectorXcd even_half = vector(Eigen::seq(0, vector.cols() - 1, 2));
    Eigen::RowVectorXcd odd_half  = vector(Eigen::seq(1, vector.cols() - 1, 2));
    for (int n=0; n<vector_size; n++) {
        Eigen::RowVectorXcd exp_pow = exponents.array().pow(n);
        std::complex<double> dot_exponent = std::exp(-2 * M_PI * n * i / (double)vector_size); // multiplier
        std::complex<double> sum_1 = exp_pow.cwiseProduct(even_half).sum();
        std::complex<double> sum_2 = exp_pow.cwiseProduct(odd_half).sum();
        result(n) = sum_1 + dot_exponent * sum_2;
    }
    return result;
}