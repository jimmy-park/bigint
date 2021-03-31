#ifndef BIGINT_H_
#define BIGINT_H_

#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

class BigInt {
public:
    BigInt() = default;
    BigInt(const char* c);
    BigInt(std::string_view sv);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
    friend BigInt Add(const BigInt& a, const BigInt& b);

private:
    std::optional<bool> sign_; // false: negative, true: positive, empty: zero
    std::vector<int> value_;
};

BigInt Add(const BigInt& a, const BigInt& b);

#endif // BIGINT_H_