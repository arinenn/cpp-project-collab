#ifndef FFT_H
#define FFT_H

#include <stdexcept>
#include <complex>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Core>

Eigen::RowVectorXcd fft(Eigen::RowVectorXcd &);

#endif  // FFT_H