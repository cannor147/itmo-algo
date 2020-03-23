
/*
 * todo: make normal version of HLD
 */

#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;

struct P {
    int index, depth;
    P() {
        this->depth = INT32_MAX;
        this->index = 0;
    }
    P(int index, int depth) {
        this->index = index;
        this->depth = depth;
    }
};
P min(const P &first, const P &second) {
    if (first.depth < second.depth) {
        return first;
    } else {
        return second;
    }
}

class Segment_tree {

private:
    struct Node {
        P min;

        Node() {
            this->min = P();
        }

        Node(P value) {
            this->min = value;
        }
    };
    int size;
    vector<Node> tree;
    void update(int index) {
        tree[index].min = min(tree[2 * index].min, tree[2 * index + 1].min);
    }

public:
    Segment_tree(vector<P> &arr) {
        int n = arr.size();
        size = 1 << (((int) log2(n)) + (((n & (n - 1)) == 0) ? 0 : 1));
        tree.resize(2 * size, Node());
        for (int i = 0; i < n; i++) tree[size + i] = Node(arr[i]);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    int get_size() {
        return size;
    }
    P get_min(const int i, const int lb, const int rb, const int l, const int r) {
        if (l > r) return P();
        if (l == lb && r == rb) return tree[i].min;
        int mid = (lb + rb + 1) / 2;
        return min(get_min(i * 2, lb, mid - 1, l, min(r, mid - 1)), get_min(i * 2 + 1, mid, rb, max(l, mid), r));
    }
};
class My_tree {

private:
    struct Node {
        int number;
        vector<int> children;
        Node() {
            this->number = 0;
        }
        Node(int number) {
            this->number = number;
        }
    };
    vector<bool> visited;
    vector<Node> nodes;
    vector<int> depth, parent;
    vector<map<int, int>> g;
    vector<vector<int>> minimum;
    vector<vector<int>> dp;
    vector<bool> to_binary(int k) {
        vector<bool> res(0);
        while (k > 0) {
            res.push_back((bool)(k % 2));
            k /= 2;
        }
        return res;
    }
    void dfs(int v, int p, int d) {
        if (visited[v]) {
            return;
        }
        visited[v] = true;
        parent[v] = p;
        depth[v] = d;
        for (auto x : g[v]) {
            int to = x.first;
            dfs(to, v, d + 1);
        }
    }
    void precalc(int size, int log_size) {
        for (int jump = 0; jump < log_size; jump++) {
            for (int v = 0; v < size; v++) {
                if (jump == 0) {
                    dp[v][jump] = parent[v];
                    minimum[v][jump] = g[parent[v]][v];
                }
                else {
                    dp[v][jump] = dp[dp[v][jump - 1]][jump - 1];
                    minimum[v][jump] = min(minimum[v][jump - 1], minimum[dp[v][jump - 1]][jump - 1]);
                }
            }
        }
    }

public:
    My_tree(int size) {
        nodes.resize(size);
        visited.resize(size, false);
        depth.resize(size);
        parent.resize(size);
        g.resize(size);
        int log_size = (int)log2(size) + 1;
        minimum.resize(size, vector<int>(log_size, INT32_MAX));
        dp.resize(size, vector<int>(log_size, 0));
    }
    int size() {
        return nodes.size();
    }
    int add_node(int parent, int index, int cost) {
        nodes[parent].children.push_back(index);
        g[parent][index] = cost;
    }
    void count_arr(vector<P> *arr, int number, int depth) {
        arr->emplace_back(number, depth);
        for (int &i : nodes[number].children) {
            count_arr(arr, i, depth + 1);
            arr->emplace_back(number, depth);
        }
    }
    void calculate() {
        dfs(0, 0, 0);
        precalc(minimum.size(), minimum[0].size());
    }
    int get_min(int u, int v, int lca) {
        auto jumps_v = to_binary(depth[v] - depth[lca]);
        auto jumps_u = to_binary(depth[u] - depth[lca]);
        int ans = INT32_MAX;
        for (int i = 0; i < jumps_u.size(); i++) {
            if (jumps_u[i]) {
                ans = min(ans, minimum[u][i]);
                u = dp[u][i];
            }
        }
        for (int i = 0; i < jumps_v.size(); i++) {
            if (jumps_v[i]) {
                ans = min(ans, minimum[v][i]);
                v = dp[v][i];
            }
        }
        return ans;
    }
};

int main() {
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n;
    My_tree tree1(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        tree1.add_node(a - 1, i, b);
    }
    vector<P> arr;
    tree1.count_arr(&arr, 0, 0);
    vector<pair<int, int>> pos(n, make_pair(-1, -1));
    for (int i = 0; i < arr.size(); i++) {
        P &c = arr[i];
        if (pos[c.index].first == -1) pos[c.index].first = i;
        pos[c.index].second = i;
    }
    Segment_tree tree(arr);
    cin >> m;
    tree1.calculate();
    for (int j = 0; j < m; j++) {
        int q1, q2;
        cin >> q1 >> q2;
        int l = min(pos[q1 - 1].first, pos[q2 - 1].first);
        int r = max(pos[q1 - 1].second, pos[q2 - 1].second);
        int lca = tree.get_min(1, 0, tree.get_size() - 1, l, r).index;
        int result = tree1.get_min(q1 - 1, q2 - 1, lca);
        cout << result << endl;
    }
}