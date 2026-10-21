#include <iostream>
#include <vector>
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
class Sparse_table {

private:
    vector<vector<P>> table;

public:
    Sparse_table(vector<P> &arr) {
        int s = arr.size();
        table.resize(s, vector<P>((int)log2(s) + 1, P()));
        for (int j = 0; (1 << j) <= s; j++) {
            for (int i = 0; i + (1 << j) <= s; i++) {
                if (j == 0) {
                    table[i][j] = arr[i];
                } else {
                    table[i][j] = min(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
                }
            }
        }
    }
    P get_min(int l, int r) {
        int j = 0;
        while ((1 << j + 1) <= r - l + 1) {
            j++;
        }
        return min(table[l][j], table[r - (1 << j) + 1][j]);
    }
};
class Binary_tree {

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
    vector<Node> nodes;

public:
    Binary_tree(int n) {
        for (int i = 0; i < n; i++) {
            nodes.emplace_back(i);
        }
    }
    int size() {
        return nodes.size();
    }
    void add_node(int parent, int number) {
        nodes[parent].children.push_back(number);
    }
    void count_arr(vector<P> *arr, int number, int depth) {
        vector<pair<int, int>> stack{{number, 0}};
        while (!stack.empty()) {
            int v = stack.back().first;
            int &child = stack.back().second;
            if (child == 0) arr->emplace_back(v, depth + stack.size() - 1);
            if (child < nodes[v].children.size()) {
                int next = nodes[v].children[child++];
                stack.emplace_back(next, 0);
            } else {
                stack.pop_back();
                if (!stack.empty()) arr->emplace_back(stack.back().first, depth + stack.size() - 1);
            }
        }
    }
};

int main() {
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Binary_tree bin_tree(n);
    string word;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        bin_tree.add_node(p, i);
    }
    vector<P> arr;
    bin_tree.count_arr(&arr, 0, 0);
    int s = bin_tree.size();
    vector<pair<int, int>> pos(s, make_pair(-1, -1));
    for (int i = 0; i < arr.size(); i++) {
        P &c = arr[i];
        if (pos[c.index].first == -1) pos[c.index].first = i;
        pos[c.index].second = i;
    }

    int x, y, z;
    int a1, a2;
    cin >> a1 >> a2 >> x >> y >> z;

    Sparse_table table(arr);
    P ans;
    long long sum = 0;
    int q1 = a1, q2 = a2;
    for (int j = 1; j <= m; j++) {
        int l = min(pos[q1].first, pos[q2].first);
        int r = max(pos[q1].second, pos[q2].second);
        ans = table.get_min(l, r);
        sum += ans.index;
        if (j == m) break;
        int next_a1 = (1LL * x * a1 + 1LL * y * a2 + z) % n;
        a2 = (1LL * x * a2 + 1LL * y * next_a1 + z) % n;
        a1 = next_a1;
        q1 = (a1 + ans.index) % n;
        q2 = a2;
    }
    cout << sum;
}