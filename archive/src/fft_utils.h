#ifndef FFT_UTILS_H
#define FFT_UTILS_H

#include <array>
#include <vector>
#include <complex>
#include "constants.h"

typedef std::complex<float> Complex;

void twiddle_factors(std::array<Complex, N / 2> &t);
void bit_reverse_array(std::array<std::size_t, N> &unscrambled);
void ite_dit_fft(std::vector<Complex> &x);

#endif