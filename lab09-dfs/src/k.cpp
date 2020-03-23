#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class graph {

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
    set<pair<size_t, size_t>> edges;

    void dfs_cc(size_t i, vector<size_t> &colors, vector<size_t> &cc) {
        if (colors[i] == 0) {
            colors[i]++;
            cc.push_back(i);
            if (matrix[i].empty()) return;
            for (auto &e : matrix[i]) {
                dfs_cc(e.get_index(), colors, cc);
            }
        }
    }
    void dfs_br(size_t i, int q, vector<size_t> &colors, vector<size_t> &a, vector<size_t> &b, set<int> &result, size_t &t) {
        colors[i]++;
        a[i] = b[i] = t++;
        for (auto &e : matrix[i]) {
            if (e.get_weight() == q) continue;
            if (colors[e.get_index()] == 1) {
                a[i] = min(a[i], b[e.get_index()]);
            } else {
                dfs_br(e.get_index(), e.get_weight(), colors, a, b, result, t);
                a[i] = min(a[i], a[e.get_index()]);
                if (a[e.get_index()] > b[i]) {
                    result.insert(e.get_weight());
                }
            }
        }
    }
    void dfs_cv(size_t i, int q, vector<size_t> &colors, vector<size_t> &a, vector<size_t> &b, set<int> &result, size_t &t) {
        colors[i]++;
        size_t count = 0;
        a[i] = b[i] = t++;
        for (auto &e : matrix[i]) {
            if (e.get_weight() == q) continue;
            if (colors[e.get_index()] == 1) {
                a[i] = min(a[i], b[e.get_index()]);
            } else {
                dfs_cv(e.get_index(), e.get_weight(), colors, a, b, result, t);
                a[i] = min(a[i], a[e.get_index()]);
                if (a[e.get_index()] >= b[i] && q != -1) {
                    result.insert(i);
                }
                count++;
            }
        }
        if (count > 1 && q == -1) {
            result.insert(i);
        }
    }
    bool dfs_bi(size_t i, int color, vector<int> &colors) {
        if (colors[i] == 0) {
            colors[i] = color;
            bool f = true;
            for (auto &e : matrix[i]) {
                f &= dfs_bi(e.get_index(), color - 2 * color, colors);
                if (!f) break;
            }
            return f;
        } else {
            return colors[i] == color;
        }
    }
    void dfs_ecc(size_t i, vector<size_t> &colors, set<int> &br, vector<size_t> &result, size_t &k, size_t t) {
        colors[i]++;
        result[i] = t - 1;
        for (auto &e: matrix[i]) {
            if (colors[e.get_index()] == 0) {
                if (br.count(e.get_weight()) > 0) {
                    k++;
                    dfs_ecc(e.get_index(), colors, br, result, k, k);
                } else {
                    dfs_ecc(e.get_index(), colors, br, result, k, t);
                }
            }
        }
    }

public:
    graph() {
        matrix = vector<vector<edge>>();
        edges = set<pair<size_t, size_t>>();
    }
    explicit graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
        edges = set<pair<size_t, size_t>>();
    }
    size_t size() {
        return matrix.size();
    }
    bool is_edge(size_t i, size_t j) {
        return edges.count({i, j}) > 0;
    }
    void add_edge(size_t i, size_t j, size_t w = 0) {
        matrix[i].emplace_back(j, w);
        matrix[j].emplace_back(i, w);
        edges.emplace(i, j);
        edges.emplace(j, i);
    }
    void add_vertex() {
        matrix.emplace_back();
    }

    vector<size_t> get_components(size_t &k) {
        vector<size_t> colors(size(), 0), result(size());
        k = 0;
        for (size_t i = 0; i < size(); i++) {
            vector<size_t> cc;
            dfs_cc(i, colors, cc);
            for (size_t j = 0; j < cc.size(); j++) {
                result[cc[j]] = k;
            }
            if (!cc.empty()) k++;
            cc.clear();
        }
        return result;
    }
    set<int> bridges() {
        vector<size_t> colors(size(), 0), a(size(), 0), b(size(), 0);
        set<int> result;
        size_t t = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                dfs_br(i, -1, colors, a, b, result, t);
            }
        }
        return result;
    }
    set<int> cutvertex() {
        vector<size_t> colors(size(), 0), a(size(), 0), b(size(), 0);
        set<int> result;
        size_t t = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                dfs_cv(i, -1, colors, a, b, result, t);
            }
        }
        return result;
    }
    bool is_bipartite() {
        vector<int> colors(size(), 0);
        bool result = true;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                result &= dfs_bi(i, 1, colors);
            }
        }
        return result;
    }
    vector<size_t> get_edge_comp(size_t &k) {
        vector<size_t> colors(size(), 0), result(size(), 0);
        set<int> br = bridges();
        k = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                k++;
                dfs_ecc(i, colors, br, result, k, k);
            }
        }
        return result;
    }
};

int main() {
    freopen("bicone.in", "r", stdin);
    freopen("bicone.out", "w", stdout);

    size_t n, m;
    cin >> n >> m;
    graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1, i);
    }
    size_t k = 0;
    vector<size_t> ecc = g.get_edge_comp(k);
    cout << k << endl;
    for (size_t i = 0; i < ecc.size(); i++) {
        cout << ecc[i] + 1 << " ";
    }
    return 0;
}