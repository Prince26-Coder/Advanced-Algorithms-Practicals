#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    bool isSuffixEnd = false;

    int suffixIndex = -1;
};

class SuffixTrie {
    TrieNode* root;
    string text; 

public:
    SuffixTrie(const string& s) {
        root = new TrieNode();
        text = s + "$"; 
        bruteForceSuffixTrie();
    }

    void bruteForceSuffixTrie() {
        int n = text.size();
        for (int i = 0; i < n; i++) {
            insertSuffix(i);
        }
    }

    void insertSuffix(int start) {
        TrieNode* current = root;
        for (int i = start; i < (int)text.size(); i++) {
            char ch = text[i];
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isSuffixEnd = true;
        current->suffixIndex = start;
    }

    bool search(const string& pattern) {
        TrieNode* current = root;
        for (char ch : pattern) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return true; 
    }
};

int main() {
    string text;
    cout << "Enter the text: ";
    cin >> text;

    SuffixTrie trie(text);

    int q;
    cout << "Enter number of patterns to search: ";
    cin >> q;

    cout << "Enter each pattern:\n";
    while (q--) {
        string pattern;
        cin >> pattern;
        if (trie.search(pattern)) {
            cout << "\"" << pattern << "\" found in text.\n";
        } else {
            cout << "\"" << pattern << "\" NOT found in text.\n";
        }
    }

    return 0;
}
