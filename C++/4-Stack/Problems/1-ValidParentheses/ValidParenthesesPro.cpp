#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exception handling

using namespace std;

// Approach 1: Classic Stack Solution
//   - Uses a stack to track opening brackets and checks for proper closing.
//   - Suitable for basic validation in any application that processes bracketed input.
bool isValid_Stack(const string& s) {
    if (s.empty()) return true; // Empty string is considered valid
    if (s.size() % 2 != 0) return false; // Odd length strings cannot be valid

    stack<char> bracketStack;
    for (char c : s) {
        switch (c) {
            case '(': bracketStack.push(c); break;
            case '{': bracketStack.push(c); break;
            case '[': bracketStack.push(c); break;
            case ')':
                if (bracketStack.empty() || bracketStack.top() != '(') return false;
                bracketStack.pop();
                break;
            case '}':
                if (bracketStack.empty() || bracketStack.top() != '{') return false;
                bracketStack.pop();
                break;
            case ']':
                if (bracketStack.empty() || bracketStack.top() != '[') return false;
                bracketStack.pop();
                break;
            default:
                // Handle invalid characters.  In a real application, you might:
                // 1. Log an error.
                // 2. Throw an exception.
                // 3. Ignore the character.
                return false; // For this problem, we'll treat invalid chars as making the string invalid.
        }
    }
    return bracketStack.empty(); // The string is valid if the stack is empty at the end.
}

// Approach 2: Stack with Early Exit for Mismatched Counts
//   - Optimized version that checks counts of opening and closing brackets early on.
//   - Useful when dealing with potentially very long strings, providing a quick check before more intensive processing.
bool isValid_StackEarlyExit(const string& s) {
    if (s.empty()) return true;
    if (s.size() % 2 != 0) return false;

    int openParenCount = 0, openBraceCount = 0, openBracketCount = 0;
    for (char c : s) {
        switch (c) {
            case '(': openParenCount++; break;
            case '{': openBraceCount++; break;
            case '[': openBracketCount++; break;
            case ')': openParenCount--; break;
            case '}': openBraceCount--; break;
            case ']': openBracketCount--; break;
            default: return false;
        }
    }
    if (openParenCount != 0 || openBraceCount != 0 || openBracketCount != 0) return false;

    stack<char> bracketStack;
    for (char c : s) {
        switch (c) {
            case '(': bracketStack.push(c); break;
            case '{': bracketStack.push(c); break;
            case '[': bracketStack.push(c); break;
            case ')':
                if (bracketStack.empty() || bracketStack.top() != '(') return false;
                bracketStack.pop();
                break;
            case '}':
                if (bracketStack.empty() || bracketStack.top() != '{') return false;
                bracketStack.pop();
                break;
            case ']':
                if (bracketStack.empty() || bracketStack.top() != '[') return false;
                bracketStack.pop();
                break;
            default: return false;
        }
    }
    return bracketStack.empty();
}

// Approach 3: Using a Map for Matching
//   - Employs an unordered_map for efficient matching of closing to opening brackets.
//   - Improves readability and can be slightly faster for large inputs due to the hash table lookup.
bool isValid_Map(const string& s) {
    if (s.empty()) return true;
    if (s.size() % 2 != 0) return false;

    unordered_map<char, char> matchingPairs = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    stack<char> bracketStack;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            bracketStack.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (bracketStack.empty() || bracketStack.top() != matchingPairs[c]) {
                return false;
            }
            bracketStack.pop();
        } else {
            return false;
        }
    }
    return bracketStack.empty();
}

// Approach 4: Iterative Replacement (Not Recommended for Large Inputs)
//   - Repeatedly replaces matching pairs "()", "{}", and "[]" with empty strings.
//   - Simpler to understand but can be inefficient for long or complex strings due to repeated string operations.
//   - Best suited for very short strings or as a demonstration of a different approach.  Avoid in performance-critical code.
bool isValid_Replace(string s) {
    if (s.empty()) return true;
    if (s.size() % 2 != 0) return false;

    while (s.find("()") != string::npos || s.find("{}") != string::npos || s.find("[]") != string::npos) {
        size_t pos;
        pos = s.find("()");
        if (pos != string::npos) s.replace(pos, 2, "");
        pos = s.find("{}");
        if (pos != string::npos) s.replace(pos, 2, "");
        pos = s.find("[]");
        if (pos != string::npos) s.replace(pos, 2, "");
    }
    return s.empty();
}

