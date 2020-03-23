#include <iostream>

using namespace std;

struct Node {
    int key, prior, order, size;
    Node *left, *right, *parent;
    Node(int x, int y, int z) {
        key = x;
        prior = y;
        order = z + 1;
        size = 1;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

void merge(pair<int, int>  arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 =  r - m;
    pair <int, int> *left = new pair<int, int>[n1];
    pair <int, int> *right = new pair<int, int>[n2];
    for (int i = 0; i < n1; i++) left[i] = arr[l + i];
    for (int i = 0; i < n2; i++) right[i] = arr[m + i + 1];
    int i = 0, j = 0, k = l;
    while ((i < n1) && (j < n2)){
        if (left[i].first >= right[j].first){
            arr[k] = left[i];
            i++;
        } else if (true) {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
    delete [] left;
    delete [] right;
}

void mergeSort(pair<int, int> arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

const int s = 300001;
pair<int, int> a[s];
Node *nodes[s];

Node* insertInTreap(Node *n, int key, int prior, int num) {
    Node *m = new Node(key, prior, num);
    nodes[num] = m;
    if (num == 0) {
        return m;
    } else if (num > 0) {
        Node *k = nodes[num - 1];
        while ((k != n) && (k->prior < prior)) {
            k = k->parent;
        }
        if (k == n) {

        } else if (k != n) {

        }
        m->left = k->right;
        k->right = m;
        m->parent = k;
        if (m->parent == NULL) return m;
    }
    return n;
}

void writeInTreap(Node *n) {
    int p_res = (n->parent != NULL) ? (n->parent)->order : 0;
    int l_res = (n->left != NULL) ? (n->left)->order : 0;
    int r_res = (n->right != NULL) ? (n->right)->order : 0;
    cout << p_res << " " << l_res << " " << r_res << endl;
}

int main() {
    Node *root = NULL;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < n; i++) root = insertInTreap(root, i, a[i].second, i);
    for (int i = 0; i < n; i++) writeInTreap(nodes[i]);
}