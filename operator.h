//
// Created by Gnome on 09.06.2021.
//

#ifndef FFT__DFT_OPERATOR_H_
#define FFT__DFT_OPERATOR_H_

#include "dft.h"

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
#endif //FFT__DFT_OPERATOR_H_
