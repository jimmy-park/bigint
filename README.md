# BigInt

Simple Implementation of Big Integer in C++

# Usage

```cpp
#include "BigInt.h"

int main()
{
    auto fibo = [](int n) -> BigInt {
        if (n == 0)
            return "0";

        BigInt next { "1" }, curr { "1" }, prev { "0" };

        for (int i = 2; i <= n; ++i) {
            next = Add(curr, prev);
            prev = curr;
            curr = next;
        }

        return next;
    };

    // Print 100th fibonacci number (354224848179261915075)
    // which exceeds std::uint64_t range
    std::cout << fibo(100);
}
```

Run code in browser : <https://godbolt.org/z/caPKEqc5h>
