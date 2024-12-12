#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <Eigen/Dense>

#define PRECISION 12

class PricesPrinter {
private:
    double K_lower;
    double K_upper;
public:
    PricesPrinter(double K_lower, double K_upper);
    void set_bounds(double K_lower, double K_upper);
    double get_lower();
    double get_upper();
    void to_out(Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices);
    void to_csv(const std::string &filename, Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices);
};

#endif  // PRINT_H