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
    Binary_tree() {
        nodes.emplace_back(0);
    }
    int size() {
        return nodes.size();
    }
    int add_node(int number) {
        nodes[number - 1].children.push_back(size());
        nodes.emplace_back(size());
    }
    void count_arr(vector<P> *arr, int number, int depth) {
        arr->emplace_back(number + 1, depth);
        for (int &i : nodes[number].children) {
            count_arr(arr, i, depth + 1);
            arr->emplace_back(number + 1, depth);
        }
    }
};

int main() {
    freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int k;
    cin >> k;
    vector<pair<int, int>> queries;
    Binary_tree bin_tree;
    string word;
    while (cin >> word) {
        int a, b;
        cin >> a >> b;
        if (word == "ADD") bin_tree.add_node(a);
        if (word == "GET") queries.emplace_back(a, b);
    }
    vector<P> arr;
    bin_tree.count_arr(&arr, 0, 0);
    int s = bin_tree.size();
    vector<pair<int, int>> pos(s + 1, make_pair(-1, -1));
    for (int i = 0; i < arr.size(); i++) {
        P &c = arr[i];
        if (pos[c.index].first == -1) pos[c.index].first = i;
        pos[c.index].second = i;
    }
    Segment_tree tree(arr);
    for (int j = 0; j < queries.size(); j++) {
        int l = min(pos[queries[j].first].first, pos[queries[j].second].first);
        int r = max(pos[queries[j].first].second, pos[queries[j].second].second);
        P ans = tree.get_min(1, 0, tree.get_size() - 1, l, r);
        cout << ans.index << endl;
    }
}