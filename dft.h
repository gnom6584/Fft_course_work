//
// Created by Gnome on 08.06.2021.
//

#ifndef FFT__DFT_H_
#define FFT__DFT_H_

#include <cmath>
#include "alias.h"
#include "dft_16.h"

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
        const auto x_odd = x[k + N_2 + offset];
        x[k + offset] = x_even  + x_odd * exps[k * depth];
        x[k + offset + N_2] = x_even  + x_odd * exps[(k + N_2) * depth];
    }
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



const struct Operator {
public:
    enum {
        Dft, I_Dft, Fft, I_Fft
    };

    explicit Operator(int type) noexcept : type(type) {}

    std::vector<Complex> operator*
        (const std::vector<Complex>& f) const {
        switch (type) {
            case Dft: return dft(f);
            case I_Dft: return i_dft(f);
            case Fft: return fft(f);
            case I_Fft: return i_fft(f);
        }
        throw std::runtime_error("Invalid operator");
    }
private:
    const int type;
} Dft(Operator::Dft), I_Dft(Operator::I_Dft), Fft(Operator::Fft), I_Fft(Operator::I_Fft);


#endif //FFT__DFT_H_
