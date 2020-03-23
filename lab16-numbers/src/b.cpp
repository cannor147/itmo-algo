#include <iostream>
#include <vector>

const int MAX_NUMBER = 1000000;

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

std::vector<int> get_prime_multipliers(int n) {
    int sqr = 1, odd = 3;
    std::vector<int> result(n + 1, 1);
    result[0] = result[1] = 0;
    for (int i = 2; sqr <= n; ++i) {
        sqr += odd;
        odd += 2;
        if (result[i] == 1) {
            for (int j = sqr; j <= n; j += i) {
                if (result[j] == 1) {
                    result[j] = i;
                }
            }
        }
    }

    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto prime_multipliers = get_prime_multipliers(MAX_NUMBER);
    int n, x;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        while (prime_multipliers[x] != 1) {
            std::cout << prime_multipliers[x] << " ";
            x /= prime_multipliers[x];
        }
        std::cout << x << "\n";
    }
    return 0;
}