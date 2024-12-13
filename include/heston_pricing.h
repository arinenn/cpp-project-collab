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
 * @brief       A class of Heston model european options calculator
 * 
 * @details     This class is later used for price calculations.
 *              Time to maturity and strike could be changed, but option type couldn't.
 *              If values of T or K are invalid, std::invalid_argument is thrown.
 */
class HestonEuropeanOptionCalculator {
private:
    double r;               // market parameteres
    double s_0;
    double v_0;
    HestonParams params;    // model parameteres
    double alpha;           // calculator parameteres
    int N;      // count of exponents in integral approximation
    double d_u; // u grid step
    double d_k; // log strike grid step
    double df(double t, double T);  // get discount factor
public:
    HestonEuropeanOptionCalculator(
        double r,
        double s_0,
        double v_0,
        HestonParams &params,
        double alpha,
        int N,
        double d_u
    );
    void set_calculator_params(double alpha, int N, double d_u);
    double get_alpha();
    double get_N();
    double get_d_u();
    double get_d_k();
    Eigen::RowVectorXd get_log_strike_grid();
    Eigen::RowVectorXd calculate(EuropeanOption &option);
};

#endif  // HESTON_PRICING_H