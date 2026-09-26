#include <bits/stdc++.h>
using namespace std;

vector<int> computeLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0; 
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; 
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> matches;
    int n = text.size(), m = pattern.size();
    if (m == 0) return matches;

    vector<int> lps = computeLPS(pattern);

    int i = 0; 
    int j = 0; 

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            if (j == m) {
                matches.push_back(i - j); 
                j = lps[j - 1];           
            }
        } else if (j != 0) {
            j = lps[j - 1]; 
        } else {
            i++;
        }
    }
    return matches;
}

int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    vector<int> result = KMPSearch(text, pattern);

    if (result.empty()) {
        cout << "\nPattern not found in text.\n";
    } else {
        cout << "\nPattern found at index(es): ";
        for (int idx : result) cout << idx << " ";
        cout << "\n";
    }

    return 0;
}
