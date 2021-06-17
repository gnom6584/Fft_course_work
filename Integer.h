//
// Created by Gnome on 17.06.2021.
//
#include <iostream>
#include "dft.h"
#ifndef FFT__INTEGER_H_
#define FFT__INTEGER_H_

inline std::vector<int> normalize(const std::vector<int>& input_number) {
    auto N = std::size(input_number);
    std::vector<int> number(N);
    for (auto i = 0u; i < N; ++i)
        number[i] = input_number[N - 1 - i];

    for (int i = 0; i < N; ++i) {
        while (number[i] >= 10) {
            number[i] -= 10;

            if (N <= i + 1) {
                number.push_back(0);
                N++;
            }

            number[i + 1] += 1;
        }
    }
    for (auto i = 0u; i < N / 2; ++i) {
        const auto temp = number[i];
        number[i] = number[N - 1 - i];
        number[N - 1 - i] = temp;
    }
    return number;
}

class Integer {
public:
    [[maybe_unused]] const static Integer zero;

    explicit Integer(const std::string& str_number) {
        const auto size = std::size(str_number);
        using namespace std;

        if(size == 0)
            throw length_error("");

        if(size != 1) {
            if (str_number.starts_with("0"))
                throw invalid_argument(str_number);
        }

        is_negative = str_number.starts_with("-");

        bool skip_first = is_negative || str_number.starts_with("+");

        if(is_negative && size == 1)
            throw invalid_argument(str_number);

        for (const auto& num : str_number) {
            if(skip_first) {
                skip_first = false;
                continue;
            }
            if(!isdigit(num))
                throw invalid_argument(str_number);
            digits.emplace_back(num - 48);
        }
    }

    [[nodiscard]] bool is_zero() const {
        return digits[0] == 0;
    }

    Integer operator*(const Integer& other) const {
        if(other.is_zero() || is_zero())
            return Integer("0");

        const auto this_digits_size = std::size(digits);
        const auto other_digits_size = std::size(other.digits);

        const auto diff = std::abs((int)other_digits_size - (int)this_digits_size);
        const auto size = std::max(other_digits_size, this_digits_size);
        const auto size_2 = size * 2;
        using namespace std;
        vector<Complex> a(size_2);
        vector<Complex> b(size_2);

        for (int i = 0; i < this_digits_size; ++i)
            a[i] = digits[i];

        for (int i = 0; i < other_digits_size; ++i)
            b[i] = other.digits[i];

        const auto ft_a = fft(a);
        const auto ft_b = fft(b);

        vector<Complex> mul_product(size_2);

        for (int i = 0; i < size_2; ++i)
            mul_product[i] = ft_a[i] * ft_b[i];

        const auto ift_product = i_fft(mul_product);

        vector<int> result_digits(size_2 - 1 - diff);
        for (int i = 0; i < size_2 - 1; ++i)
            result_digits[i] = round(ift_product[i].real());

        return Integer(normalize(result_digits), is_negative ^ other.is_negative);
    }

    bool operator==(const Integer& other) const {
        return digits == other.digits;
    }

private:
    explicit Integer(std::vector<int> number, bool negative) noexcept : digits(std::move(number)), is_negative(negative) {
    }

    std::vector<int> digits;

    bool is_negative;

    friend std::ostream& operator << (std::ostream& os, const Integer& integer);
};

std::ostream& operator << (std::ostream& os, const Integer& integer) {
    if(integer.is_negative)
        os << "-";
    for(auto digit : integer.digits)
        os << digit;
    return os;
}
#endif //FFT__INTEGER_H_
