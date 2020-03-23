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
    void dfs_vcc(size_t i, int q, vector<size_t> &colors,
                 vector<size_t> &a, vector<size_t> &b, vector<size_t> &result, size_t &k, size_t t) {
        colors[i]++;
        for (auto &e : matrix[i]) {
            if (e.get_weight() == q) continue;
            if (colors[e.get_index()] == 0) {
                if (a[e.get_index()] >= b[i]) {
                    k++;
                    result[e.get_weight()] = k - 1;
                    dfs_vcc(e.get_index(), e.get_weight(), colors, a, b, result, k, k);
                } else {
                    result[e.get_weight()] = t - 1;
                    dfs_vcc(e.get_index(), e.get_weight(), colors, a, b, result, k, t);
                }
            } else {
                if (b[e.get_index()] < b[i]) {
                    result[e.get_weight()] = t - 1;
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
    size_t number_of_edges() {
        size_t result = 0;
        for (size_t i = 0; i < size(); i++) {
            result += matrix[i].size();
        }
        return result / 2;
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
    set<int> bridges(vector<size_t> &a, vector<size_t> &b) {
        a.resize(size(), 0);
        b.resize(size(), 0);
        vector<size_t> colors(size(), 0);
        set<int> result;
        size_t t = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                dfs_br(i, -1, colors, a, b, result, t);
            }
        }
        return result;
    }
    set<int> cutvertex(vector<size_t> &a, vector<size_t> &b) {
        a.resize(size(), 0);
        b.resize(size(), 0);
        vector<size_t> colors(size(), 0);
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
        vector<size_t> colors(size(), 0), result(size(), 0), a, b;
        set<int> br = bridges(a, b);
        k = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                k++;
                dfs_ecc(i, colors, br, result, k, k);
            }
        }
        return result;
    }
    vector<size_t> get_vertex_comp(size_t &k) {
        vector<size_t> colors(size(), 0), result(number_of_edges(), 0), a, b;
        set<int> cv = cutvertex(a, b);
        k = 0;
        for (size_t i = 0; i < size(); i++) {
            if (colors[i] == 0) {
                dfs_vcc(i, -1, colors, a, b, result, k, k);
            }
        }
        return result;
    }
    void write_edges() {
        cout << number_of_edges() << endl;
        set<pair<size_t, size_t>> tmp;
        for (auto &e : edges) {
            if (tmp.count({e.first, e.second}) == 0) {
                cout << e.first + 1 << " " << e.second + 1 << endl;
                tmp.insert({e.first, e.second});
                tmp.insert({e.second, e.first});
            }
        }
    }
};

int main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);

    size_t n, m;
    cin >> n >> m;
    graph g(n);
    vector<size_t> a(m), first(n, 0), last(n, 0);
    for (size_t i = 0; i < m; i++) {
        cin >> a[i];
        a[i]--;
        last[a[i]] = i;
    }
    vector<size_t> stack;
    for (size_t i = 0; i < m; i++) {
        if (first[a[i]] == 0) {
            first[a[i]] = 1;
            stack.push_back(a[i]);
        }
        if (last[a[i]] == i) {
            for (size_t j = 0; j < stack.size() - 1; j++) {
                if (a[i] > stack[j + 1]) {
                    g.add_edge(a[i], stack[j]);
                }
            }
            stack.pop_back();
            if (stack.size() > 0) {
                g.add_edge(a[i], stack.back());
            }
        }
    }
    g.write_edges();
    return 0;
}