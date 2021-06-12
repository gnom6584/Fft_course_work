//
// Created by Gnome on 08.06.2021.
//

#ifndef FFT__DFT_H_
#define FFT__DFT_H_

#include <cmath>
#include "alias.h"
#include "dft_16.h"
#include "dft_16_simd.h"

const auto img_i = Complex(0.0, 1.0);
const auto i2pi = 2.0 * M_PI * img_i;

inline std::vector<Complex> dft(const std::vector<Complex>& f) {
    const auto N = std::size(f);
    std::vector<Complex> x(N);
    for(auto k = 0u; k < N; ++k) {
        auto x_k = Complex(0.0, 0.0);
        for(auto j = 0u; j < N; ++j)
            x_k += f[j]
                * std::exp(-i2pi * (j * ((Real)k / N)));
        x[k] = x_k;
    }
    return x;
}

inline std::vector<Complex> i_dft(const std::vector<Complex>& x) {
    const auto N = std::size(x);
    std::vector<Complex> f(N);
    for(auto k = 0u; k < N; ++k) {
        auto f_k = Complex(0.0, 0.0);
        for(auto j = 0u; j < N; ++j)
            f_k += x[j]
                * std::exp(i2pi * (j * ((Real)k / N)));
        f[k] = f_k / (Real) N;
    }
    return f;
}

inline std::vector<Complex> fft(const std::vector<Complex>& f) {
    const auto N = std::size(f);

    if(N <= 16)
        return dft(f);

    std::vector<Complex> x(N);

    const auto N_2 = N / 2;
    std::vector<Complex> f_even(N_2);
    std::vector<Complex> f_odd(N_2);

    for(auto m = 0u, m_2 = 0u; m < N_2; m++, m_2 = 2.0 * m) {
        f_even[m] = f[m_2];
        f_odd[m] = f[m_2 + 1];
    }

    const auto x_even = fft(f_even);
    const auto x_odd = fft(f_odd);

    for(auto k = 0u; k < N; k++) {
        auto r_k = k % N_2;
        x[k] = x_even[r_k] + x_odd[r_k] * std::exp(-i2pi * ((Real)k / N));
    }

    return x;
}

inline std::vector<Complex> fft_1(const std::vector<Complex>& f, const std::vector<Complex>& exps, int depth = 1) {
    const auto N = std::size(f);

    if(N <= 16)
        return dft(f);

    std::vector<Complex> x(N);

    const auto N_2 = N / 2;
    std::vector<Complex> f_even(N_2);
    std::vector<Complex> f_odd(N_2);

    for(auto m = 0u, m_2 = 0u; m < N_2; m++, m_2 = 2.0 * m) {
        f_even[m] = f[m_2];
        f_odd[m] = f[m_2 + 1];
    }

    const auto x_even = fft_1(f_even, exps, depth * 2);
    const auto x_odd = fft_1(f_odd, exps, depth * 2);

    for(auto k = 0u; k < N; k++) {
        auto r_k = k % N_2;
        x[k] = x_even[r_k] + x_odd[r_k] * exps[k * depth];
    }

    return x;
}

inline void fft_2(const std::vector<Complex>& f, std::vector<Complex>& x, const std::vector<Complex>& exps,
    unsigned int N,
    unsigned int depth,
    unsigned int odd,
    unsigned int offset) {

    if(N <= 16) {
        for(auto k = 0u; k < N; ++k) {
            auto x_k = Complex(0.0, 0.0);
            for(auto j = 0u; j < N; ++j)
                x_k += f[j * depth + odd]
                    * std::exp(-i2pi * (j * ((Real)k / N)));
            x[k + offset] = x_k;
        }
        return;
    }

    const auto N_2 = N / 2;
    fft_2(f, x, exps,  N / 2, depth * 2, odd, offset);
    fft_2(f, x, exps,  N / 2, depth * 2, odd + depth, offset + N_2);

    for(auto k = 0u; k < N_2; ++k) {
        const auto x_even = x[k + offset];
        const auto x_odd = x[k + N_2 + offset];
        x[k + offset] = x_even  + x_odd * exps[k * depth];
        x[k + offset + N_2] = x_even  + x_odd * exps[(k + N_2) * depth];
    }
}
inline void fft_3(const std::vector<Complex>& f, std::vector<Complex>& x, const std::vector<Complex>& exps,
    unsigned int N,
    unsigned int depth,
    unsigned int odd,
    unsigned int offset) {
    if(N <= 16) {

        dft_16(f, x, depth, odd, offset);
        return;
    }

    const auto N_2 = N / 2;
    fft_3(f, x, exps,  N / 2, depth * 2, odd, offset);
    fft_3(f, x, exps,  N / 2, depth * 2, odd + depth, offset + N_2);

    for(auto k = 0u; k < N_2; ++k) {
        const auto x_even = x[k + offset];
        const auto x_odd = x[k + N_2 + offset] * exps[k * depth];
        x[k + offset] = x_even + x_odd;
        x[k + offset + N_2] = x_even  - x_odd;
    }
}

