/**
 * @file
 * @brief Parameteres of Heston model and implementation of characteristic functions.
 */
#ifndef HESTON_MODEL_H
#define HESTON_MODEL_H

#include <complex>
#include <cmath>

/**
 * @brief       A Heston model parameteres struct
 * 
 * @details     This structure is later used for characteristic functions and price calculations.
 */
struct HestonParams
{
    //! Correlation between brownian motions
    double rho;

    //! Speed of mean-reversion
    double kappa;

    //! Long-term mean
    double theta;

    //! Volatility of volatility   
    double sigma;
};

/**
 * @brief       Get char. function of \f$ X_T = \ln F_T \f$
 *
 * @details     Calculates char. function of \f$ X_T = \ln F_T \f$ by given formulae.
 *              For references see Project's overleaf page at Main Page.
 *           
 * @warning     There is no input parameres check. Be cautious to use this function outside of this project.
 *
 * @param   u       Complex argument of char. function
 * @param   x       Log forward value at current time
 * @param   v       Volatility value at current time
 * @param   t       Market current time
 * @param   T       Time to expiration
 * @param   params  Heston model parameters struct
 *
 * @return      Analytical value of characteristic function.
 */
std::complex<double>
heston_log_price_cf(std::complex<double> u, double x, double v, double t, double T, HestonParams &params);

/**
 * @brief       Get char. function of \f$ c_T(k) = e^{\alpha k}\mathbb{E}[(F_T-K)^+] \f$
 *
 * @details     Calculates char. function of \f$ c_T(k) = e^{\alpha k}\mathbb{E}[(F_T-K)^+] \f$ by given formulae.
 *              It calls heston_log_price_cf with current time equal to 0.
 *              For references see Project's overleaf page at Main Page.
 *           
 * @warning     There is no input parameres check. Be cautious to use this function outside of this project.
 *
 * @param   u       Complex argument of char. function
 * @param   x       Log forward value at current time
 * @param   v       Volatility value at current time
 * @param   alpha   Exponent parameter
 * @param   T       Time to expiration
 * @param   params  Heston model parameters struct
 *
 * @return      Analytical value of characteristic function.
 */
std::complex<double>
heston_exp_option_cf(std::complex<double> u, double x, double v, double alpha, double T, HestonParams &params);

#endif  // HESTON_MODEL_H