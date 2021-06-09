//
// Created by Gnome on 09.06.2021.
//

#ifndef FFT__DFT_16_H_
#define FFT__DFT_16_H_

#include "alias.h"

inline constexpr auto exp_0 = Complex(1, -0); //e^{-i*2*pi*0*0/16}
inline constexpr auto exp_1 = Complex(0.92388, -0.382683); //e^{-i*2*pi*1*1/16}
inline constexpr auto exp_2 = Complex(0.707107, -0.707107); //e^{-i*2*pi*1*2/16}
inline constexpr auto exp_3 = Complex(0.382683, -0.92388); //e^{-i*2*pi*1*3/16}
inline constexpr auto exp_4 = Complex(6.12323e-17, -1); //e^{-i*2*pi*1*4/16}
inline constexpr auto exp_5 = Complex(-0.382683, -0.92388); //e^{-i*2*pi*1*5/16}
inline constexpr auto exp_6 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*1*6/16}
inline constexpr auto exp_7 = Complex(-0.92388, -0.382683); //e^{-i*2*pi*1*7/16}
inline constexpr auto exp_8 = Complex(-1, -1.22465e-16); //e^{-i*2*pi*1*8/16}
inline constexpr auto exp_9 = Complex(-0.92388, 0.382683); //e^{-i*2*pi*1*9/16}
inline constexpr auto exp_10 = Complex(-0.707107, 0.707107); //e^{-i*2*pi*1*10/16}
inline constexpr auto exp_11 = Complex(-0.382683, 0.92388); //e^{-i*2*pi*1*11/16}
inline constexpr auto exp_12 = Complex(-1.83697e-16, 1); //e^{-i*2*pi*1*12/16}
inline constexpr auto exp_13 = Complex(0.382683, 0.92388); //e^{-i*2*pi*1*13/16}
inline constexpr auto exp_14 = Complex(0.707107, 0.707107); //e^{-i*2*pi*1*14/16}
inline constexpr auto exp_15 = Complex(0.92388, 0.382683); //e^{-i*2*pi*1*15/16}
inline constexpr auto exp_16 = Complex(1, 2.44929e-16); //e^{-i*2*pi*2*8/16}
inline constexpr auto exp_17 = Complex(0.707107, -0.707107); //e^{-i*2*pi*2*9/16}
inline constexpr auto exp_18 = Complex(3.06162e-16, -1); //e^{-i*2*pi*2*10/16}
inline constexpr auto exp_19 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*2*11/16}
inline constexpr auto exp_20 = Complex(-1, -3.67394e-16); //e^{-i*2*pi*2*12/16}
inline constexpr auto exp_21 = Complex(-0.707107, 0.707107); //e^{-i*2*pi*2*13/16}
inline constexpr auto exp_22 = Complex(-4.28626e-16, 1); //e^{-i*2*pi*2*14/16}
inline constexpr auto exp_23 = Complex(0.707107, 0.707107); //e^{-i*2*pi*2*15/16}
inline constexpr auto exp_24 = Complex(-0.382683, -0.92388); //e^{-i*2*pi*3*7/16}
inline constexpr auto exp_25 = Complex(-0.382683, 0.92388); //e^{-i*2*pi*3*9/16}
inline constexpr auto exp_26 = Complex(0.92388, -0.382683); //e^{-i*2*pi*3*11/16}
inline constexpr auto exp_27 = Complex(5.51091e-16, -1); //e^{-i*2*pi*3*12/16}
inline constexpr auto exp_28 = Complex(-0.92388, -0.382683); //e^{-i*2*pi*3*13/16}
inline constexpr auto exp_29 = Complex(-0.707107, 0.707107); //e^{-i*2*pi*3*14/16}
inline constexpr auto exp_30 = Complex(0.382683, 0.92388); //e^{-i*2*pi*3*15/16}
inline constexpr auto exp_31 = Complex(1, 4.89859e-16); //e^{-i*2*pi*4*8/16}
inline constexpr auto exp_32 = Complex(-1, -6.12323e-16); //e^{-i*2*pi*4*10/16}
inline constexpr auto exp_33 = Complex(-2.44991e-15, 1); //e^{-i*2*pi*4*11/16}
inline constexpr auto exp_34 = Complex(1, 7.34788e-16); //e^{-i*2*pi*4*12/16}
inline constexpr auto exp_35 = Complex(-9.80336e-16, -1); //e^{-i*2*pi*4*13/16}
inline constexpr auto exp_36 = Complex(-1, -8.57253e-16); //e^{-i*2*pi*4*14/16}
inline constexpr auto exp_37 = Complex(-2.69484e-15, 1); //e^{-i*2*pi*4*15/16}
inline constexpr auto exp_38 = Complex(-0.92388, 0.382683); //e^{-i*2*pi*5*5/16}
inline constexpr auto exp_39 = Complex(0.382683, -0.92388); //e^{-i*2*pi*5*7/16}
inline constexpr auto exp_40 = Complex(0.707107, -0.707107); //e^{-i*2*pi*5*10/16}
inline constexpr auto exp_41 = Complex(-0.92388, -0.382683); //e^{-i*2*pi*5*11/16}
inline constexpr auto exp_42 = Complex(0.92388, -0.382683); //e^{-i*2*pi*5*13/16}
inline constexpr auto exp_43 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*5*14/16}
inline constexpr auto exp_44 = Complex(-0.382683, 0.92388); //e^{-i*2*pi*5*15/16}
inline constexpr auto exp_45 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*6*9/16}
inline constexpr auto exp_46 = Complex(0.707107, -0.707107); //e^{-i*2*pi*6*11/16}
inline constexpr auto exp_47 = Complex(-1, -1.10218e-15); //e^{-i*2*pi*6*12/16}
inline constexpr auto exp_48 = Complex(0.707107, 0.707107); //e^{-i*2*pi*6*13/16}
inline constexpr auto exp_49 = Complex(-4.90478e-16, -1); //e^{-i*2*pi*6*14/16}
inline constexpr auto exp_50 = Complex(-0.707107, 0.707107); //e^{-i*2*pi*6*15/16}
inline constexpr auto exp_51 = Complex(0.92388, -0.382683); //e^{-i*2*pi*7*7/16}
inline constexpr auto exp_52 = Complex(0.92388, 0.382683); //e^{-i*2*pi*7*9/16}
inline constexpr auto exp_53 = Complex(0.382683, 0.92388); //e^{-i*2*pi*7*11/16}
inline constexpr auto exp_54 = Complex(-0.382683, 0.92388); //e^{-i*2*pi*7*13/16}
inline constexpr auto exp_55 = Complex(0.707107, -0.707107); //e^{-i*2*pi*7*14/16}
inline constexpr auto exp_56 = Complex(-0.92388, 0.382683); //e^{-i*2*pi*7*15/16}
inline constexpr auto exp_57 = Complex(1, 9.79717e-16); //e^{-i*2*pi*8*8/16}
inline constexpr auto exp_58 = Complex(1, 1.22465e-15); //e^{-i*2*pi*8*10/16}
inline constexpr auto exp_59 = Complex(-1, -4.89983e-15); //e^{-i*2*pi*8*11/16}
inline constexpr auto exp_60 = Complex(1, 1.46958e-15); //e^{-i*2*pi*8*12/16}
inline constexpr auto exp_61 = Complex(-1, 1.96067e-15); //e^{-i*2*pi*8*13/16}
inline constexpr auto exp_62 = Complex(1, 1.71451e-15); //e^{-i*2*pi*8*14/16}
inline constexpr auto exp_63 = Complex(-1, -5.38968e-15); //e^{-i*2*pi*8*15/16}
inline constexpr auto exp_64 = Complex(0.92388, -0.382683); //e^{-i*2*pi*9*9/16}
inline constexpr auto exp_65 = Complex(0.382683, -0.92388); //e^{-i*2*pi*9*11/16}
inline constexpr auto exp_66 = Complex(-3.42963e-15, 1); //e^{-i*2*pi*9*12/16}
inline constexpr auto exp_67 = Complex(-0.382683, -0.92388); //e^{-i*2*pi*9*13/16}
inline constexpr auto exp_68 = Complex(0.707107, 0.707107); //e^{-i*2*pi*9*14/16}
inline constexpr auto exp_69 = Complex(-0.92388, -0.382683); //e^{-i*2*pi*9*15/16}
inline constexpr auto exp_70 = Complex(-2.45548e-16, -1); //e^{-i*2*pi*10*10/16}
inline constexpr auto exp_71 = Complex(0.707107, 0.707107); //e^{-i*2*pi*10*11/16}
inline constexpr auto exp_72 = Complex(0.707107, -0.707107); //e^{-i*2*pi*10*13/16}
inline constexpr auto exp_73 = Complex(-3.91949e-15, 1); //e^{-i*2*pi*10*14/16}
inline constexpr auto exp_74 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*10*15/16}
inline constexpr auto exp_75 = Complex(-0.92388, 0.382683); //e^{-i*2*pi*11*11/16}
inline constexpr auto exp_76 = Complex(2.4431e-16, -1); //e^{-i*2*pi*11*12/16}
inline constexpr auto exp_77 = Complex(0.92388, 0.382683); //e^{-i*2*pi*11*13/16}
inline constexpr auto exp_78 = Complex(-0.707107, 0.707107); //e^{-i*2*pi*11*14/16}
inline constexpr auto exp_79 = Complex(-0.382683, -0.92388); //e^{-i*2*pi*11*15/16}
inline constexpr auto exp_80 = Complex(1, 2.20436e-15); //e^{-i*2*pi*12*12/16}
inline constexpr auto exp_81 = Complex(-4.16442e-15, 1); //e^{-i*2*pi*12*13/16}
inline constexpr auto exp_82 = Complex(-1, 9.80955e-16); //e^{-i*2*pi*12*14/16}
inline constexpr auto exp_83 = Complex(9.79098e-16, -1); //e^{-i*2*pi*12*15/16}
inline constexpr auto exp_84 = Complex(-0.92388, 0.382683); //e^{-i*2*pi*13*13/16}
inline constexpr auto exp_85 = Complex(-0.707107, -0.707107); //e^{-i*2*pi*13*14/16}
inline constexpr auto exp_86 = Complex(0.382683, -0.92388); //e^{-i*2*pi*13*15/16}
inline constexpr auto exp_87 = Complex(8.32946e-15, -1); //e^{-i*2*pi*14*14/16}
inline constexpr auto exp_88 = Complex(0.707107, -0.707107); //e^{-i*2*pi*14*15/16}
inline constexpr auto exp_89 = Complex(0.92388, -0.382683); //e^{-i*2*pi*15*15/16}

