#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <regex> // Include the regex header

using namespace std;

// Approach 1: Using a Stack (Standard Approach)
// Time Complexity: O(n), Space Complexity: O(n)
bool isValid1(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false; // Closing bracket with nothing to match
            char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false; // Mismatched brackets
            }
        }
    }
    return st.empty(); // Ensure all opening brackets are matched
}

// Approach 2: Using a Stack and a Map
// Time Complexity: O(n), Space Complexity: O(n)
bool isValid2(string s) {
    stack<char> st;
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            st.pop();
            if (pairs[c] != top) {
                return false;
            }
        }
    }
    return st.empty();
}

// Approach 3: Without Stack (but less efficient for all cases) - Optimized for specific patterns
// Time Complexity: O(n) in best case, O(n^2) in worst case, Space Complexity: O(1)
bool isValid3(string s) {
    int len;
    do {
        len = s.length();
        s = regex_replace(s, regex("\\(\\)|\\[\\]|\\{\\}"), ""); //repeatedly remove "()", "[]", "{}"
    } while (len != s.length());
    return s.empty();
}

// Approach 4: Using Recursion (Not recommended for very long strings due to stack overflow)
// Time Complexity: O(n) in best case, O(n^2) in worst case, Space Complexity: O(n)
bool isValid4(string s) {
    if (s.empty()) return true;
    size_t pos;
    pos = s.find("()");
    if (pos != string::npos) return isValid4(s.substr(0, pos) + s.substr(pos + 2));
    pos = s.find("[]");
    if (pos != string::npos) return isValid4(s.substr(0, pos) + s.substr(pos + 2));
    pos = s.find("{}");
    if (pos != string::npos) return isValid4(s.substr(0, pos) + s.substr(pos + 2));
    return false;
}

// Approach 5: Using a Stack and a Vector for lookup.
// Time Complexity: O(n), Space Complexity: O(n)
bool isValid5(string s) {
    stack<char> st;
    vector<char> openChars = {'(', '[', '{'};
    vector<char> closeChars = {')', ']', '}'};
    for(char c : s){
        for(int i = 0; i < 3; ++i){
            if(c == openChars[i]){
                st.push(c);
                goto nextChar; // Jump to the next character in s
            }
            else if (c == closeChars[i]){
                if(st.empty()) return false;
                char top = st.top();
                st.pop();
                if(top != openChars[i]) return false;
                goto nextChar; // Jump to the next character in s
            }
        }
        nextChar:; // Label for the goto statement
    }
    return st.empty();
}

int main() {
    string test1 = "()";
    string test2 = "()[]{}";
    string test3 = "(]";
    string test4 = "([)]";
    string test5 = "{[]}";
    string test6 = "((()))";
    string test7 = "){";

    cout << "Test Cases:\n";
    cout << "1. " << test1 << endl;
    cout << "2. " << test2 << endl;
    cout << "3. " << test3 << endl;
    cout << "4. " << test4 << endl;
    cout << "5. " << test5 << endl;
    cout << "6. " << test6 << endl;
    cout << "7. " << test7 << endl;

    cout << "\nResults using Approach 1 (Stack):\n";
    cout << "1: " << isValid1(test1) << endl;
    cout << "2: " << isValid1(test2) << endl;
    cout << "3: " << isValid1(test3) << endl;
    cout << "4: " << isValid1(test4) << endl;
    cout << "5: " << isValid1(test5) << endl;
    cout << "6: " << isValid1(test6) << endl;
    cout << "7: " << isValid1(test7) << endl;

    cout << "\nResults using Approach 2 (Stack and Map):\n";
    cout << "1: " << isValid2(test1) << endl;
    cout << "2: " << isValid2(test2) << endl;
    cout << "3: " << isValid2(test3) << endl;
    cout << "4: " << isValid2(test4) << endl;
    cout << "5: " << isValid2(test5) << endl;
    cout << "6: " << isValid2(test6) << endl;
    cout << "7: " << isValid2(test7) << endl;

    cout << "\nResults using Approach 3 (Without Stack):\n";
    cout << "1: " << isValid3(test1) << endl;
    cout << "2: " << isValid3(test2) << endl;
    cout << "3: " << isValid3(test3) << endl;
    cout << "4: " << isValid3(test4) << endl;
    cout << "5: " << isValid3(test5) << endl;
    cout << "6: " << isValid3(test6) << endl;
    cout << "7: " << isValid3(test7) << endl;

    cout << "\nResults using Approach 4 (Recursion):\n";
    cout << "1: " << isValid4(test1) << endl;
    cout << "2: " << isValid4(test2) << endl;
    cout << "3: " << isValid4(test3) << endl;
    cout << "4: " << isValid4(test4) << endl;
    cout << "5: " << isValid4(test5) << endl;
    cout << "6: " << isValid4(test6) << endl;
    cout << "7: " << isValid4(test7) << endl;

    cout << "\nResults using Approach 5 (Stack and Vector):\n";
    cout << "1: " << isValid5(test1) << endl;
    cout << "2: " << isValid5(test2) << endl;
    cout << "3: " << isValid5(test3) << endl;
    cout << "4: " << isValid5(test4) << endl;
    cout << "5: " << isValid5(test5) << endl;
    cout << "6: " << isValid5(test6) << endl;
    cout << "7: " << isValid5(test7) << endl;

    return 0;
}