inline std::vector<Complex> compute_exp(size_t N) {
    std::vector<Complex> exps;
    exps.resize(N);
    auto N_4 = N / 4;
    auto N_2 = N_4 * 2;
    auto N_3_4 = N_4 * 3;
    for (auto k = 0ul; k < N_4; k++) {
        auto e = std::exp(-i2pi * ((Real) k / N));
        exps[k] = e;
    }

    for (auto k = N_4; k < N_2; k++) {
        auto e = exps[k - N_2];
        exps[k] = Complex(e.imag(), -e.real());
    }

    for (auto k = N_2; k < N_3_4; k++) {
        auto e = exps[k - N_3_4];
        exps[k] = Complex(-e.real(), -e.imag());
    }

    for (auto k = N_3_4; k < N; k++) {
        auto e = exps[k - N_3_4];
        exps[k] = Complex(-e.imag(), e.real());
    }


    return exps;
}

inline bool is_2_power(unsigned  int x) {
    return x != 0 && !(x & (x - 1));
}

inline bool next_2_power(unsigned  int x) {
    return pow(2, ceil(log(x)/log(2)));;
}

#include <tbb/parallel_for.h>
inline std::vector<Complex> fft_4(const std::vector<Complex>& f) {
    using namespace std;

    const auto f_N = size(f);

    if(f_N <= 16)
        return dft(f);

    vector<Complex> x;
    x.reserve(f_N);

    auto exps = vector<Complex>();
    const auto f_N_2 = f_N / 2;
    exps.reserve(f_N_2);

    for (int k = 0; k < f_N_2; ++k)
        exps[k] = exp(-i2pi * ((Real) k / f_N));

    auto d = 1;
    vector<int> indices(1, 0);
    while (d < f_N / 16) {
        auto new_indices = vector<int>(d);
        for (int i = 0; i < d; i += 2) {
            new_indices[i] = indices[i / 2];
            new_indices[i + 1] = new_indices[i] + d;
        }
        indices = new_indices;
        d *= 2;
    }

    auto d_2 = d / 2;

    tbb::parallel_for( tbb::blocked_range<unsigned int>(0, d),
        [&](tbb::blocked_range<unsigned int> range)
    {
        for(auto i = std::begin(range); i < std::end(range); ++i)
            dft_16_simd(f, x, d, indices[i % d_2] + i / d_2, i * 16);
    });

    d = d_2;
    for (auto off_cof = 32; d >= 1; d /= 2, off_cof *= 2) {
        tbb::parallel_for( tbb::blocked_range<unsigned int>(0, d),
            [&](tbb::blocked_range<unsigned int> range) {
                for(auto i = std::begin(range); i < std::end(range); ++i) {
                    const auto N = f_N / d;
                    const auto N_2 = N / 2;
                    const auto offset = i * off_cof;
                    for (auto k = 0u; k < N_2; k += 4) {
                        auto k_1 = k + 1;
                        auto k_2 = k + 2;
                        auto k_3 = k + 3;
                        auto k_offset = k + offset;
                        auto k_offset_1 = k_offset + 1;
                        auto k_offset_2 = k_offset + 2;
                        auto k_offset_3 = k_offset + 3;
                        auto k_N_2 = k + N_2;
                        auto k_N_2_offset = k_N_2 + offset;
                        auto k_N_2_offset_1 = k_N_2_offset + 1;
                        auto k_N_2_offset_2 = k_N_2_offset + 2;
                        auto k_N_2_offset_3 = k_N_2_offset + 3;

                        double r_even_a[4] = {x[k + offset].real(), x[k_offset_1].real(), x[k_offset_2].real(), x[k_offset_3].real()};
                        double i_even_a[4] = {x[k + offset].imag(), x[k_offset_1].imag(), x[k_offset_2].imag(), x[k_offset_3].imag()};
                        double r_odd_a[4] = {x[k_N_2_offset].real(), x[k_N_2_offset_1].real(), x[k_N_2_offset_2].real(), x[k_N_2_offset_3].real()};
                        double i_odd_a[4] = {x[k_N_2_offset].imag(), x[k_N_2_offset_1].imag(), x[k_N_2_offset_2].imag(), x[k_N_2_offset_3].imag()};
                        double r_exp_a[4] =  {exps[k * d].real(), exps[k_1 * d].real(), exps[k_2 * d].real(), exps[k_3 * d].real()};
                        double i_exp_a[4] =  {exps[k * d].imag(), exps[k_1 * d].imag(), exps[k_2 * d].imag(), exps[k_3 * d].imag()};

                        auto r_even_m = _mm256_load_pd(r_even_a);
                        auto i_even_m = _mm256_load_pd(i_even_a);

                        auto r_odd_m = _mm256_load_pd(r_odd_a);
                        auto i_odd_m = _mm256_load_pd(i_odd_a);

                        auto r_exp_m = _mm256_load_pd(r_exp_a);
                        auto i_exp_m = _mm256_load_pd(i_exp_a);

                        auto m_r = _mm256_sub_pd(_mm256_mul_pd(r_odd_m, r_exp_m), _mm256_mul_pd(i_odd_m, i_exp_m));
                        auto m_i = _mm256_add_pd(_mm256_mul_pd(i_odd_m, r_exp_m), _mm256_mul_pd(r_odd_m, i_exp_m));

                        _mm256_storeu_pd(r_even_a, _mm256_add_pd(r_even_m, m_r));
                        _mm256_storeu_pd(i_even_a, _mm256_add_pd(i_even_m, m_i));
                        _mm256_storeu_pd(r_odd_a, _mm256_sub_pd(r_even_m, m_r));
                        _mm256_storeu_pd(i_odd_a, _mm256_sub_pd(i_even_m, m_i));

                        x[k_offset] = Complex(r_even_a[0], i_even_a[0]);
                        x[k_offset_1] = Complex(r_even_a[1], i_even_a[1]);
                        x[k_offset_2] = Complex(r_even_a[2], i_even_a[2]);
                        x[k_offset_3] = Complex(r_even_a[3], i_even_a[3]);
                        x[k_N_2_offset] = Complex(r_odd_a[0], i_odd_a[0]);
                        x[k_N_2_offset_1] = Complex(r_odd_a[1], i_odd_a[1]);
                        x[k_N_2_offset_2] = Complex(r_odd_a[2], i_odd_a[2]);
                        x[k_N_2_offset_3] = Complex(r_odd_a[3], i_odd_a[3]);
                    }
                }
        });
    }
    return x;
}

