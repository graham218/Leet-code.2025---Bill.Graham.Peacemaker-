/**
 * Sieve of Eratosthenes - Five Implementations
 * ----------------------------------------
 *
 * This code demonstrates five different implementations of the Sieve of Eratosthenes algorithm
 * for finding prime numbers up to a given limit. Each implementation is tailored to a
 * specific real-world project scenario.
 */

/**
 * 1. Basic Sieve of Eratosthenes
 *
 * - Description:  The most straightforward implementation.  Good for understanding
 * the core algorithm.
 * - Application:  Educational tool for demonstrating prime number generation.
 */
function basicSieve(limit) {
    if (limit <= 1) return [];

    const isPrime = new Array(limit + 1).fill(true);
    isPrime[0] = isPrime[1] = false;

    for (let p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (let i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    const primes = [];
    for (let i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push(i);
        }
    }
    return primes;
}

// Example Usage:
const basicPrimes = basicSieve(100);
console.log("1. Basic Sieve (Educational Tool):", basicPrimes);


/**
 * 2. Sieve with Bit Array Optimization
 *
 * - Description:  Uses a bit array to reduce memory usage.  Each bit represents a number.
 * - Application:  Finding primes in embedded systems with limited memory.
 */
function sieveWithBitArray(limit) {
    if (limit <= 1) return [];

    const numBits = Math.ceil((limit + 1) / 32);
    const bitArray = new Uint32Array(numBits);

    // Helper functions to set and check bits
    const setBit = (arr, n) => {
        const wordIndex = Math.floor(n / 32);
        const bitIndex = n % 32;
        arr[wordIndex] |= (1 << bitIndex);
    };

    const checkBit = (arr, n) => {
        const wordIndex = Math.floor(n / 32);
        const bitIndex = n % 32;
        return (arr[wordIndex] & (1 << bitIndex)) !== 0;
    };

    // Initialize all bits to 1 (prime)
    for (let i = 0; i < numBits; i++) {
        bitArray[i] = 0xFFFFFFFF; // Set all 32 bits to 1
    }
    setBit(bitArray, 0); // 0 is not prime
    setBit(bitArray, 1); // 1 is not prime

    for (let p = 2; p * p <= limit; p++) {
        if (checkBit(bitArray, p)) {
            for (let i = p * p; i <= limit; i += p) {
                setBit(bitArray, i);
            }
        }
    }

    const primes = [];
    for (let i = 2; i <= limit; i++) {
        if (checkBit(bitArray, i)) {
            primes.push(i);
        }
    }
    return primes;
}

// Example Usage:
const bitArrayPrimes = sieveWithBitArray(100);
console.log("2. Sieve with Bit Array (Embedded System):", bitArrayPrimes);


/**
 * 3. Segmented Sieve
 *
 * - Description: Divides the range into smaller segments to reduce memory usage.
 * - Application: Finding primes in very large ranges, such as in cryptographic applications.
 */
function segmentedSieve(limit) {
    if (limit <= 1) return [];
    const segmentSize = Math.floor(Math.sqrt(limit));
    const primes = [];
    const firstSegmentPrimes = basicSieve(segmentSize); // Use basic sieve for first segment

    for (let i = 0; i * segmentSize <= limit; i++) {
        const low = i * segmentSize;
        const high = Math.min((i + 1) * segmentSize - 1, limit);
        const isPrime = new Array(high - low + 1).fill(true);

        for (const p of firstSegmentPrimes) {
            let start = Math.max(p * p, Math.ceil(low / p) * p);
            for (let j = start - low; j <= high - low; j += p) {
                isPrime[j] = false;
            }
        }

        for (let j = low; j <= high; j++) {
            if (isPrime[j - low]) {
                primes.push(j);
            }
        }
    }
    return primes;
}

// Example Usage:
const segmentedPrimes = segmentedSieve(1000);
console.log("3. Segmented Sieve (Large Range):", segmentedPrimes.slice(0, 50), "..."); // Print only the first 50


/**
 * 4. Sieve with Wheel Factorization (Wheel 6)
 *
 * - Description: Uses a "wheel" to skip multiples of small primes (2, 3) to improve efficiency.
 * - Application:  Optimized prime generation for number theory research.
 */
function sieveWithWheel6(limit) {
    if (limit <= 1) return [];

    const primes = [2, 3]; // Initial primes
    const isPrime = new Array(Math.floor((limit - 1) / 6) + 1).fill(true);

    for (let i = 5, w = 2; i * i <= limit; w = 6 - w, i += w) {
        if (isPrime[Math.floor((i - 1) / 6)]) {
            for (let j = i * i, step = w; j <= limit; step = 6 - step, j += step * i) {
                isPrime[Math.floor((j - 1) / 6)] = false;
            }
        }
    }

    for (let i = 5, w = 2; i <= limit; w = 6 - w, i += w) {
        if (isPrime[Math.floor((i - 1) / 6)]) {
            primes.push(i);
        }
    }
    return primes;
}

// Example Usage:
const wheel6Primes = sieveWithWheel6(200);
console.log("4. Sieve with Wheel 6 (Number Theory):", wheel6Primes);


/**
 * 5. Sieve with Incremental Sieving
 *
 * - Description:  Generates primes in chunks and combines the results. Useful for
 * applications where primes are needed in a streaming fashion.
 * - Application:  Generating prime numbers for a real-time game or simulation.
 */
function incrementalSieve(limit, callback) {
     if (limit <= 1) return [];

    const segmentSize = 1000; // Tune this based on performance
    let currentStart = 2;

    while (currentStart <= limit) {
        const currentEnd = Math.min(currentStart + segmentSize - 1, limit);
        const isPrime = new Array(currentEnd - currentStart + 1).fill(true);

        for (let p = 2; p * p <= currentEnd; p++) {
            if(p >= currentStart){
               let start = p * p;
               for (let i = start - currentStart; i <= currentEnd - currentStart; i += p) {
                    isPrime[i] = false;
                }
            }
            else{
                let start = Math.ceil(currentStart / p) * p;
                 for (let i = start - currentStart; i <= currentEnd - currentStart; i += p) {
                    isPrime[i] = false;
                }
            }

        }

        for (let i = currentStart; i <= currentEnd; i++) {
            if (isPrime[i - currentStart]) {
                callback(i); // Send prime to callback
            }
        }
        currentStart = currentEnd + 1;
    }
}
// Example Usage:
const incrementalPrimes = [];
incrementalSieve(150, (prime) => {
    incrementalPrimes.push(prime);
});
console.log("5. Incremental Sieve (Real-time Game):", incrementalPrimes);
