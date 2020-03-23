#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

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

vector<size_t> suffix_array(string &s) {
    size_t n = s.length();
    vector<size_t> result(n);
    // n
    for (size_t i = 0; i < n; i++) {
        result[i] = i;
    }
    // nlogn
    std::sort(result.begin(), result.end(), [&](const size_t &s1, const size_t &s2) {
        return s[s1] < s[s2];
    });

    std::vector<size_t> cl(n);
    cl[result[0]] = 0;
    // n
    for (size_t i = 1; i < n; i++) {
        cl[result[i]] = cl[result[i - 1]];
        if (s[result[i]] != s[result[i - 1]]) {
            cl[result[i]]++;
        }
    }
    bool f = true;

    // nlog^2n + nlogn
    for (size_t count = 1; f; count = my_min_max::min(count * 2, n)) {
        //
        std::sort(result.begin(), result.end(), [&] (const size_t &s1, const size_t &s2) {
            if (cl[s1] != cl[s2]) return cl[s1] < cl[s2];
            return cl[(s1 + count) % n] < cl[(s2 + count) % n];
        });

        std::vector<size_t> tmp(n);
        tmp[result[0]] = 0;
        for (size_t i = 1; i < n; i++) {
            tmp[result[i]] = tmp[result[i - 1]];
            if (cl[result[i]] != cl[result[i - 1]]) {
                tmp[result[i]]++;
                continue;
            }
            if (cl[(result[i] + count) % n] != cl[(result[i - 1] + count) % n]) {
                tmp[result[i]]++;
            }
        }
        for (size_t i = 0; i < n; i++) {
            cl[i] = tmp[i];
        }
        tmp.clear();
        f = count < n;
    }
    return result;
}

// summary 2 * 10^7 + 10^6
bool is_substring(string &p, string &t, vector<size_t> &suf) {
//    for (auto x : suf) cout << x << endl;

    size_t l = 0, r = suf.size() - 1, m;
    while (r >= l) {
        m = l + (r - l) / 2;
        bool f = false;
        size_t i;
        for (i = 0; i < p.length() && i < t.length() - suf[m]; i++) {
            if (t[suf[m] + i] < p[i]) f = true;
            if (t[suf[m] + i] > p[i]) f = false;
            if (t[suf[m] + i] != p[i]) {
                i = 0;
                break;
            }
        }
        if (i == t.length() - suf[m]) f = true;
        if (i == p.length()) f = false;
        if (f) {
            l = m + 1;
        } else {
            if (l == r) break;
            r = m;
        }
//        cout << l << " " << m << " " << r << endl;
    }
//    cout << t.substr(suf[l], t.length() - suf[l]) << endl;
    if (l > suf.size() - 1 || p.length() > t.length() - suf[l]) return false;
    for (size_t i = 0; i < p.length(); i++) {
        if (t[suf[l] + i] != p[i]) return false;
    }
    return true;
}

int main() {
    size_t n;
    cin >> n;
    vector<string> str(n);
    for (size_t i = 0; i < n; i++) {
        cin >> str[i];
    }

    string c;
    cin >> c;
    c += "&";
    auto suf = suffix_array(c);

    for (size_t i = 0; i < n; i++) {
        if (is_substring(str[i], c, suf)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}