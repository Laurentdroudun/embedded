#include "fft_utils.h"

void twiddle_factors(std::array<Complex, N / 2> &t) {
    for (std::size_t k = 0; k < N / 2; k++) {
        t[k] = std::polar(1.0, -2.0 * PI * k / N);
    }
}

void bit_reverse_array(std::array<std::size_t, N> &unscrambled) {
    std::size_t m = std::log2(N);
    //std::size_t m = ((unsigned) (8 * sizeof(unsigned long long) - __builtin_clzll((N)) - 1));
    for (std::size_t i = 0; i < N; i++) {
        std::size_t j = i;
        j = (((j & 0xaaaaaaaa) >> 1) | ((j & 0x55555555) << 1));
        j = (((j & 0xcccccccc) >> 2) | ((j & 0x33333333) << 2));
        j = (((j & 0xf0f0f0f0) >> 4) | ((j & 0x0f0f0f0f) << 4));
        j = (((j & 0xff00ff00) >> 8) | ((j & 0x00ff00ff) << 8));
        j = ((j >> 16) | (j << 16)) >> (32 - m);
        if (i < j) {
            unscrambled[i] = j;
        }
        else {
            unscrambled[i] = i;
        }
    }
}

void ite_dit_fft(std::vector<Complex> &x) {
    std::size_t problemSize = x.size();
    std::size_t stages = std::log2(problemSize);
    std::array<Complex, N / 2> tf;
    twiddle_factors(tf);

    std::array<std::size_t, N> unscrambled;
    bit_reverse_array(unscrambled);
    for (std::size_t i = 0; i < x.size(); i++) {
        std::size_t j = unscrambled[i];
        if (i < j) {
            swap(x[i], x[j]);
        }
    }

    for (std::size_t stage = 0; stage <= stages; stage++) {
        std::size_t currentSize = 1 << stage;
        std::size_t step = stages - stage;
        std::size_t halfSize = currentSize / 2;
        for (std::size_t k = 0; k < problemSize; k = k + currentSize) {
            //for (std::size_t k = 0; k <= problemSize - currentSize; k = k + currentSize) {
            for (std::size_t j = 0; j < halfSize; j++) {
                auto u = x[k + j];
                auto v = x[k + j + halfSize] * tf[j * (1 << step)];
                x[k + j] = (u + v);
                x[k + j + halfSize] = (u - v);
            }
        }
    }
}