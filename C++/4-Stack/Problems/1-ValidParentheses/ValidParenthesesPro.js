/**
 * 1. Stack Approach (Most Common)
 *
 * * Concept: Uses a stack to keep track of opening brackets.  When a closing bracket is encountered,
 * it checks if it matches the top of the stack.
 * * Real-world: Useful in compilers to validate code syntax, in XML/JSON parsers to check tag matching,
 * and in text editors for bracket matching.
 */
function isValidStack(s) {
    const stack = [];
    const map = {
        ')': '(',
        '}': '{',
        ']': '['
    };

    for (let i = 0; i < s.length; i++) {
        const char = s[i];

        if (map[char]) { // If it's a closing bracket
            const topElement = stack.pop() || '#'; // Use '#' as a dummy if stack is empty
            if (topElement !== map[char]) {
                return false;
            }
        } else { // If it's an opening bracket
            stack.push(char);
        }
    }

    return stack.length === 0;
}

// 2. Stack Approach with Early Exit
// Concept: Similar to the first approach, but adds an optimization to exit early if a mismatch is found.
function isValidStackEarlyExit(s) {
  const stack = [];
  const map = {
    ')': '(',
    '}': '{',
    ']': '['
  };

  for (let i = 0; i < s.length; i++) {
    const char = s[i];

    if (map[char]) {
      const topElement = stack.pop();
      if (!topElement || topElement !== map[char]) { // Check for empty stack *and* mismatch
        return false;
      }
    } else {
      stack.push(char);
    }
  }
  return stack.length === 0;
}

/**
 * 3. Recursive Approach (Less Common, but good for understanding recursion)
 *
 * * Concept: Recursively checks if the first bracket and its matching closing bracket
 * are valid, then recursively checks the rest of the string.
 * * Real-world:  While less common for this specific problem, recursion is fundamental
 * in many algorithms like tree traversals, graph searches, and parsing complex structures.  This
 * demonstrates a basic recursive pattern.
 */
function isValidRecursive(s) {
    if (s.length === 0) return true;

    const matching = { '(': ')', '{': '}', '[': ']' };
    for (let i = 0; i < s.length; i++) {
        if (matching[s[i]]) {
            let count = 1;
            for (let j = i + 1; j < s.length; j++) {
                if (s[j] === matching[s[i]]) {
                    count--;
                    if (count === 0) {
                        const restOfStringValid = isValidRecursive(s.substring(i + 1, j)) && isValidRecursive(s.substring(j+1));
                        return restOfStringValid;
                    }
                } else if (s[j] === s[i]) {
                    count++;
                }
            }
            return false; //closing bracket not found
        }
    }
    return false;
}

/**
 * 4. Replace and Check (Efficient for certain patterns)
 *
 * * Concept: Repeatedly removes all matching pairs of parentheses from the string.
 * If the string is empty at the end, it's valid.
 * * Real-world: Useful in some string processing scenarios where you need to simplify
 * or normalize strings by removing matching patterns.  Can be adapted for tasks
 * like removing redundant delimiters or simplifying code.
 */
function isValidReplace(s) {
    let originalLength;
    do {
        originalLength = s.length;
        s = s.replace(/\(\)|{}|\[\]/g, '');
    } while (s.length !== originalLength);
    return s.length === 0;
}

/**
 * 5. Using a Map and Single Loop (Optimized)
 *
 * Concept: Uses a map to store the opening-closing pairs and efficiently checks the string in a single loop.
 * Real-world: This approach is very efficient and can be used in performance-critical applications
 * such as validating large code files or processing a high volume of data with bracketed structures.
 */
function isValidMap(s) {
    if (s.length % 2 !== 0) return false; // Odd length strings cannot be valid.

    const map = new Map([
        [')', '('],
        ['}', '{'],
        [']', '[']
    ]);
    const stack = [];

    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (map.has(char)) { // Closing bracket
            const top = stack.pop();
            if (top !== map.get(char)) {
                return false;
            }
        } else { // Opening bracket
            stack.push(char);
        }
    }
    return stack.length === 0;
}

// Test Cases
const testCases = [
    "()",
    "()[]{}",
    "(]",
    "([)]",
    "{[]}",
    "((()))",
    "[{()}]",
    "}",
    "(",
    "}{",
    "((",
    "))",
    "())(",
    "((())",
    "((",
    "))"
];

// Run tests and log results
console.log("--- Stack Approach ---");
testCases.forEach(testCase => {
    console.log(`Input: ${testCase}, Output: ${isValidStack(testCase)}`);
});

console.log("\n--- Stack Approach with Early Exit ---");
testCases.forEach(testCase => {
    console.log(`Input: ${testCase}, Output: ${isValidStackEarlyExit(testCase)}`);
});

console.log("\n--- Recursive Approach ---");
testCases.forEach(testCase => {
    console.log(`Input: ${testCase}, Output: ${isValidRecursive(testCase)}`);
});

console.log("\n--- Replace and Check Approach ---");
testCases.forEach(testCase => {
    console.log(`Input: ${testCase}, Output: ${isValidReplace(testCase)}`);
});

console.log("\n--- Map and Single Loop Approach ---");
testCases.forEach(testCase => {
    console.log(`Input: ${testCase}, Output: ${isValidMap(testCase)}`);
});
