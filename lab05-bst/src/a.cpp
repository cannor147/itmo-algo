#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int x)	{
        key = x;
        left = NULL;
        right = NULL;
    }
};

Node* insertInBST(Node *n, int x) {
    if (n == NULL) {
        return new Node(x);
    }
    if (n->key > x) {
        n->left = insertInBST(n->left, x);
    } else if (n->key < x) {
        n->right = insertInBST(n->right, x);
    }
    return n;
}

Node* minInBST(Node *n) {
    if (n->left == NULL) return n;
    return minInBST(n->left);
}

Node* maxInBST(Node *n) {
    if (n->right == NULL) return n;
    return maxInBST(n->right);
}

Node* deleteInBST(Node *n, int x) {
    if (n == NULL) return NULL;
    if (n->key == x) {
        if ((n->left != NULL) && (n->right != NULL)) {
            n->key = (minInBST(n->right))->key;
            n->right = deleteInBST(n->right, n->key);
        } else if (n->left != NULL) {
            n = n->left;
        } else if (n->right != NULL) {
            n = n->right;
        } else if (true) {
            n = NULL;
        }
    } else if (n->key > x) {
        n->left = deleteInBST(n->left, x);
    } else if (n->key < x) {
        n->right = deleteInBST(n->right, x);
    }
    return n;
}

Node* searchInBST(Node *n, int x) {
    if (n == NULL) return NULL;
    if (n->key == x) return n;
    if (n->key > x) {
        return searchInBST(n->left, x);
    } else if (n->key < x) {
        return searchInBST(n->right, x);
    }
}

Node* nextInBST(Node *n, int x) {
    Node *i = n;
    Node *j = NULL;
    while (i != NULL) {
        if (i->key > x) {
            j = i;
            i = i->left;
        } else if (true) {
            i = i->right;
        }
    }
    return j;
}

Node* prevInBST(Node *n, int x) {
    Node *i = n;
    Node *j = NULL;
    while (i != NULL) {
        if (i->key < x) {
            j = i;
            i = i->right;
        } else if (true) {
            i = i->left;
        }
    }
    return j;
}

int main() {
    Node *root = NULL;
    string action;
    int x;
    while (cin >> action) {
        cin >> x;
        if (action == "insert") {
            root = insertInBST(root, x);
        } else if (action == "delete") {
            root = deleteInBST(root, x);
        } else if (action == "exists") {
            if (searchInBST(root, x) != NULL) {
                cout << "true" << endl;
            } else if (true) {
                cout << "false" << endl;
            }
        } else if (action == "next") {
            Node *m = nextInBST(root, x);
            if (m != NULL) {
                cout << m->key << endl;
            } else if (true) {
                cout << "none" << endl;
            }
        } else if (action == "prev") {
            Node *m = prevInBST(root, x);
            if (m != NULL) {
                cout << m->key << endl;
            } else if (true) {
                cout << "none" << endl;
            }
        }
    }
}