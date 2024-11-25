#include "fft.h"
#include <iostream>

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
    double vector_size = vector.cols();
    double half_size = vector.cols() >> 1;
    std::complex<double> i(0.0, 1.0);
    Eigen::RowVectorXcd exponents((int) half_size);
    exponents = Eigen::RowVectorXcd::LinSpaced((int) half_size, 0, (int) half_size - 1);
    exponents = (-2 * M_PI * i / half_size) * exponents;
    exponents = exponents.array().exp();

    // calculate the spectrum
    Eigen::RowVectorXcd even_half = vector(Eigen::seq(0, vector.cols() - 1, 2));
    Eigen::RowVectorXcd odd_half  = vector(Eigen::seq(1, vector.cols() - 1, 2));
    int n = 0;  // degree counter
    for (auto x: result) {
        std::complex<double> dot_exponent = std::exp(- 2 * M_PI * n * i / vector_size); // multiplier
        Eigen::RowVectorXcd exp_pow = exponents.array().pow(n);
        x = exp_pow.dot(even_half) + dot_exponent * exp_pow.dot(odd_half);
        n += 1;
    }

    return result;
}