/**
 * @file
 * @brief Printer class for stdout and .csv data export
 */
#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <Eigen/Dense>

//! Output after dot precision.
#define PRECISION 12

/**
 * @brief       A calculated prices printer
 * 
 * @details     This class is used for calculated prices export.
 *              It's purpose is to export values of options with strikes from given interval.
 */
class PricesPrinter
{
private:
    //! Upper bound of strike value.
    double K_lower;
    //! Lower bound of strike value.
    double K_upper;
public:
    /**
     * @brief   A PricesPrinter constructor
     * 
     * @details Sets inner interval. For invalid interval bounds exception is thrown.
     * 
     * @param   K_lower Upper bound of strike value
     * @param   K_upper Lpper bound of strike value
     */
    PricesPrinter(double K_lower, double K_upper);

    /**
     * @brief   A interval setter
     * 
     * @details Sets inner interval. For invalid interval bounds exception is thrown.
     * 
     * @param   K_lower Upper bound of strike value
     * @param   K_upper Lpper bound of strike value
     */
    void set_bounds(double K_lower, double K_upper);

    //! Get upper bound of strike value.
    double get_lower();

    //! Get lower bound of strike value.
    double get_upper();

    /**
     * @brief           Print strike to option price table to stdout.
     *
     * @details         Prints prices only for strikes for saved interval.
     *                  As output stream std::cout is chosen.
     *                  Standard pipeline is
     *                      1) calculate prices by Calculator.calculate, 
     *                      2) calculate strikes as exponent of log strikes grid given by Calculator.get_log_strike_grid(), 
     *                      3) give strikes, prices to Printer.to_out
     * 
     * @warning         There is no input vectors check. Be cautious to use this function outside of this project.
     * 
     * @param   strikes     Vector of doubles of strike values
     * @param   prices      Vector of doubles of prices values
     *
     */
    void to_out(Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices);

    /**
     * @brief           Print strike to option price table to filename.csv
     *
     * @details         Prints prices only for strikes for saved interval.
     *                  As output stream std::ostream("filename.csv") is chosen.
     *                  Standard pipeline is
     *                      1) calculate prices by Calculator.calculate, 
     *                      2) calculate strikes as exponent of log strikes grid given by Calculator.get_log_strike_grid(), 
     *                      3) give strikes, prices to Printer.to_csv
     * 
     * @warning         There is no input vectors check. Be cautious to use this function outside of this project.
     * 
     * @param   strikes     Vector of doubles of strike values
     * @param   prices      Vector of doubles of prices values
     *
     */
    void to_csv(const std::string &filename, Eigen::RowVectorXd &strikes, Eigen::RowVectorXd &prices);
};

#endif  // PRINT_H