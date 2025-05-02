// KMP Algorithm and Its Real-World Project Implementations (5 Approaches)
// Author: [Your Name]
// Description: This file contains C++ implementations of the Knuth-Morris-Pratt (KMP) pattern matching algorithm
// across five different real-world scenarios with detailed code comments.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Helper: Build the Longest Prefix Suffix (LPS) array
vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m);
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i++] = len;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

// Core KMP Pattern Search
vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size();
    int m = pattern.size();

    vector<int> lps = buildLPS(pattern);
    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++, i++;
        }
        if (j == m) {
            result.push_back(i - j); // pattern found
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return result;
}

/********** Real-World Implementation Scenarios **********/

// 1. Spam Detection in Emails
void spamDetection() {
    string emailBody = "Dear user, you have won a prize! Claim your prize now!";
    string spamPhrase = "claim your prize";
    vector<int> matches = KMPSearch(emailBody, spamPhrase);

    cout << "[Spam Detection] Found spam phrase at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// 2. DNA Sequence Analysis
void dnaSequenceSearch() {
    string genome = "ACTGAGCTAGCTAGCTTACGATC";
    string genePattern = "AGCTAGC";
    vector<int> matches = KMPSearch(genome, genePattern);

    cout << "[DNA Search] Found gene pattern at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// 3. Plagiarism Detection in Text Documents
void plagiarismDetection() {
    string doc1 = "The quick brown fox jumps over the lazy dog.";
    string doc2 = "brown fox jumps over";
    vector<int> matches = KMPSearch(doc1, doc2);

    cout << "[Plagiarism Detection] Match found at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// 4. Intrusion Detection in Network Logs
void intrusionDetection() {
    string networkLog = "User login success. Failed attempt. Failed attempt. Suspicious activity detected.";
    string intrusionPattern = "Failed attempt. Suspicious activity";
    vector<int> matches = KMPSearch(networkLog, intrusionPattern);

    cout << "[Intrusion Detection] Intrusion pattern at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// 5. Search Engine Query Matching
void searchEngineQuery() {
    string websiteText = "Learn C++ programming with hands-on projects and examples.";
    string userQuery = "C++ programming";
    vector<int> matches = KMPSearch(websiteText, userQuery);

    cout << "[Search Engine] Query matched at indices: ";
    for (int idx : matches) cout << idx << " ";
    cout << endl;
}

// Main driver
int main() {
    spamDetection();
    dnaSequenceSearch();
    plagiarismDetection();
    intrusionDetection();
    searchEngineQuery();
    return 0;
}
