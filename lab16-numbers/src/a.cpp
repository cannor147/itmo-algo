#include <iostream>
#include <vector>

const int MAX_NUMBER = 20000000;

std::vector<char> get_primes(int n) {
    int sqr = 1, odd = 3;
    std::vector<char> result(n + 1, true);
    result[0] = result[1] = false;
    for (int i = 2; sqr <= n; ++i) {
        sqr += odd;
        odd += 2;
        if (result[i]) {
            for (int j = sqr; j <= n; j += i) {
                result[j] = false;
            }
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto primes = get_primes(MAX_NUMBER);
    int n, x;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        if (primes[x]) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}