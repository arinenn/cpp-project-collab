# FFT Heston model option pricing

Plotting https://github.com/lava/matplotlib-cpp

For "matplotlib-cpp.h"
```
sudo apt install python-2.7 python-pip
python2.7 -m pip install numpy
python2.7 -m pip install matplotlib
```
```
sudo apt install python3
python3 -m pip install numpy==1.10.1 matplotlib
```

Usage
```
cmake -S . -B build -D CMAKE_CPP_COMPILER="/urs/bin/g++
cmake --build build
./build/test
```

Alternatives
- https://github.com/epezent/implot
- https://alandefreitas.github.io/matplotplusplus/
- https://www.reddit.com/r/cpp_questions/comments/yrz323/how_to_implement_matplotlib_in_c/?rdt=62318