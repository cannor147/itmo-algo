#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;

class oriental_graph {

private:
    class edge {
    private:
        size_t index;
        int weight;
    public:
        edge() {
            index = 0;
            weight = 0;
        }
        explicit edge(size_t i, int w = 0) {
            index = i;
            weight = w;
        }
        size_t get_index() {
            return index;
        }
        int get_weight() {
            return weight;
        }
    };
    vector<vector<edge>> matrix;

    bool dfs_ts(size_t i, vector<size_t> &colors, vector<size_t> &result) {
        bool f = true;
        if (colors[i] == 0) {
            colors[i]++;
            for (edge &e : matrix[i]) {
                f &= dfs_ts(e.get_index(), colors, result);
            }
            colors[i]++;
            result.push_back(i);
        } else if (colors[i] == 1) {
            f = false;
        }
        return f;
    }
    void dfs_c1(size_t i, vector<size_t> &colors, vector<size_t> &order) {
        if (colors[i]) return;
        colors[i] = 1;
        for (edge &e : matrix[i]) {
            dfs_c1(e.get_index(), colors, order);
        }
        order.push_back(i);
    }
    void dfs_c2(size_t i, vector<size_t> &colors, vector<size_t> &scc) {
        if (colors[i]) return;
        colors[i] = 1;
        scc.push_back(i);
        for (edge &e : matrix[i]) {
            dfs_c2(e.get_index(), colors, scc);
        }
    }
    bool dfs_cycl(size_t i, vector<size_t> &colors, stack<size_t> &st) {
        bool f = true;
        if (colors[i] == 0) {
            colors[i]++;
            st.push(i);
            for (edge &e : matrix[i]) {
                f &= dfs_cycl(e.get_index(), colors, st);
                if (!f) return false;
            }
            st.pop();
            colors[i]++;
        } else if (colors[i] == 1) {
            st.push(i);
            f = false;
        }
        return f;
    }
    size_t dfs_odd(size_t i, vector<size_t> &ans_odd, vector<size_t> &ans_even) {
        if (ans_odd[i] == 2) {
            ans_odd[i] = 1;
            if (matrix[i].empty()) ans_odd[i] = 0;
            for (auto &e : matrix[i]) {
                ans_odd[i] &= dfs_even(e.get_index(), ans_odd, ans_even);
            }
        }
        return ans_odd[i];
    }
    size_t dfs_even(size_t i, vector<size_t> &ans_odd, vector<size_t> &ans_even) {
        if (ans_even[i] == 2) {
            ans_even[i] = 1;
            for (auto &e : matrix[i]) {
                ans_even[i] &= dfs_odd(e.get_index(), ans_odd, ans_even);
            }
        }
        return ans_even[i];
    }
    void dfs_fl(size_t i, vector<size_t> &colors, int &value) {
        if (colors[i] == 0) {
            colors[i] = 1;
            for (auto &e : matrix[i]) {
                if (e.get_weight() <= value) {
                    dfs_fl(e.get_index(), colors, value);
                }
            }
        }
    }

public:
    oriental_graph() {
        matrix = vector<vector<edge>>();
    }
    explicit oriental_graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
    }
    size_t size() {
        return matrix.size();
    }
    void add_edge(size_t i, size_t j, int w = 0) {
        matrix[i].emplace_back(j, w);
    }
    void add_vertex() {
        matrix.emplace_back();
    }

    vector<size_t> top_sort() {
        vector<size_t> colors(size(), 0);
        vector<size_t> result;
        bool f = true;
        for (size_t d = 0; d < size(); d++) {
            f &= dfs_ts(d, colors, result);
        }
        if (!f) {
            result.clear();
        } else {
            std::reverse(result.begin(), result.end());
        }
        return result;
    }
    oriental_graph transpose() {
        oriental_graph result(size());
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < matrix[i].size(); j++) {
                result.add_edge(matrix[i][j].get_index(), i, matrix[i][j].get_weight());
            }
        }
        return result;
    }
    vector<size_t> get_condensation(size_t &k) {
        vector<size_t> colors(size(), 0), order, result(size());
        for (size_t i = 0; i < size(); i++) {
            dfs_c1(i, colors, order);
        }
        colors = vector<size_t>(size(), 0);
        oriental_graph trans = transpose();
        for (size_t i = 0; i < size(); i++) {
            vector<size_t> scc;
            trans.dfs_c2(order[size() - i - 1], colors, scc);
            for (size_t j = 0; j < scc.size(); j++) {
                result[scc[j]] = k;
            }
            if (scc.size() > 0) k++;
            scc.clear();
        }
        return result;
    }
    long long get_path(size_t i, size_t j) {
        vector<long long> dw(size(), INT32_MAX);
        dw[i] = 0;

        vector<size_t> ts = top_sort();
        size_t d;
        for (d = 0; d < size(); d++) {
            if (ts[d] == i) break;
        }
        for (; d < size(); d++) {
            for (auto r : matrix[ts[d]]) {
                dw[r.get_index()] = min(dw[r.get_index()], dw[ts[d]] + r.get_weight());
            }
        }
        return dw[j];
    }
    vector<size_t> cycle() {
        vector<size_t> colors(size(), 0), result;
        stack<size_t> st;
        for (size_t i = 0; i < size(); i++) {
            bool f = dfs_cycl(i, colors, st);
            if (!f) {
                result.push_back(st.top());
                st.pop();
                while (st.top() != result[0]) {
                    result.push_back(st.top());
                    st.pop();
                }
                std::reverse(result.begin(), result.end());
                break;
            }
        }
        return result;
    }
    bool odd_path(size_t i) {
        size_t result = 0;
        vector<size_t> ans_even(size(), 2), ans_odd(size(), 2);
        for (auto &e : matrix[i]) {
            result |= dfs_even(e.get_index(), ans_odd, ans_even);
        }
        return result != 0;
    }
    bool is_full(int value) {
        vector<size_t> colors(size(), 0);
        dfs_fl(0, colors, value);
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) return false;
        }
        return true;
    }
};

int main() {
    size_t n;
    cin >> n;
    oriental_graph g(n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            size_t x;
            cin >> x;
            if (i == j) continue;
            g.add_edge(i, j, x);
        }
    }
    auto trans = g.transpose();
    int l = - 1, r = 1000000000;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (g.is_full(m) && trans.is_full(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    int l = - 1, r = 1000000000;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (g.is_full(m) && trans.is_full(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
    return 0;
}