inline std::vector<Complex> fft_5(const std::vector<Complex>& f) {
    using namespace std;

    const auto f_N = size(f);

    if(f_N <= 16)
        return dft(f);

    vector<Complex> x;
    x.reserve(f_N);

    auto exps = vector<Complex>();
    const auto f_N_2 = f_N / 2;
    exps.reserve(f_N_2);

    for (int k = 0; k < f_N_2; ++k)
        exps[k] = exp(-i2pi * ((Real) k / f_N));

    auto d = 1;
    vector<int> indices(1, 0);
    while (d < f_N / 16) {
        auto new_indices = vector<int>(d);
        for (int i = 0; i < d; i += 2) {
            new_indices[i] = indices[i / 2];
            new_indices[i + 1] = new_indices[i] + d;
        }
        indices = new_indices;
        d *= 2;
    }

    auto d_2 = d / 2;

    tbb::parallel_for( tbb::blocked_range<unsigned int>(0, d),
        [&](tbb::blocked_range<unsigned int> range)
        {
            for(auto i = std::begin(range); i < std::end(range); ++i)
                dft_16(f, x, d, indices[i % d_2] + i / d_2, i * 16);
        });

    d = d_2;
    for (auto off_cof = 32; d >= 1; d /= 2, off_cof *= 2) {
        tbb::parallel_for( tbb::blocked_range<unsigned int>(0, d),
            [&](tbb::blocked_range<unsigned int> range) {
                for(auto i = std::begin(range); i < std::end(range); ++i) {
                    const auto N = f_N / d;
                    const auto N_2 = N / 2;
                    const auto offset = i * off_cof;
                    for (auto k = 0u; k < N_2; k++) {
                        const auto x_even = x[k + offset];
                        const auto x_odd = x[k + N_2 + offset] * exps[k * d];
                        x[k + offset] = x_even + x_odd;
                        x[k + offset + N_2] = x_even  - x_odd;
                    }
                }
            });
    }
    return x;
}

inline std::vector<Complex> i_fft(const std::vector<Complex>& f) {
    const auto N = std::size(f);

    if(N <= 16)
        return i_dft(f);

    std::vector<Complex> x(N);

    const auto N_2 = N / 2;
    std::vector<Complex> f_even(N_2);
    std::vector<Complex> f_odd(N_2);

    for(auto m = 0u, m_2 = 0u; m < N_2; m++, m_2 = 2.0 * m) {
        f_even[m] = f[m_2];
        f_odd[m] = f[m_2 + 1];
    }

    const auto x_even = i_fft(f_even);
    const auto x_odd = i_fft(f_odd);

    for(auto k = 0u; k < N; k++) {
        auto r_k = k % N_2;
        x[k] = (x_even[r_k] + x_odd[r_k] * std::exp(i2pi * ((Real)k / N))) / 2.0;
    }

    return x;
}

#endif //FFT__DFT_H_
