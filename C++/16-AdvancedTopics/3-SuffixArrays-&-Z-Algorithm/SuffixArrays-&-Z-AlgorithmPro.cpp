// C++ Solution: Suffix Arrays & Z-Algorithm with 5 Approaches
// This code demonstrates five different real-world inspired approaches to using suffix arrays and the Z-algorithm in C++

#include <bits/stdc++.h>
using namespace std;

//--------------------------------------//
// Approach 1: Basic Suffix Array Construction (Naive - Education Purpose)
//--------------------------------------//
vector<int> buildSuffixArrayNaive(const string &s) {
    int n = s.size();
    vector<pair<string, int>> suffixes;
    for (int i = 0; i < n; ++i) {
        suffixes.emplace_back(s.substr(i), i);
    }
    sort(suffixes.begin(), suffixes.end());

    vector<int> sa(n);
    for (int i = 0; i < n; ++i)
        sa[i] = suffixes[i].second;

    return sa;
}

//--------------------------------------//
// Approach 2: Kasai's Algorithm for LCP Array (used in text indexing/search engines)
//--------------------------------------//
vector<int> buildLCPArray(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> rank(n, 0), lcp(n, 0);
    for (int i = 0; i < n; ++i) rank[sa[i]] = i;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) ++k;
        lcp[rank[i]] = k;
        if (k) --k;
    }
    return lcp;
}

//--------------------------------------//
// Approach 3: Z-Algorithm (Used in Bioinformatics for DNA sequence analysis)
//--------------------------------------//
vector<int> computeZArray(const string &s) {
    int n = s.size();
    vector<int> Z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) Z[i] = min(r - i + 1, Z[i - l]);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) ++Z[i];
        if (i + Z[i] - 1 > r) l = i, r = i + Z[i] - 1;
    }
    return Z;
}

//--------------------------------------//
// Approach 4: Pattern Matching Using Suffix Array (Search engine autocomplete feature)
//--------------------------------------//
bool patternExists(const string &text, const string &pattern, const vector<int> &sa) {
    int left = 0, right = sa.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        string suffix = text.substr(sa[mid]);
        if (suffix.compare(0, pattern.size(), pattern) == 0)
            return true;
        else if (suffix < pattern)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

//--------------------------------------//
// Approach 5: Spam Detection using Z-algorithm (Real-world content filtering)
//--------------------------------------//
bool isSpam(const string &emailBody, const vector<string> &spamKeywords) {
    for (const string &keyword : spamKeywords) {
        string combined = keyword + "$" + emailBody;
        vector<int> Z = computeZArray(combined);
        for (int i = keyword.size() + 1; i < Z.size(); ++i) {
            if (Z[i] == keyword.size()) return true;
        }
    }
    return false;
}

//--------------------------------------//
// Main function to demonstrate usage
//--------------------------------------//
int main() {
    string text = "banana";
    vector<int> sa = buildSuffixArrayNaive(text);
    vector<int> lcp = buildLCPArray(text, sa);

    cout << "Suffix Array: ";
    for (int i : sa) cout << i << " ";
    cout << "\nLCP Array: ";
    for (int i : lcp) cout << i << " ";
    cout << endl;

    string pattern = "ana";
    cout << "Pattern \"" << pattern << "\" found: " << (patternExists(text, pattern, sa) ? "Yes" : "No") << endl;

    vector<string> spamWords = {"free", "win", "banana"};
    cout << "Email is spam: " << (isSpam("You can win a banana!", spamWords) ? "Yes" : "No") << endl;

    return 0;
}
