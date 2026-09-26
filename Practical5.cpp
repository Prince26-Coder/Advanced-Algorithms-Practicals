#include <bits/stdc++.h>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;
    int t; 
    BTreeNode(int t, bool leaf) {
        this->t = t;
        this->leaf = leaf;
    }

    void traverse() {
        int i;
        for (i = 0; i < (int)keys.size(); i++) {
            if (!leaf) children[i]->traverse();
            cout << keys[i] << " ";
        }
        if (!leaf) children[i]->traverse();
    }

    void insertNonFull(int key) {
        int i = keys.size() - 1;

        if (leaf) {
            keys.push_back(0); // make space
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
        } else {
            while (i >= 0 && keys[i] > key) i--;
            i++;

            if ((int)children[i]->keys.size() == 2 * t - 1) {
                splitChild(i, children[i]);
                if (keys[i] < key) i++;
            }
            children[i]->insertNonFull(key);
        }
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->leaf);
        int t = y->t;

        z->keys.assign(y->keys.begin() + t, y->keys.end());

        if (!y->leaf) {
            z->children.assign(y->children.begin() + t, y->children.end());
            y->children.resize(t);
        }

        int midKey = y->keys[t - 1];
        y->keys.resize(t - 1);

        children.insert(children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, midKey);
    }
};

class BTree {
    BTreeNode* root;
    int t;
public:
    BTree(int t) {
        this->t = t;
        root = nullptr;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
        cout << "\n";
    }

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(key);
            return;
        }

        if ((int)root->keys.size() == 2 * t - 1) {
            BTreeNode* newRoot = new BTreeNode(t, false);
            newRoot->children.push_back(root);
            newRoot->splitChild(0, root);

            int i = (newRoot->keys[0] < key) ? 1 : 0;
            newRoot->children[i]->insertNonFull(key);

            root = newRoot;
        } else {
            root->insertNonFull(key);
        }
    }
};

int main() {
    int t;
    cout << "Enter minimum degree t of the B-Tree (t >= 2): ";
    cin >> t;

    BTree tree(t);

    int n;
    cout << "Enter number of keys to insert: ";
    cin >> n;

    cout << "Enter " << n << " keys: ";
    for (int i = 0; i < n; i++) {
        int key;
        cin >> key;
        tree.insert(key);
    }

    cout << "\nIn-order traversal of the B-Tree (sorted keys): ";
    tree.traverse();

    return 0;
}
