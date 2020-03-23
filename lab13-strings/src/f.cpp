#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

namespace my_min_max {

    size_t max(size_t x, size_t y) {
        return (x < y) ? y : x;
    }
    size_t min(size_t x, size_t y) {
        return (x < y) ? x : y;
    }
}

vector<size_t> prefix_function(const string &s) {
    vector<size_t> p(s.length(), 0);
    for (size_t i = 1; i < s.length(); i++) {
        p[i] = p[i - 1];
        while (p[i] > 0 && s[i] != s[p[i]]) {
            p[i] = p[p[i] - 1];
        }
        if (s[i] == s[p[i]]) p[i]++;
    }
    return p;
}

vector<size_t> z_function(const string &s) {
    size_t last = 0, bound = 0;
    vector<size_t> z(s.length(), 0);
    for (size_t i = 1; i < s.length(); i++) {
        if (i < bound) z[i] = my_min_max::max(0, my_min_max::min(z[i - last], bound - i));
        while (i + z[i] < s.length() && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > bound) {
            last = i;
            bound = i + z[i];
        }
    }
    z[0] = s.length();
    return z;
}

int main() {
    string c;
    cin >> c;
    auto z = z_function(c);
    for (size_t i = 1; i < z.size(); i++) {
        if (z.size() % i != 0) continue;
        size_t v = z.size() / i;
        if (z[i] == (v - 1) * i) {
            cout << i;
            return 0;
        }
    }
    cout << z.size();
    return 0;
}