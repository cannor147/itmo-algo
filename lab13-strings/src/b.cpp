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
    string p, t;
    cin >> p >> t;
    if (p.length() > t.length()) {
        cout << 0;
        return 0;
    }
    string c = p + t;
    auto z = z_function(c);
    vector<size_t> ans;
    for (size_t i = p.length(); i < z.size(); i++) {
        if (z[i] >= p.length()) ans.push_back(i);
    }
    cout << ans.size() << endl;
    for (auto x : ans) {
        cout << x - p.length() + 1 << " ";
    }
    return 0;
}