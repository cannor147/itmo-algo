#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long int64;

class Segment_tree {

private:
    struct Node {
        int64 min, max, sum;

        Node() {
            this->min = INT64_MAX;
            this->max = INT64_MIN;
            this->sum = 0;
        }

        Node(int64 value) {
            this->min = value;
            this->max = value;
            this->sum = value;
        }
    };
    int size;
    vector<Node> tree;
    void update(int index) {
        tree[index].min = min(tree[2 * index].min, tree[2 * index + 1].min);
        tree[index].max = max(tree[2 * index].max, tree[2 * index + 1].max);
        tree[index].sum = tree[2 * index].sum + tree[2 * index + 1].sum;
    }

public:
    Segment_tree(vector<int64> &arr) {
        int n = arr.size();
        size = 1 << (((int) log2(n)) + (((n & (n - 1)) == 0) ? 0 : 1));
        tree.resize(2 * size, Node());
        for (int i = 0; i < n; i++) tree[size + i] = Node(arr[i]);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    void change(int64 index, int64 value) {
        int i = (int)index + size;
        tree[i] = Node(value);
        for (i /= 2; i >= 1; i /= 2) update(i);
    }
    int64 get_min(int64 left, int64 right) {
        int l = (int)left, r = (int)right;
        int64 result = INT64_MAX;
        for (l += size, r += size; l <= r; l /= 2, r /= 2) {
            if (l % 2 == 1) result = min(result, tree[l++].min);
            if (r % 2 == 0) result = min(result, tree[r--].min);
        }
        return result;
    }
    int64 get_max(int64 left, int64 right) {
        int l = (int)left, r = (int)right;
        int64 result = INT32_MIN;
        for (l += size, r += size; l <= right; l /= 2, r /= 2) {
            if (l % 2 == 1) result = max(result, tree[l++].max);
            if (r % 2 == 0) result = max(result, tree[r--].max);
        }
        return result;
    }
    int64 get_sum(int64 left, int64 right) {
        int l = (int)left, r = (int)right;
        int64 result = INT32_MAX;
        for (l += size, r += size; l <= right; l /= 2, r /= 2) {
            if (l % 2 == 1) result += tree[l++].sum;
            if (r % 2 == 0) result += tree[r--].sum;
        }
        return result;
    }
    int64 get(int64 index) {
        int i = (int)index;
        return tree[size + i].min;
    }
    void write() {
        for (int i = 0; i < tree.size(); i++) {
            cout << tree[i].min << " ";
        }
        cout << endl;
    }
};

int main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    vector<int64> arr;
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; cin >> arr[i++]);
    Segment_tree tree(arr);
    string word;
    while (cin >> word) {
        int64 a, b;
        cin >> a >> b;
        if (word == "set") tree.change(a - 1, b);
        if (word == "sum") cout << tree.get_sum(a - 1, b - 1) << endl;
    }
}