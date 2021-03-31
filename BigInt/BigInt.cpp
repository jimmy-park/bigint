#include "BigInt.h"

#include <algorithm>
#include <charconv>
#include <iomanip>
#include <limits>

template <typename T, T exp>
constexpr T Pow(T base)
{
    if constexpr (exp == 0)
        return 1;
    else if constexpr (exp == 1)
        return base;

    T temp = Pow<T, exp / 2>(base);

    if constexpr (exp % 2 == 0)
        return temp * temp;
    else
        return base * temp * temp;
}

constexpr auto digit = std::numeric_limits<int>::digits10;
constexpr auto base = Pow<int, digit>(10);

BigInt::BigInt(const char* c)
    : BigInt { std::string_view { c } }
{
}

BigInt::BigInt(std::string_view sv)
{
    if (sv == "0") {
        value_.push_back(0);
        return;
    }

    if (sign_ = sv.front() != '-'; !sign_.value())
        sv = sv.substr(1);

    value_.reserve(sv.size() / digit + (sv.size() % digit ? 1 : 0));

    int value;

    while (sv.size() > digit) {
        std::from_chars(sv.data() + sv.size() - digit, sv.data() + sv.size(), value);
        value_.push_back(value);

        sv = sv.substr(0, sv.size() - digit);
    }

    std::from_chars(sv.data(), sv.data() + sv.size(), value);
    value_.push_back(value);
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi)
{
    if (!bi.sign_.has_value())
        return os << '0';

    if (!bi.sign_.value())
        os << '-';

    os << *std::crbegin(bi.value_);
    if (bi.value_.size() == 1)
        return os;

    std::for_each(std::next(std::crbegin(bi.value_)), std::crend(bi.value_), [&os](auto value) {
        os << std::setfill('0') << std::setw(digit) << value;
    });

    return os;
}

BigInt Add(const BigInt& a, const BigInt& b)
{
    auto pa = &a.value_;
    auto pb = &b.value_;

    if (pa->size() < pb->size())
        std::swap(pa, pb);

    BigInt ret;
    ret.sign_ = true;
    ret.value_.reserve(pa->size());

    int carry = 0;
    for (auto i = 0; i < pb->size(); ++i) {
        auto sum = carry + pa->at(i) + pb->at(i);
        ret.value_.push_back(sum % base);

        carry = sum / base;
    }

    for (auto i = pb->size(); i < pa->size(); ++i) {
        auto sum = carry + pa->at(i);
        ret.value_.push_back(sum % base);

        carry = sum / base;
    }

    if (carry) {
        ret.value_.reserve(pa->size() + 1);
        ret.value_.push_back(1);
    }

    return ret;
}