// Approach 5: Recursive Solution (For Demonstration - Can Cause Stack Overflow)
//   - Recursively checks for and removes matching pairs.
//   - Elegant but can be very inefficient and lead to stack overflow for deeply nested brackets.
//   - Primarily for educational purposes, demonstrating recursion.  Avoid in production code for potentially large inputs.
bool isValid_Recursive(const string& s) {
    if (s.empty()) return true;
    if (s.size() % 2 != 0) return false;

    size_t pos;
    string modifiedS = s; // Create a copy to modify

    pos = modifiedS.find("()");
    if (pos != string::npos) {
        modifiedS.replace(pos, 2, "");
        return isValid_Recursive(modifiedS);
    }
    pos = modifiedS.find("{}");
    if (pos != string::npos) {
        modifiedS.replace(pos, 2, "");
        return isValid_Recursive(modifiedS);
    }
    pos = modifiedS.find("[]");
    if (pos != string::npos) {
        modifiedS.replace(pos, 2, "");
        return isValid_Recursive(modifiedS);
    }
    return modifiedS.empty();
}

int main() {
    // Test cases to demonstrate the different approaches
    vector<string> testCases = {
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "",
        "((()))",
        "[{()}]",
        "((",
        "))",
        "}{",
        "[(])",
        "()[]{}(){}",
        "((()))[{}]",
        "{{{{}}}}"
    };

    cout << "Valid Parentheses - Test Cases and Results:\n";
    cout << "-------------------------------------------\n";

    for (const string& testCase : testCases) {
        cout << "Test Case: \"" << testCase << "\"\n";
        cout << "--------------------\n";
        try {
            cout << "Stack Approach:         " << (isValid_Stack(testCase) ? "Valid" : "Invalid") << "\n";
            cout << "Stack Early Exit:       " << (isValid_StackEarlyExit(testCase) ? "Valid" : "Invalid") << "\n";
            cout << "Map Approach:           " << (isValid_Map(testCase) ? "Valid" : "Invalid") << "\n";
            cout << "Replace Approach:       " << (isValid_Replace(testCase) ? "Valid" : "Invalid") << "\n";
            cout << "Recursive Approach:     " << (isValid_Recursive(testCase) ? "Valid" : "Invalid") << "\n";
        } catch (const std::exception& e) {
            cerr << "An exception occurred: " << e.what() << "\n";
        }
        cout << "\n";
    }

    // Example of using the isValid function in a real-world scenario (e.g., config file validation)
    cout << "\nReal-world Example: Configuration File Validation\n";
    cout << "--------------------------------------------------\n";
    string configFile = "[{ \"server\": \"localhost\", \"port\": 8080, \"connections\": (100) }]";
    if (isValid_Stack(configFile)) { // Use the Stack approach, as it's generally the most robust
        cout << "Configuration file is valid.\n";
        //  Parse the configuration file here (e.g., using a JSON parser).  This is where you'd
        //  integrate this validation into your application's startup or configuration loading.
    } else {
        cout << "Configuration file is invalid: " << configFile << "\n";
        //  Handle the error:  log it, display an error message to the user, or exit the application.
    }

    cout << "\nReal-world Example: Code Editor/IDE Bracket Matching\n";
    cout << "--------------------------------------------------\n";
    string codeSnippet = "function example(arg1: string, arg2: number[]): void { console.log(arg1, arg2); }";
    if(isValid_Stack(codeSnippet)) {
        cout << "Code snippet has balanced brackets.\n";
    }
    else {
        cout << "Code snippet has unbalanced brackets.\n";
    }

    return 0;
}
