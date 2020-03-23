#include <iostream>
#include <vector>
#include <set>
#include <queue>

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

    void bfs_sc(vector<size_t> &colors, vector<size_t> &result, queue<size_t> q) {
        while (!q.empty()) {
            auto i = q.front();
            q.pop();
            for (auto &e : matrix[i]) {
                auto j = e.get_index();
                if (colors[j] == 0) {
                    colors[j] = 1;
                    result[j] = result[i] + 1;
                    q.push(j);
                }
            }
        }
    }
    void dijkstra(vector<int> &result, set<pair<int, size_t>> q) {
        for (size_t i = 0; i < size(); i++) {
            size_t j_min = (*q.begin()).second;
            q.erase({result[j_min], j_min});
            if (result[j_min] == INT32_MAX) {
                break;
            }
            for (auto &e : matrix[j_min]) {
                if (result[j_min] + e.get_weight() < result[e.get_index()]) {
                    q.erase({result[e.get_index()], e.get_index()});
                    result[e.get_index()] = result[j_min] + e.get_weight();
                    q.insert({result[e.get_index()], e.get_index()});
                }
            }
        }
    }

public:
    graph() {
        matrix = vector<vector<edge>>();
    }
    explicit graph(size_t n) {
        matrix = vector<vector<edge>>(n, vector<edge>());
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
    void add_edge(size_t i, size_t j, size_t w = 0) {
        matrix[i].emplace_back(j, w);
        matrix[j].emplace_back(i, w);
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

    vector<size_t> shortcuts(size_t i) {
        vector<size_t> colors(size(), 0), result(size());
        queue<size_t> q;
        q.push(i);
        result[i] = 0;
        colors[i] = 1;
        bfs_sc(colors, result, q);
        return result;
    }
    vector<int> shortcuts2(size_t i) {
        vector<int> result(size(), INT32_MAX);
        set<pair<int, size_t>> q;
        result[i] = 0;
        q.insert({0, i});
        dijkstra(result, q);
        return result;
    }
};

int main() {
//    freopen("biconv.in", "r", stdin);
//    freopen("biconv.out", "w", stdout);

    size_t n, m;
    cin >> n >> m;
    graph g(n);
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        int c;
        cin >> a >> b;
        g.add_edge(a - 1, b - 1, 1);
    }
    vector<size_t> sc = g.shortcuts(0);
    for (size_t i = 0; i < sc.size(); i++) {
        cout << sc[i] << " ";
    }
    return 0;
}