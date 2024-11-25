#include <iostream>
#include "fft.h"
#include "european_options.h"
#include "heston_model.h"

struct MarketParams
{
    double v;               // initial variance
    double s;               // initial underlying price
    double r;               // risk-free interest rate
    Eigen::RowVectorXcd times;  // arbitrary size double vector
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

int main()
{
    // test_Eigen();

    HestonParams params = {0.5, 0.5, 0.5, 0.5};
    std::complex<double> res = heston_log_price_cf(0.5, 0, 0.5, 0.5, 1, params); // (0.96895,-0.0613529) CORRECT
    // std::complex<double> res = heston_log_price_cf(0.5, 1, 0.5, 0.5, 1, params); // (0.879748,0.410697)  CORRECT
    std::cout << res << std::endl;

    Eigen::RowVectorXcd vector(6);
    vector << std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5),
        std::complex<double>(1.5, 5.5);
    // std::cout << vector << std::endl;
    Eigen::RowVectorXcd result(6);
    try {
        result = fft(vector);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Result1   " << result << std::endl;

    Eigen::RowVectorXcd vector2(8);
    vector2 = std::complex<double> (0.0, 2.0) * M_PI * Eigen::RowVectorXcd::LinSpaced(8, 0, 7) / 8;
    vector2 = vector2.array().exp();
    std::cout << "Result2   " << fft(vector2) << std::endl;
    return 0;
}