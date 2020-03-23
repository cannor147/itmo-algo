#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
typedef long long int64;

class Segment_tree {

private:
    struct Node {
        long long min, max, sum;

        Node() {
            this->min = INT64_MAX;
            this->max = INT64_MIN;
            this->sum = 0;
        }

        Node(int value) {
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
    void change(int index, int64 value) {
        tree[index += size] = Node(value);
        for (index /= 2; index >= 1; index /= 2) update(index);
    }
    int64 get_min(int left, int right) {
        int64 result = INT32_MAX;
        for (left += size, right += size; left <= right; left /= 2, right /= 2) {
            if (left % 2 == 1) result = min(result, tree[left++].min);
            if (right % 2 == 0) result = min(result, tree[right--].min);
        }
        return result;
    }
    int64 get_max(int left, int right) {
        int64 result = INT64_MIN;
        for (left += size, right += size; left <= right; left /= 2, right /= 2) {
            if (left % 2 == 1) result = max(result, tree[left++].max);
            if (right % 2 == 0) result = max(result, tree[right--].max);
        }
        return result;
    }
    int64 get_sum(int left, int right) {
        int64 result = 0;
        for (left += size, right += size; left <= right; left /= 2, right /= 2) {
            if (left % 2 == 1) result += tree[left++].sum;
            if (right % 2 == 0) result += tree[right--].sum;
        }
        return result;
    }
};

int main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
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
        if (word == "set") tree.change((int)a - 1, b);
        if (word == "min") cout << tree.get_min((int)a - 1, (int)b - 1) << endl;
    }
}