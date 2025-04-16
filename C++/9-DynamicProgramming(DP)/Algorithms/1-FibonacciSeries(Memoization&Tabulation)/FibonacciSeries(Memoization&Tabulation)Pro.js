// 1. Fibonacci Series - Memoization (Top-Down) - Basic
//    - Using a simple object (cache) for memoization

function fibonacciMemoizationBasic(n, cache = {}) {
  if (n <= 1) return n;
  if (cache[n]) return cache[n];
  cache[n] = fibonacciMemoizationBasic(n - 1, cache) + fibonacciMemoizationBasic(n - 2, cache);
  return cache[n];
}

// 2. Fibonacci Series - Memoization (Top-Down) - Using Map
//    - Using a Map for memoization, which is slightly more performant for larger datasets
function fibonacciMemoizationMap(n, memo = new Map()) {
  if (n <= 1) return n;
  if (memo.has(n)) return memo.get(n);
  const result = fibonacciMemoizationMap(n - 1, memo) + fibonacciMemoizationMap(n - 2, memo);
  memo.set(n, result);
  return result;
}

// 3. Fibonacci Series - Tabulation (Bottom-Up) - Basic
//    - Iterative approach using an array

function fibonacciTabulationBasic(n) {
  if (n <= 1) return n;
  const table = [0, 1];
  for (let i = 2; i <= n; i++) {
    table[i] = table[i - 1] + table[i - 2];
  }
  return table[n];
}

// 4. Fibonacci Series - Tabulation (Bottom-Up) - Optimized Space
//    - Iterative approach using only two variables (space optimization)

function fibonacciTabulationOptimized(n) {
  if (n <= 1) return n;
  let a = 0, b = 1;
  for (let i = 2; i <= n; i++) {
    const next = a + b;
    a = b;
    b = next;
  }
  return b;
}

// 5. Fibonacci Series - Memoization -  Real-World Project Implementation: Caching Expensive API Responses
// In a real-world scenario, you might use memoization to cache the results of expensive API calls that return Fibonacci-like sequences.
// For example, consider an API that calculates compound interest over time, which follows a Fibonacci-like pattern.

const compoundInterestCache = new Map(); // Use a Map for the cache

async function getCompoundInterest(principal, rate, years) {
    const key = `${principal}-${rate}-${years}`;
    if (compoundInterestCache.has(key)) {
        console.log(`[CACHE HIT] Compound Interest for ${principal} at ${rate}% over ${years} years`);
        return compoundInterestCache.get(key);
    }

    // Simulate an expensive API call with a delay
    await new Promise(resolve => setTimeout(resolve, 500)); // Simulate 500ms delay

    // Compound interest calculation (simplified for demonstration)
    let amount = principal * Math.pow(1 + rate, years);
    amount = parseFloat(amount.toFixed(2)); // consistent formatting
    console.log(`[API CALL] Calculating Compound Interest for ${principal} at ${rate}% over ${years} years. Result: ${amount}`);
    compoundInterestCache.set(key, amount);
    return amount;
}

// Driver function to demonstrate the Fibonacci implementations and the compound interest caching
async function runFibonacciExamples() {
    console.log("Fibonacci Series Examples:");
    console.log("--------------------------");

    const n = 10;
    console.log(`Fibonacci(${n}) - Memoization (Basic):`, fibonacciMemoizationBasic(n));
    console.log(`Fibonacci(${n}) - Memoization (Map):`, fibonacciMemoizationMap(n));
    console.log(`Fibonacci(${n}) - Tabulation (Basic):`, fibonacciTabulationBasic(n));
    console.log(`Fibonacci(${n}) - Tabulation (Optimized):`, fibonacciTabulationOptimized(n));

    console.log("\nReal-World Example: Caching Compound Interest");
    console.log("---------------------------------------------");

    // Example usage of the compound interest function
    const principal = 1000;
    const rate = 0.05; // 5%
    const years = 5;

    // First call: API call is made and result is cached
    const result1 = await getCompoundInterest(principal, rate, years);
    console.log("Result 1:", result1);

    // Second call with the same parameters: Result is retrieved from the cache
    const result2 = await getCompoundInterest(principal, rate, years);
    console.log("Result 2:", result2);

    // Third call with different parameters
    const result3 = await getCompoundInterest(2000, 0.06, 7);
    console.log("Result 3:", result3);

    // Fourth call with same parameter as third call: Result is retrieved from cache
    const result4 = await getCompoundInterest(2000, 0.06, 7);
    console.log("Result 4:", result4);
}

// Run the examples
runFibonacciExamples();
