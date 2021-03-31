#include <iostream>
#include <string>

#include "BigInt.h"

int main()
{
    BigInt next { "1" }, curr { "1" }, prev { "0" };

    for (int i = 2; i <= 100; ++i) {
        next = Add(curr, prev);
        prev = curr;
        curr = next;

        std::cout << next << std::endl;
    }
}