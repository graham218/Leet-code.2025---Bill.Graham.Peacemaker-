// Dynamic Programming (DP) - Longest Common Subsequence (LCS)

/*
The Longest Common Subsequence (LCS) problem is a classic computer science problem that involves finding the longest subsequence common to two or more sequences. A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.

Here are 5 different approaches to solve the LCS problem, along with real-world project implementations:

1.  **Memoization (Top-Down)**: This approach involves storing the results of expensive function calls and reusing them when needed. It's a top-down approach because it starts with the original problem and breaks it down into smaller subproblems.
    * **Real-world project implementation**: Bioinformatics (sequence alignment), Text differencing (Git).

2.  **Tabulation (Bottom-Up)**: This approach involves filling up a table in a bottom-up manner, ensuring that before solving a larger subproblem, all its smaller subproblems are already solved.
    * **Real-world project implementation**:  Diff utilities, Plagiarism detection.

3.  **Space Optimized Tabulation**: This is an optimized version of the tabulation method, where instead of storing the entire table, we only store the previous row. This reduces the space complexity from O(m*n) to O(min(m,n)).
     * **Real-world project implementation**: DNA sequence alignment (for memory-constrained systems).

4.  **Recursive Solution**: This is the most basic solution.
    * **Real-world project implementation**: While not always directly used due to inefficiency, it's the basis for understanding DP solutions and is used in teaching DP concepts.

5.  **Finding the LCS String**: This approach not only finds the length of the LCS but also reconstructs the actual LCS string.
    * **Real-world project implementation**: File comparison and merging (generating the diff),  Bioinformatics (finding common DNA subsequences).
*/

// 1. Memoization (Top-Down)
function lcsMemoization(str1, str2, m, n, memo = {}) { // Added m and n to function parameters
  if (m === 0 || n === 0) {
    return 0;
  }

  const key = `${m}-${n}`;
  if (memo[key] !== undefined) {
    return memo[key];
  }

  if (str1[m - 1] === str2[n - 1]) {
    memo[key] = 1 + lcsMemoization(str1, str2, m - 1, n - 1, memo); // Corrected recursive call
  } else {
    memo[key] = Math.max(
      lcsMemoization(str1, str2, m - 1, n, memo),     // Corrected recursive call
      lcsMemoization(str1, str2, m, n - 1, memo)      // Corrected recursive call
    );
  }

  return memo[key];
}

// 2. Tabulation (Bottom-Up)
function lcsTabulation(str1, str2) {
  const m = str1.length;
  const n = str2.length;
  const dp = Array(m + 1)
    .fill(null)
    .map(() => Array(n + 1).fill(0));

  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (str1[i - 1] === str2[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  return dp[m][n];
}

// 3. Space Optimized Tabulation
function lcsSpaceOptimized(str1, str2) {
  const m = str1.length;
  const n = str2.length;

  // Ensure that 'prev' array always stores the smaller length string
  if (m < n) {
    [str1, str2] = [str2, str1]; //swap
  }

  const len1 = str1.length; // Longer string
  const len2 = str2.length; // Shorter string

  let prev = Array(len2 + 1).fill(0); // Previous row
  let curr = Array(len2 + 1).fill(0); // Current row

  for (let i = 1; i <= len1; i++) {
    for (let j = 1; j <= len2; j++) {
      if (str1[i - 1] === str2[j - 1]) {
        curr[j] = 1 + prev[j - 1];
      } else {
        curr[j] = Math.max(prev[j], curr[j - 1]);
      }
    }
    // After processing current row, update 'prev' with 'curr' for next iteration
    prev = [...curr]; // Important: Create a copy, not a reference!
  }
  return prev[len2];
}

// 4. Recursive Solution
function lcsRecursive(str1, str2, m, n) {
  if (m === 0 || n === 0) {
    return 0;
  }

  if (str1[m - 1] === str2[n - 1]) {
    return 1 + lcsRecursive(str1, str2, m - 1, n - 1);
  } else {
    return Math.max(
      lcsRecursive(str1, str2, m - 1, n),
      lcsRecursive(str1, str2, m, n - 1)
    );
  }
}

// 5. Finding the LCS String
function lcsString(str1, str2) {
  const m = str1.length;
  const n = str2.length;
  const dp = Array(m + 1)
    .fill(null)
    .map(() => Array(n + 1).fill(0));

  for (let i = 1; i <= m; i++) {
    for (let j = 1; j <= n; j++) {
      if (str1[i - 1] === str2[j - 1]) {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      } else {
        dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  let i = m;
  let j = n;
  let lcs = "";
  while (i > 0 && j > 0) {
    if (str1[i - 1] === str2[j - 1]) {
      lcs = str1[i - 1] + lcs;
      i--;
      j--;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      i--;
    } else {
      j--;
    }
  }
  return { length: dp[m][n], sequence: lcs };
}

// Example Usage
const str1 = "AGGTAB";
const str2 = "GXTXAYB";

console.log("String 1:", str1);
console.log("String 2:", str2);
console.log("\n--- LCS Length ---");
console.log("Memoization:", lcsMemoization(str1, str2, str1.length, str2.length));
console.log("Tabulation:", lcsTabulation(str1, str2));
console.log("Space Optimized:", lcsSpaceOptimized(str1, str2));
console.log("Recursion:", lcsRecursive(str1, str2, str1.length, str2.length));

console.log("\n--- LCS String ---");
const result = lcsString(str1, str2);
console.log("LCS Length:", result.length);
console.log("LCS Sequence:", result.sequence);
