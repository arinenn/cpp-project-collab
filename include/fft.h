/**
 * @file
 * @brief FFT algorithm implementation.
 */
#ifndef FFT_H
#define FFT_H

#include <stdexcept>
#include <complex>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Core>

/**
 * @brief           Calculate Discrete Fourier Transform by Fast Fourier Transform method
 *
 * @details         Calculates DFT \f$ F_n = \sum_{k=0}^{N-1}f_k e^{-2\pi ink/N}_{N},~ n=\overline{0,N-1} \f$
 *                  by given vector of complex values with even shape $f_k,k=\overline{0,N-1}$.
 *                  If \f$ N=2k+1 \f$ (is odd), exception std::invalid_argument is thrown.
 *                  Time complexity is \f$\mathcal{O}(Nlog(N)) \f$.
 *                  For references see Project's overleaf page at Main Page.
 *
 * @param   vector  Vector of complex values with even shape.
 *
 * @return          DFT of current data.
 */
Eigen::RowVectorXcd fft(Eigen::RowVectorXcd &vector);

#endif  // FFT_H