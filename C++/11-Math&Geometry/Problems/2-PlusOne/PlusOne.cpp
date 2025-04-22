// Approach 1: Simple Iteration from End
function plusOneIterative(digits) {
    for (let i = digits.length - 1; i >= 0; i--) {
        if (digits[i] < 9) {
            digits[i]++;
            return digits;
        }
        digits[i] = 0;
    }
    return [1, ...digits];
}

// Approach 2: Recursive Solution
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

// Approach 3: Using BigInt for Very Large Numbers
function plusOneBigInt(digits) {
    const numStr = digits.join('');
    const bigNum = BigInt(numStr) + BigInt(1);
    return bigNum.toString().split('').map(Number);
}

// Approach 4: Using Array Join and Split
function plusOneJoinSplit(digits) {
    let num = parseInt(digits.join('')) + 1;
    return num.toString().split('').map(Number);
}

// Approach 5: Using Reduce Right
function plusOneReduceRight(digits) {
    return digits.reduceRight((acc, digit, index) => {
        if (digit === 9) {
            acc[index] = 0;
            if (index === 0) {
                acc.unshift(1);
            }
        } else {
            acc[index]++;
            return acc;
        }
        return acc;
    }, [...digits]);
}

// Test Cases
const testCases = [
    [1, 2, 3],
    [4, 3, 2, 1],
    [9],
    [9, 9, 9],
    [6, 1, 4, 5, 3, 9, 0, 1, 9, 5, 1, 8, 6, 7, 0, 5, 5, 4, 3]
];

// Display results for all approaches
console.log("Plus One Problem - 5 Different Approaches\n");

testCases.forEach((testCase, i) => {
    console.log(`Test Case ${i + 1}: [${testCase}]`);

    const result1 = plusOneIterative([...testCase]);
    console.log(`Approach 1 (Iterative): [${result1}]`);

    const result2 = plusOneRecursive([...testCase]);
    console.log(`Approach 2 (Recursive): [${result2}]`);

    // Skip BigInt for very large arrays to avoid performance issues in console
    if (testCase.length < 15) {
        const result3 = plusOneBigInt([...testCase]);
        console.log(`Approach 3 (BigInt):   [${result3}]`);
    } else {
        console.log(`Approach 3 (BigInt):   Skipped for large array`);
    }

    // Skip join/split for very large numbers to avoid precision loss
    if (testCase.length < 15) {
        const result4 = plusOneJoinSplit([...testCase]);
        console.log(`Approach 4 (Join/Split): [${result4}]`);
    } else {
        console.log(`Approach 4 (Join/Split): Skipped for large array (precision loss)`);
    }

    const result5 = plusOneReduceRight([...testCase]);
    console.log(`Approach 5 (ReduceRight): [${result5}]`);

    console.log('-'.repeat(50));
});