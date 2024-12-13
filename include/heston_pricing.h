/**
 * @file
 * @brief Class of european options Heston model calculator.
 */
#ifndef HESTON_PRICING_H
#define HESTON_PRICING_H

#include "fft.h"
#include "heston_model.h"
#include "european_options.h"

/**
 * @brief               A class of Heston model european options calculator
 * 
 * @details             It encapsulates model and market parameteres, aswell as it's own.
 *                      Integral discretization elements count must be even.
 *                      Other parameteres must be positive.
 */
class HestonEuropeanOptionCalculator {
private:
    //! Risk-free interest rate.
    double r;

    //! Initial stock price.
    double s_0;

    //! Initial volatility value.
    double v_0;

    //! Heston model parameteres struct.
    HestonParams params;

    //! Exponent Carr-Madan parameter.
    double alpha;

    //! Integral discretization elements count.
    int N;

    //! Log forward char. function argument grid step \f$\Delta u>0\f$.
    double d_u;

    //! Log strike grid step \f$\Delta k>0\f$.
    double d_k;

    /**
     * @brief           Calculate discount factor \f$ B(t,T)e^{-r(T-t)} \f$.
     * 
     * @param   t       Current time value
     * @param   T       Terminal time value
     */
    double df(double t, double T);  // get discount factor
public:
    /**
     * @brief           A calculator constructor
     * 
     * @details         If r or s_0 or v_0 are non-positive, std::invalid_argument is thrown.
     * 
     * @param   r       Risk-free interest rate.
     * @param   s_0     Initial stock price.
     * @param   v_0     Initial volatility value.
     * @param   params  Heston model parameteres struct.
     * @param   alpha   Exponent Carr-Madan parameter.
     * @param   N       Integral discretization elements count.
     * @param   d_u     Log forward char. function argument grid step \f$\Delta u>0\f$.
     */
    HestonEuropeanOptionCalculator(
        double r,
        double s_0,
        double v_0,
        HestonParams &params,
        double alpha,
        int N,
        double d_u
    );

    /**
     * @brief           A calculator parameteres (alpha, N, d_u, d_k) setter
     * 
     * @details         If alpha or N (N must be even) or d_u are non-positive, std::invalid_argument is thrown.
     *                  Log strike grid step \f$\Delta k>0\f$ is calculated as \f$\Delta k = \frac{2\pi}{N\Delta u} \f$.
     */
    void set_calculator_params(double alpha, int N, double d_u);

    /**
     * @brief           Get exponent Carr-Madan parameter value
     */
    double get_alpha();

    /**
     * @brief           Get integral discretization elements count
     */
    double get_N();

    /**
     * @brief           Get log forward char. function argument grid step
     */
    double get_d_u();

    /**
     * @brief           Get log strike grid step
     */
    double get_d_k();

    /**
     * @brief           Get log strike grid of N values
     * 
     * @return          evenly spaced log strikes values with step \f$\Delta k \f$.
     */
    Eigen::RowVectorXd get_log_strike_grid();

    /**
     * @brief           Calculate european option prices at inner strikes grid by FFT
     *
     * @details         Calculates european option prices on strikes grid of shape N by given formulae by FFT method.
     *                  Strike value of option is not necessary, considering that calculate() returns
     *                  prices for particular grid. Option type considered aswell:
     *                      1) call option prices are calculated,
     *                      2) if given option is of put type, use Call-Put Parity.
     *                  For references see Project's overleaf page at Main Page.
     *
     * @param   option  European option with given time to maturity and type
     *
     * @return          vector of prices of shape N.
     */
    Eigen::RowVectorXd calculate(EuropeanOption &option);
};

#endif  // HESTON_PRICING_H