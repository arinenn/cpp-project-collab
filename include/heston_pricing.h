#ifndef HESTON_PRICING_H
#define HESTON_PRICING_H

#include <fstream>

#include "fft.h"
#include "heston_model.h"
#include "european_options.h"

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
    double df(double t, double T);
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
    Eigen::RowVectorXd get_log_strike_grid();
    Eigen::RowVectorXd calculate(EuropeanOption &option);
    void calc_and_show(EuropeanOption &option, double K_lower, double K_upper);
    void print_results(Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices);
};

#endif  // HESTON_PRICING_H