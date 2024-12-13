\mainpage

A simple yet powerful C++ library that implements Carr-Madan option pricing method for Heston model using Fast Fourier Transform.

For references see [Project's overleaf page](https://www.overleaf.com/read/crxdwgqxytmc#ddd71c).

# Features

1. [Eigen 3.4](https://eigen.tuxfamily.org/index.php?title=Main_Page) is used for vectorized calculations.
2. FFT algorithm implementation.
3. Usage of OOP: classes of european options, Heston model calculator, option prices printer.
4. Implementation of theoretical results for numerical experiments.
5. Possibility of calculated data exporting.

# Basic Usage

To use this library in other projects consider a simple pipeline:

1. Clone the library to `fft-heston-cpp`.
```bash
git clone https://github.com/arinenn/fft-heston-cpp.git
```

2. Build the library using `cmake`.
```bash
cd fft-heston-cpp
cmake -B build -S . $$ cmake --build build
```

3. (Optional) Run one of the examples.
```bash
./build/example-1
```
The tail of output should look like this:
```bash
...
K=1.32814926856 C=0.0412374522479
K=1.33325243616 C=0.0404519915744
K=1.33837521173 C=0.0396786127085
K=1.34351767063 C=0.0389172128958
K=1.34867988847 C=0.0381676879673
```

4. The next command (works for both Unix and Windows) is used to compile the file `main.cpp`:
```bash
g++ main.cpp -I./fft-heston-cpp/include ./fft-heston-cpp/build/bin/libfft-heston-cpp.a
```
```bash
your_directory/
    fft-heston-cpp/
    main.cpp
```
```cpp
#include "fft-heston-cpp/include/heston_pricing.h"
#include "fft-heston-cpp/include/print.h"

int main()
{
    // Set market state
    double r = 0.02;
    double s_0 = 1;
    double v_0 = 0.3;

    // Set rho, kappa, theta, sigma
    HestonParams params = {-0.2, 2, 0.1, 0.7};

    // Set calculator parameteres
    double alpha = 2.5;
    int N = std::pow(2, 14);     // 2^14 ~16000
    double d_u = 0.1;

    // Initiate calculator for given market of Heston model
    HestonEuropeanOptionCalculator HestonCalculator(r, s_0, v_0, params, alpha, N, d_u);

    // Set option by is_call, maturity, strike
    EuropeanOption option(true, 0.5, 1);

    // Calculate option prices for grid of strikes
    Eigen::RowVectorXd prices = HestonCalculator.calculate(option);
    Eigen::RowVectorXd strikes = HestonCalculator.get_log_strike_grid().array().exp();

    // Initiate printer for strikes K from [K_lower, K_upper]
    PricesPrinter printer(0.65, 1.35);

    // Print option prices to stdout for K from [K_lower, K_upper]
    printer.to_out(strikes, prices);

    return 0;
}
```

5. Run compiled program
```bash
main        # Windows
./main      # Unix-like
```
If binary is complied successfully, then it should run for ~1 minute (depends on system characteristics).
