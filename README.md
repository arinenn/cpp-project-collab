# fft-heston-cpp

Project basis
https://www.overleaf.com/read/crxdwgqxytmc#ddd71c

Comments
- Можно переписать FFT полностью на матрицах (без циклов)
- Векторизированный подсчёт опциона? (хар-их функций)

Basic Usage

clone

build

run with prefix "-I./fft-heston-cpp/include ./fft-heston-cpp/build/bin/libfft-heston-cpp.a" (works for both Unix-like systems and Windows)
```cpp
g++ main.cpp -o main main.cpp -I./fft-heston-cpp/include ./fft-heston-cpp/build/bin/libfft-heston-cpp.a
```

(может бытЬ) run examples ...