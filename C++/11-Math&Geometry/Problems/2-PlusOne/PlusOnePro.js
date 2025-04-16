/**
 * Plus One - Multiple Solution Approaches
 *
 * Problem: Given a non-empty array of digits representing a non-negative integer,
 * increment the integer by one and return the resulting array of digits.
 */

// Test cases
const testCases = [
    [1, 2, 3],
    [4, 3, 2, 1],
    [9],
    [9, 9, 9],
    [6, 1, 4, 5, 3, 9, 0, 1, 9, 5, 1, 8, 6, 7, 0, 5, 5, 4, 3]
];

// Utility function to display results
function displayResult(approachName, input, output) {
    console.log(`${approachName}:`);
    console.log(`Input:  [${input.join(', ')}]`);
    console.log(`Output: [${output.join(', ')}]`);
    console.log('-----------------------------------');
}

// Approach 1: Iterative
function plusOneIterative(digits) {
    const n = digits.length;
    for (let i = n - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    return [1, ...digits];
}

// Approach 2: Recursive
function plusOneRecursive(digits, index = digits.length - 1) {
    if (index < 0) {
        return [1, ...digits];
    }
    if (digits[index] < 9) {
        digits[index]++;
        return digits;
    }
    digits[index] = 0;
    return plusOneRecursive(digits, index - 1);
}

// Approach 3: Using BigInt (Handles large integers)
function plusOneBigInt(digits) {
    const numStr = digits.join('');
    const bigNum = BigInt(numStr) + 1n;
    return String(bigNum).split('').map(Number);
}

// Approach 4: Functional with Reduce
function plusOneFunctional(digits) {
    const { result, carry } = digits.reduceRight(
        (acc, digit) => {
            const sum = digit + acc.carry;
            acc.result.unshift(sum % 10);
            acc.carry = Math.floor(sum / 10);
            return acc;
        },
        { result: [], carry: 1 }
    );
    return carry ? [carry, ...result] : result;
}

// Approach 5: String Conversion (Limited by Number.MAX_SAFE_INTEGER)
function plusOneStringConversion(digits) {
    const num = parseInt(digits.join(''), 10);
    const incrementedNum = num + 1;
    return String(incrementedNum).split('').map(Number);
}

// Running all approaches on test cases
function runAllApproaches() {
    testCases.forEach((testCase, index) => {
        console.log(`\nTest Case ${index + 1}:`);

        // Approach 1
        const result1 = plusOneIterative([...testCase]);
        displayResult('1. Iterative', testCase, result1);

        // Approach 2
        const result2 = plusOneRecursive([...testCase]);
        displayResult('2. Recursive', testCase, result2);

        // Approach 3
        const result3 = plusOneBigInt([...testCase]);
        displayResult('3. BigInt', testCase, result3);

        // Approach 4
        const result4 = plusOneFunctional([...testCase]);
        displayResult('4. Functional (Reduce)', testCase, result4);

        // Approach 5
        if (testCase.length <= 15) { // Heuristic to avoid potential precision issues for very long numbers
            const result5 = plusOneStringConversion([...testCase]);
            displayResult('5. String Conversion', testCase, result5);
        } else {
            console.log('5. String Conversion: Skipped for potentially unsafe integer conversion');
            console.log('-----------------------------------');
        }
    });
}

// Execute all approaches
runAllApproaches();