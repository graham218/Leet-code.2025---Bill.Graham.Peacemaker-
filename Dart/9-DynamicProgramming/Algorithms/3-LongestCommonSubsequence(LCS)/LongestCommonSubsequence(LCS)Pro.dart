import 'dart:math';

// Advanced Longest Common Subsequence (LCS) Solutions in Dart
// Implementing six distinct approaches with real-world applications

// 1. Basic Recursive Approach
// This is the most straightforward implementation of the LCS problem using recursion.
// It explores all possible subsequences, leading to exponential time complexity.
int lcsRecursive(String s1, String s2, int m, int n) {
  // Base case: If either string is empty, the LCS length is 0.
  if (m == 0 || n == 0) return 0;

  // If the last characters of both strings match, the LCS length increases by 1,
  // and we recurse for the remaining prefixes.
  if (s1[m - 1] == s2[n - 1]) {
    return 1 + lcsRecursive(s1, s2, m - 1, n - 1);
  } else {
    // If the last characters don't match, we take the maximum LCS length from
    // the two possible subproblems:
    // 1. Excluding the last character of s1.
    // 2. Excluding the last character of s2.
    return max(lcsRecursive(s1, s2, m - 1, n), lcsRecursive(s1, s2, m, n - 1));
  }
}

// 2. Memoization Approach (Top-Down DP)
// Memoization optimizes the recursive approach by storing the results of subproblems
// in a map (memo) to avoid redundant calculations.
Map<String, int> memo = {};
int lcsMemoization(String s1, String s2, int m, int n) {
  // Base case: If either string is empty, the LCS length is 0.
  if (m == 0 || n == 0) return 0;

  // Create a unique key for the current subproblem.
  String key = "$m-$n";

  // If the result is already in the memo, return it.
  if (memo.containsKey(key)) return memo[key]!;

  // If the last characters of both strings match, the LCS length increases by 1,
  // and we recurse for the remaining prefixes, storing the result in memo.
  if (s1[m - 1] == s2[n - 1]) {
    return memo[key] = 1 + lcsMemoization(s1, s2, m - 1, n - 1);
  }
  // If the last characters don't match, we take the maximum LCS length from
  // the two possible subproblems, storing the result in memo.
  return memo[key] = max(lcsMemoization(s1, s2, m - 1, n), lcsMemoization(s1, s2, m, n - 1));
}

// 3. Iterative Dynamic Programming (Bottom-Up DP)
// This approach builds a table (dp) to store the results of subproblems in a bottom-up manner.
// It avoids recursion and typically has better performance than memoization.
int lcsIterative(String s1, String s2) {
  int m = s1.length, n = s2.length;
  // Create a 2D list (dp) to store the LCS lengths for different prefixes of s1 and s2.
  // dp[i][j] represents the LCS length of s1[0...i-1] and s2[0...j-1].
  List<List<int>> dp = List.generate(m + 1, (_) => List.filled(n + 1, 0));

  // Iterate through the characters of s1 and s2.
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      // If the characters match, the LCS length increases by 1.
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        // If the characters don't match, we take the maximum LCS length from
        // the two possible subproblems.
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  // The result is stored in the bottom-right cell of the dp table.
  return dp[m][n];
}

// 4. Space Optimized DP Approach
// This approach optimizes the iterative DP method by using only two rows (prev and curr)
// instead of the entire dp table. This reduces the space complexity from O(m*n) to O(n).
int lcsSpaceOptimized(String s1, String s2) {
  int m = s1.length, n = s2.length;
  // Create two 1D lists to store the previous and current row values.
  List<int> prev = List.filled(n + 1, 0);
  List<int> curr = List.filled(n + 1, 0);

  // Iterate through the characters of s1 and s2.
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      // If the characters match, the LCS length increases by 1.
      if (s1[i - 1] == s2[j - 1]) {
        curr[j] = prev[j - 1] + 1;
      } else {
        // If the characters don't match, we take the maximum LCS length from
        // the two possible subproblems.
        curr[j] = max(prev[j], curr[j - 1]);
      }
    }
    // Update the previous row with the current row values.
    prev = List.from(curr);
  }
  // The result is stored in the last row (prev).
  return prev[n];
}

// 5. Real-World Application: Plagiarism Detection
// This function demonstrates a real-world application of LCS in plagiarism detection.
// By comparing two texts and finding their longest common subsequence,
// we can identify similarities and potential plagiarism.
int lcsPlagiarismCheck(String text1, String text2) {
  return lcsIterative(text1, text2);
}

// 6. Real-World Application: Speech-to-Text Error Correction
// This function demonstrates a real-world application of LCS in speech-to-text error correction.
// By comparing the transcribed text with the correct text,
// we can identify and correct errors by finding the longest common subsequence.
int lcsSpeechCorrection(String transcript, String correctText) {
  return lcsIterative(transcript, correctText);
}

void main() {
  String s1 = "ABCBDAB";
  String s2 = "BDCAB";

  print("Recursive LCS: ${lcsRecursive(s1, s2, s1.length, s2.length)}");
  print("Memoization LCS: ${lcsMemoization(s1, s2, s1.length, s2.length)}");
  print("Iterative DP LCS: ${lcsIterative(s1, s2)}");
  print("Space Optimized LCS: ${lcsSpaceOptimized(s1, s2)}");
  print("Plagiarism Detection: ${lcsPlagiarismCheck(s1, s2)}");
  print("Speech-to-Text Correction: ${lcsSpeechCorrection(s1, s2)}");
}