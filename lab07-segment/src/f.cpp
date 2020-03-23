#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
int rr = 0;

struct Matrix {
    int a11, a12, a21, a22;
    Matrix() {
        a11 = a22 = 1;
        a21 = a12 = 0;
    }
    void write() const {
        printf("%d %d\n%d %d\n\n", a11, a12, a21, a22);
    }
};
Matrix operator*(Matrix const &first, Matrix const &second) {
    Matrix result;
    result.a11 = (first.a11 * second.a11 + first.a12 * second.a21) % rr;
    result.a12 = (first.a11 * second.a12 + first.a12 * second.a22) % rr;
    result.a21 = (first.a21 * second.a11 + first.a22 * second.a21) % rr;
    result.a22 = (first.a21 * second.a12 + first.a22 * second.a22) % rr;
    return result;
}

class Segment_tree {

private:
    struct Node {
        Matrix mul;
        Node() {
            this->mul = Matrix();
        }
        Node(Matrix value) {
            this->mul = value;
        }
    };
    int size;
    vector<Node> tree;
    void update(int index) {
        tree[index].mul = tree[2 * index].mul * tree[2 * index + 1].mul;
    }

public:
    Segment_tree(vector<Matrix> &arr) {
        int n = arr.size();
        size = 1 << (((int) log2(n)) + (((n & (n - 1)) == 0) ? 0 : 1));
        tree.resize(2 * size, Node());
        for (int i = 0; i < n; i++) tree[size + i] = Node(arr[i]);
        for (int i = size - 1; i >= 1; i--) update(i);
    }
    int get_size() {
        return size;
    }
    Matrix get_mul(const int &i, const int &lb, const int &rb, const int &l, const int &r) {
        if (l > r) return Matrix();
        if (l == lb && r == rb) return tree[i].mul;
        int mid = (lb + rb + 1) / 2;
        return get_mul(i * 2, lb, mid - 1, l, min(r, mid - 1)) * get_mul(i * 2 + 1, mid, rb, max(l, mid), r);
    }
};

int main() {
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);

    int n, m;
    vector<Matrix> arr;
    scanf("%d %d %d", &rr, &n, &m);
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &(arr[i].a11), &(arr[i].a12), &(arr[i].a21), &(arr[i].a22));
    }
    Segment_tree tree(arr);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree.get_mul(1, 0, tree.get_size() - 1, a - 1, b - 1).write();
    }
}