// Longest Common Subsequence (LCS) Problem

// Helper function to find the maximum of two numbers.
function max(a, b) {
    return (a > b) ? a : b;
}

// 1. Recursive Approach for LCS
// This is the most basic approach, directly translating the recursive definition of LCS.
// It has exponential time complexity, making it inefficient for larger inputs.
function lcsRecursive(str1, str2, m, n) {
    if (m === 0 || n === 0) {
        return 0;
    }
    if (str1[m - 1] === str2[n - 1]) {
        return 1 + lcsRecursive(str1, str2, m - 1, n - 1);
    } else {
        return max(lcsRecursive(str1, str2, m - 1, n), lcsRecursive(str1, str2, m, n - 1));
    }
}

// 2. Memoization (Top-Down DP) Approach for LCS
// This approach improves the recursive solution by storing the results of subproblems
// in a table (memo) to avoid redundant computations.
// It has a time complexity of O(m*n), where m and n are the lengths of the strings.
function lcsMemoization(str1, str2, m, n, memo) {
    if (m === 0 || n === 0) {
        return 0;
    }
    if (memo[m][n] !== -1) {
        return memo[m][n];
    }
    if (str1[m - 1] === str2[n - 1]) {
        memo[m][n] = 1 + lcsMemoization(str1, str2, m - 1, n - 1, memo);
        return memo[m][n];
    } else {
        memo[m][n] = max(lcsMemoization(str1, str2, m - 1, n, memo), lcsMemoization(str1, str2, m, n - 1, memo));
        return memo[m][n];
    }
}

// 3. Tabulation (Bottom-Up DP) Approach for LCS
// This approach builds the solution table iteratively, starting from the base cases.
// It also has a time complexity of O(m*n) and is generally more efficient than memoization.
function lcsTabulation(str1, str2, m, n) {
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[m][n];
}

// 4. Space Optimized Tabulation Approach for LCS
// This approach optimizes the tabulation method by reducing the space complexity
// from O(m*n) to O(min(m, n)).  It only stores the previous row of the DP table.
function lcsSpaceOptimized(str1, str2, m, n) {
    if (m < n) {
        [str1, str2, m, n] = [str2, str1, n, m]; // Ensure m >= n
    }

    let prev = Array(n + 1).fill(0);
    let curr = Array(n + 1).fill(0);

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                curr[j] = 1 + prev[j - 1];
            } else {
                curr[j] = max(prev[j], curr[j - 1]);
            }
        }
        prev = [...curr]; // Copy curr to prev
    }
    return prev[n];
}

// 5.  Finding the LCS String (Tabulation)
function lcsString(str1, str2, m, n) {
    const dp = Array(m + 1).fill(null).map(() => Array(n + 1).fill(0));

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    let index = dp[m][n];
    let lcs = "";
    let i = m, j = n;
    while (i > 0 && j > 0) {
        if (str1[i - 1] === str2[j - 1]) {
            lcs = str1[i - 1] + lcs;
            i--;
            j--;
            index--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

// Example usage:
const str1 = "AGGTAB";
const str2 = "GXTXAYB";
const m = str1.length;
const n = str2.length;

// Initialize memoization table with -1
const memo = Array(m + 1).fill(null).map(() => Array(n + 1).fill(-1));

console.log("String 1: " + str1);
console.log("String 2: " + str2);
console.log("\nResults:");

console.log("1. Recursive LCS Length:", lcsRecursive(str1, str2, m, n));
console.log("2. Memoization LCS Length:", lcsMemoization(str1, str2, m, n, memo));
console.log("3. Tabulation LCS Length:", lcsTabulation(str1, str2, m, n));
console.log("4. Space Optimized LCS Length:", lcsSpaceOptimized(str1, str2, m, n));
console.log("5. LCS String:", lcsString(str1, str2, m, n));
