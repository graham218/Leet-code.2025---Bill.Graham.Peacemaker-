/**
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 *
 * An input string is valid if:
 *
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 *
 *
 * Example 1:
 *
 * Input: s = "()"
 * Output: true
 *
 * Example 2:
 *
 * Input: s = "()[]{}"
 * Output: true
 *
 * Example 3:
 *
 * Input: s = "(]"
 * Output: false
 *
 *
 * Constraints:
 *
 * 1 <= s.length <= 104
 * s consists of parentheses only '()[]{}'.
 */

/**
 * Approach 1: Using Stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function isValidWithStack(s) {
    const stack = [];
    const mapping = {
        ')': '(',
        '}': '{',
        ']': '['
    };

    for (let char of s) {
        if (mapping[char]) { // If it's a closing bracket
            const topElement = stack.pop() || '#'; // Use '#' as a dummy if stack is empty
            if (topElement !== mapping[char]) {
                return false;
            }
        } else { // If it's an opening bracket
            stack.push(char);
        }
    }

    return stack.length === 0;
}

/**
 * Approach 2: Using Stack (optimized) - slightly faster in some engines
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function isValidWithStackOptimized(s) {
    const stack = [];
    for (let i = 0; i < s.length; i++) {
        const c = s[i];
        if (c === '(' || c === '{' || c === '[') {
            stack.push(c);
        } else {
            if (!stack.length) return false; //stack is empty but it is a closing bracket
            const top = stack.pop();
            if (
                (c === ')' && top !== '(') ||
                (c === '}' && top !== '{') ||
                (c === ']' && top !== '[')
            ) {
                return false;
            }
        }
    }
    return !stack.length;
}

/**
 * Approach 3: Using Recursion (Less efficient, for demonstration)
 * Time Complexity: O(n^2) in worst case (due to string slicing)
 * Space Complexity: O(n) (due to recursion depth)
 */
function isValidRecursive(s) {
    if (s.length === 0) return true;

    for (let i = 0; i < s.length - 1; i++) {
        if (
            (s[i] === '(' && s[i + 1] === ')') ||
            (s[i] === '{' && s[i + 1] === '}') ||
            (s[i] === '[' && s[i + 1] === ']')
        ) {
            return isValidRecursive(s.substring(0, i) + s.substring(i + 2));
        }
    }
    return false;
}

/**
 * Approach 4: Iterative Replacement (Inefficient, for demonstration)
 * Time Complexity: O(n^2) in worst case
 * Space Complexity: O(1)
 */
function isValidReplace(s) {
    let previousLength = s.length;
    while (s.length > 0) {
        s = s.replace("()", "").replace("{}", "").replace("[]", "");
        if (s.length === previousLength) {
            break; // No replacements were made
        }
        previousLength = s.length;
    }
    return s.length === 0;
}

/**
 * Approach 5: Using a Map and a Stack
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
function isValidWithMap(s) {
    const map = new Map([
        [')', '('],
        ['}', '{'],
        [']', '[']
    ]);
    const stack = [];

    for (let char of s) {
        if (map.has(char)) {
            const topElement = stack.pop() || '#';
            if (topElement !== map.get(char)) {
                return false;
            }
        } else {
            stack.push(char);
        }
    }

    return stack.length === 0;
}

// Test cases
const testCases = [
    "()",
    "()[]{}",
    "(]",
    "([)]",
    "{[]}",
    "",
    "{{{{",
    "}}}}",
    "(){}}{",
    "((()))"
];

console.log("Valid Parentheses - Test Cases:");
testCases.forEach((testCase, index) => {
    console.log(`\nTest Case ${index + 1}: s = "${testCase}"`);
    console.log(`isValidWithStack: ${isValidWithStack(testCase)}`);
    console.log(`isValidWithStackOptimized: ${isValidWithStackOptimized(testCase)}`);
    console.log(`isValidRecursive: ${isValidRecursive(testCase)}`);
    console.log(`isValidReplace: ${isValidReplace(testCase)}`);
    console.log(`isValidWithMap: ${isValidWithMap(testCase)}`);
});