inline void dft_16(const std::vector<Complex>& f, std::vector<Complex>& x, unsigned int depth, unsigned int odd, unsigned int offset) {
    const auto f_0 = f[0 * depth + odd];
    const auto f_1 = f[1 * depth + odd];
    const auto f_2 = f[2 * depth + odd];
    const auto f_3 = f[3 * depth + odd];
    const auto f_4 = f[4 * depth + odd];
    const auto f_5 = f[5 * depth + odd];
    const auto f_6 = f[6 * depth + odd];
    const auto f_7 = f[7 * depth + odd];
    const auto f_8 = f[8 * depth + odd];
    const auto f_9 = f[9 * depth + odd];
    const auto f_10 = f[10 * depth + odd];
    const auto f_11 = f[11 * depth + odd];
    const auto f_12 = f[12 * depth + odd];
    const auto f_13 = f[13 * depth + odd];
    const auto f_14 = f[14 * depth + odd];
    const auto f_15 = f[15 * depth + odd];
    const auto f_0_exp_0 = f_0 * exp_0;
    x[0 + offset] = f_0_exp_0 + f_1 * exp_0 + f_2 * exp_0 + f_3 * exp_0 + f_4 * exp_0 + f_5 * exp_0 + f_6 * exp_0 + f_7 * exp_0 + f_8 * exp_0 + f_9 * exp_0 + f_10 * exp_0 + f_11 * exp_0 + f_12 * exp_0 + f_13 * exp_0 + f_14 * exp_0 + f_15 * exp_0;
    x[1 + offset] = f_0_exp_0 + f_1 * exp_1 + f_2 * exp_2 + f_3 * exp_3 + f_4 * exp_4 + f_5 * exp_5 + f_6 * exp_6 + f_7 * exp_7 + f_8 * exp_8 + f_9 * exp_9 + f_10 * exp_10 + f_11 * exp_11 + f_12 * exp_12 + f_13 * exp_13 + f_14 * exp_14 + f_15 * exp_15;
    x[2 + offset] = f_0_exp_0 + f_1 * exp_2 + f_2 * exp_4 + f_3 * exp_6 + f_4 * exp_8 + f_5 * exp_10 + f_6 * exp_12 + f_7 * exp_14 + f_8 * exp_16 + f_9 * exp_17 + f_10 * exp_18 + f_11 * exp_19 + f_12 * exp_20 + f_13 * exp_21 + f_14 * exp_22 + f_15 * exp_23;
    x[3 + offset] = f_0_exp_0 + f_1 * exp_3 + f_2 * exp_6 + f_3 * exp_9 + f_4 * exp_12 + f_5 * exp_15 + f_6 * exp_17 + f_7 * exp_24 + f_8 * exp_20 + f_9 * exp_25 + f_10 * exp_23 + f_11 * exp_26 + f_12 * exp_27 + f_13 * exp_28 + f_14 * exp_29 + f_15 * exp_30;
    x[4 + offset] = f_0_exp_0 + f_1 * exp_4 + f_2 * exp_8 + f_3 * exp_12 + f_4 * exp_16 + f_5 * exp_18 + f_6 * exp_20 + f_7 * exp_22 + f_8 * exp_31 + f_9 * exp_27 + f_10 * exp_32 + f_11 * exp_33 + f_12 * exp_34 + f_13 * exp_35 + f_14 * exp_36 + f_15 * exp_37;
    x[5 + offset] = f_0_exp_0 + f_1 * exp_5 + f_2 * exp_10 + f_3 * exp_15 + f_4 * exp_18 + f_5 * exp_38 + f_6 * exp_23 + f_7 * exp_39 + f_8 * exp_32 + f_9 * exp_30 + f_10 * exp_40 + f_11 * exp_41 + f_12 * exp_37 + f_13 * exp_42 + f_14 * exp_43 + f_15 * exp_44;
    x[6 + offset] = f_0_exp_0 + f_1 * exp_6 + f_2 * exp_12 + f_3 * exp_17 + f_4 * exp_20 + f_5 * exp_23 + f_6 * exp_27 + f_7 * exp_29 + f_8 * exp_34 + f_9 * exp_45 + f_10 * exp_37 + f_11 * exp_46 + f_12 * exp_47 + f_13 * exp_48 + f_14 * exp_49 + f_15 * exp_50;
    x[7 + offset] = f_0_exp_0 + f_1 * exp_7 + f_2 * exp_14 + f_3 * exp_24 + f_4 * exp_22 + f_5 * exp_39 + f_6 * exp_29 + f_7 * exp_51 + f_8 * exp_36 + f_9 * exp_52 + f_10 * exp_43 + f_11 * exp_53 + f_12 * exp_49 + f_13 * exp_54 + f_14 * exp_55 + f_15 * exp_56;
    x[8 + offset] = f_0_exp_0 + f_1 * exp_8 + f_2 * exp_16 + f_3 * exp_20 + f_4 * exp_31 + f_5 * exp_32 + f_6 * exp_34 + f_7 * exp_36 + f_8 * exp_57 + f_9 * exp_47 + f_10 * exp_58 + f_11 * exp_59 + f_12 * exp_60 + f_13 * exp_61 + f_14 * exp_62 + f_15 * exp_63;
    x[9 + offset] = f_0_exp_0 + f_1 * exp_9 + f_2 * exp_17 + f_3 * exp_25 + f_4 * exp_27 + f_5 * exp_30 + f_6 * exp_45 + f_7 * exp_52 + f_8 * exp_47 + f_9 * exp_64 + f_10 * exp_50 + f_11 * exp_65 + f_12 * exp_66 + f_13 * exp_67 + f_14 * exp_68 + f_15 * exp_69;
    x[10 + offset] = f_0_exp_0 + f_1 * exp_10 + f_2 * exp_18 + f_3 * exp_23 + f_4 * exp_32 + f_5 * exp_40 + f_6 * exp_37 + f_7 * exp_43 + f_8 * exp_58 + f_9 * exp_50 + f_10 * exp_70 + f_11 * exp_71 + f_12 * exp_63 + f_13 * exp_72 + f_14 * exp_73 + f_15 * exp_74;
    x[11 + offset] = f_0_exp_0 + f_1 * exp_11 + f_2 * exp_19 + f_3 * exp_26 + f_4 * exp_33 + f_5 * exp_41 + f_6 * exp_46 + f_7 * exp_53 + f_8 * exp_59 + f_9 * exp_65 + f_10 * exp_71 + f_11 * exp_75 + f_12 * exp_76 + f_13 * exp_77 + f_14 * exp_78 + f_15 * exp_79;
    x[12 + offset] = f_0_exp_0 + f_1 * exp_12 + f_2 * exp_20 + f_3 * exp_27 + f_4 * exp_34 + f_5 * exp_37 + f_6 * exp_47 + f_7 * exp_49 + f_8 * exp_60 + f_9 * exp_66 + f_10 * exp_63 + f_11 * exp_76 + f_12 * exp_80 + f_13 * exp_81 + f_14 * exp_82 + f_15 * exp_83;
    x[13 + offset] = f_0_exp_0 + f_1 * exp_13 + f_2 * exp_21 + f_3 * exp_28 + f_4 * exp_35 + f_5 * exp_42 + f_6 * exp_48 + f_7 * exp_54 + f_8 * exp_61 + f_9 * exp_67 + f_10 * exp_72 + f_11 * exp_77 + f_12 * exp_81 + f_13 * exp_84 + f_14 * exp_85 + f_15 * exp_86;
    x[14 + offset] = f_0_exp_0 + f_1 * exp_14 + f_2 * exp_22 + f_3 * exp_29 + f_4 * exp_36 + f_5 * exp_43 + f_6 * exp_49 + f_7 * exp_55 + f_8 * exp_62 + f_9 * exp_68 + f_10 * exp_73 + f_11 * exp_78 + f_12 * exp_82 + f_13 * exp_85 + f_14 * exp_87 + f_15 * exp_88;
    x[15 + offset] = f_0_exp_0 + f_1 * exp_15 + f_2 * exp_23 + f_3 * exp_30 + f_4 * exp_37 + f_5 * exp_44 + f_6 * exp_50 + f_7 * exp_56 + f_8 * exp_63 + f_9 * exp_69 + f_10 * exp_74 + f_11 * exp_79 + f_12 * exp_83 + f_13 * exp_86 + f_14 * exp_88 + f_15 * exp_89;
}
#endif //FFT__DFT_16_H_
