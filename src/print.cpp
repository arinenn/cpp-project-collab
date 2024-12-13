/**
 * @file
 * @brief Printer class for stdout and .csv data export
 */
#include "print.h"

PricesPrinter::PricesPrinter(double K_lower, double K_upper)
{
    set_bounds(K_lower, K_upper);
}

void PricesPrinter::set_bounds(double _K_lower, double _K_upper)
{
    if (_K_lower < 0 || _K_upper < 0 || (_K_lower >= _K_upper)) {
        throw std::invalid_argument("Interval [K_lower, K_upper] must be non-empty and of positive values.");
    }
    K_lower = _K_lower;
    K_upper = _K_upper;
}

double PricesPrinter::get_lower()
{
    return K_lower;
}

double PricesPrinter::get_upper()
{
    return K_upper;
}

void PricesPrinter::to_out(Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices)
{
    for (int i=0; i < strikes.cols(); i++) {
        if ((strikes[i] >= K_lower) && (strikes[i] <= K_upper)) {
            std::cout << std::setprecision(PRECISION) << "K=" << strikes[i] << "\tC=" << prices[i] << std::endl;
        } else if (strikes[i] > K_upper) {
            break;
        }
    }
}

void PricesPrinter::to_csv(const std::string &filename, Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices)
{
    std::ofstream fout(filename + ".csv"); 
    fout << "K,C" << std::endl;
    for (int i=0; i < strikes.cols(); i++) {
        if ((strikes[i] >= K_lower) && (strikes[i] <= K_upper)) {
            fout << std::setprecision(PRECISION) << strikes[i] << "," << prices[i] << std::endl;
        } else if (strikes[i] > K_upper) {
            break;
        }
    }
    fout.close();
}