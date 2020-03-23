#include <iostream>
#include <cmath>
#include <map>

long long pow(long long a, long long b, long long n) {
    long long result = 1;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % n;
            --b;
        } else {
            a = (a * a) % n;
            b /= 2;
        }
    }
    return result;
}

long long discrete_log(long long a, long long b, long long n) {
    if ((a % n == 0) != (b % n == 0)) {
        return -1;
    }
    if (a == b) {
        return 1;
    }
    std::map<long long, long long> values;

    auto sqrt = static_cast<long long>(std::sqrt(n) + 1);
    for (long long i = sqrt; i >= 1; --i) {
        long long f1 = pow(a, i * sqrt, n);
        values[f1] = i;
    }

    for (long long i = 0; i < sqrt; ++i) {
        long long f2 = (b * pow(a, i, n)) % n;
        if (values.count(f2) > 0) {
            long long ans = sqrt * values[f2] - i;
            if (ans < n) {
                return ans;
            }
        }
    }

    return -1ll;
}

int main() {
    long long a, b, n;
    std::cin >> a >> b >> n;
    auto ans = discrete_log(a, b % n, n);
    std::cout << ans;
}