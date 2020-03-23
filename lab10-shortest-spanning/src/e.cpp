#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

const long long INF = 5e18 + 1;

class oriental_graph {

private:
    class edge {
    private:
        size_t index;
        long long weight;
    public:
        edge() {
            index = 0;
            weight = 0;
        }
        explicit edge(size_t i, long long w = 0) {
            index = i;
            weight = w;
        }
        size_t get_index() {
            return index;
        }
        long long get_weight() {
            return weight;
        }
    };
    vector<vector<edge>> matrix;
    set<pair<size_t, size_t>> edges;

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
    void dfs_kek(size_t i, vector<long long> &distance) {
        if (distance[i] == -INF - 1) return;
        distance[i] = -INF - 1;
        for (edge &e : matrix[i]) {
            dfs_kek(e.get_index(), distance);
        }
    }

public:
    oriental_graph() {
        matrix = vector<vector<edge>>();
        edges = set<pair<size_t, size_t>>();
    }
    explicit oriental_graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
        edges = set<pair<size_t, size_t>>();
    }
    size_t size() {
        return matrix.size();
    }
    void add_edge(size_t i, size_t j, long long w = 0) {
        matrix[i].emplace_back(j, w);
        edges.emplace(i, j);
    }
    bool is_edge(size_t i, size_t j) {
        return edges.count({i, j}) > 0;
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
                result.add_edge(matrix[i][j].get_index(), i);
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
    bool is_hamiltonian() {
        vector<size_t> ts = top_sort();
        bool f = true;
        for (size_t i = 1; i < size(); i++) {
            f &= is_edge(ts[i - 1], ts[i]);
        }
        return f;
    }

    vector<long long> find_distances(size_t s) {
        vector<long long> distance(size(), INF);
        distance[s] = 0;
        for (size_t i = 0; i < size(); i++) {
            for (size_t j = 0; j < size(); j++) {
                if (distance[j] == INF) continue;
                for (auto &e : matrix[j]) {
                    auto k = e.get_index();
                    auto w = e.get_weight();
                    if (distance[j] == -INF) {
                        distance[k] = -INF;
                    } else {
                        if (distance[k] > distance[j] + w) {
                            if (i + 1 == size()) {
                                dfs_kek(k, distance);
                            } else {
                                distance[k] = max(-INF, distance[j] + w);
                            }
                        }
                    }
                }
            }
        }
        for (size_t i = 0; i < size(); i++) {
            if (distance[i] == -INF) {
                dfs_kek(i, distance);
            }
        }
        return distance;
    }
};

int main() {
    size_t n, m, s;
    cin >> n >> m >> s;
    oriental_graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        long long c;
        cin >> a >> b >> c;
        g.add_edge(a - 1, b - 1, c);
    }
    auto dist = g.find_distances(s - 1);
    for (size_t i = 0; i < dist.size(); i++) {
        if (dist[i] == INF) {
            cout << "*" << endl;
        } else if (dist[i] == -INF - 1) {
            cout << "-" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}