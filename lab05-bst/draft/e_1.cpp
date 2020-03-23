#include <iostream>

using namespace std;

struct Node {
    int key, prior, order;
    Node *left, *right, *parent;
    Node(int x, int y, int z) {
        key = x;
        prior = y;
        order = z;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

const int s = 300001;
Node *nodes[s];

Node* mergeTreaps(Node *l, Node *r) {
    if (l == NULL)
        return r;
    if (r == NULL)
        return l;
    Node* res;
    if (l->prior < r->prior) {
        l->right = mergeTreaps(l->right, r);
        res = l;
    } else if (l->prior > r->prior) {
        r->left = mergeTreaps(l, r->left);
        res = r;
    }
    return res;
}

pair <Node*, Node*> splitInTreap(Node *n, int x) {
    if (n == NULL) return make_pair(n, n);
    pair <Node*, Node*> res;
    if (n->key < x) {
        res = splitInTreap(n->right, x);
        n->right = res.first;
        res.first = n;
    } else if (n->key >= x) {
        res = splitInTreap(n->left, x);
        n->left = res.second;
        res.second = n;
    }
    return res;
}

Node* insertInTreap(Node *n, int x, int y, int z) {
    Node *m = new Node(x, y, z + 1);
    nodes[z] = m;
    pair <Node*, Node*> split = splitInTreap(n, x);
    split.first = mergeTreaps(split.first, m);
    return mergeTreaps(split.first, split.second);
}

void writeInTreap(Node *n) {
    int p_res = (n->parent != NULL) ? (n->parent)->order : 0;
    int l_res = (n->left != NULL) ? (n->left)->order : 0;
    int r_res = (n->right != NULL) ? (n->right)->order : 0;
    cout << p_res << " " << l_res << " " << r_res << endl;
}

void typeParents(Node* n)
{
    if (n->left != NULL) {
        (n->left)->parent = n;
        typeParents(n->left);
    }
    if (n->right != NULL) {
        (n->right)->parent = n;
        typeParents(n->right);
    }
}

int main() {
    Node *root = NULL;
    int n;
    int a, b;
    cin >> n;
    for (int i = 0; i < n; i++)	{
        cin >> a >> b;
        root = insertInTreap(root, a, b, i);
    }
    if (true) {
        cout << "YES" << endl;
        typeParents(root);
        for (int i = 0; i < n; i++) writeInTreap(nodes[i]);
    } else if (false) {
        cout << "NO";
    }
    return 0;
}