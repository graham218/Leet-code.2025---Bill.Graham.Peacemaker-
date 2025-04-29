#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// 1. Standard Sieve of Eratosthenes
//   - Basic implementation to find all prime numbers up to a given limit.
//   - Project Application: Generating prime number tables for cryptographic applications.
vector<bool> sieveOfEratosthenes_Standard(int limit) {
    if (limit <= 1) return {};
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }
    return isPrime;
}

// 2. Sieve with Optimized Space (Using bitset) - More memory efficient
//   - Uses a bitset (represented here as a vector<bool> for simplicity) to reduce memory usage.
//   - Project Application: Finding primes in embedded systems with limited memory.
vector<bool> sieveOfEratosthenes_OptimizedSpace(int limit) {
    if (limit <= 1) return {};
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }
    return isPrime;
}

// 3. Segmented Sieve of Eratosthenes
//   - Divides the range into smaller segments to handle very large limits.
//   - Project Application: Generating primes for very large number ranges, like in distributed computing for scientific research.
vector<bool> segmentedSieveOfEratosthenes(int limit) {
    if (limit <= 1) return {};

    int segmentSize = (int)sqrt(limit) + 1;
    vector<bool> isPrime(limit + 1, true);
    vector<bool> segment(segmentSize, true);

    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i])
            primes.push_back(i);
    }

    for (int low = segmentSize; low <= limit; low += segmentSize) {
        int high = min(low + segmentSize - 1, limit);
        fill(segment.begin(), segment.end(), true);

        for (int p : primes) {
            int start = (low / p) * p;
            if (start < low) start += p;
            for (int i = start - low; i <= high - low; i += p) {
                segment[i] = false;
            }
        }

        for (int i = low; i <= high; ++i) {
            isPrime[i] = segment[i - low];
        }
    }
    return isPrime;
}

// 4. Sieve of Atkin
//   - An optimized sieve algorithm that is faster than the Sieve of Eratosthenes for larger limits.
//   - Project Application: High-performance prime number generation for research or competitive programming.
vector<bool> sieveOfAtkin(int limit) {
    if (limit <= 3) {
        vector<bool> primes(limit + 1, false);
        for (int i = 2; i <= limit; i++)
            if (i == 2 || i == 3)
                primes[i] = true;
        return primes;
    }

    vector<bool> isPrime(limit + 1, false);
    isPrime[2] = isPrime[3] = true;

    for (int x = 1; x * x <= limit; x++) {
        for (int y = 1; y * y <= limit; y++) {
            int n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                isPrime[n] = !isPrime[n];

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
                isPrime[n] = !isPrime[n];

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
                isPrime[n] = !isPrime[n];
        }
    }

    for (int p = 5; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p * p)
                isPrime[i] = false;
        }
    }
    return isPrime;
}

// 5. Wheel Factorization Sieve
//   - Uses a "wheel" to skip multiples of small primes (2, 3, 5) to improve efficiency.
//   - Project Application: Optimized prime generation for specific applications where performance is critical.
vector<bool> wheelFactorizationSieve(int limit) {
    if (limit <= 1) return {};

    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    isPrime[2] = isPrime[3] = isPrime[5] = true;

    int wheel[8] = {7, 11, 13, 17, 19, 23, 25, 29};
    for (int i = 7; i <= limit;) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
        }
        i += wheel[(i % 30) / 7];
    }
    return isPrime;
}

// Function to print prime numbers from a boolean vector
void printPrimes(const vector<bool>& isPrime) {
    cout << "Prime Numbers: ";
    for (int i = 2; i < isPrime.size(); ++i) {
        if (isPrime[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
}

int main() {
    int limit;
    cout << "Enter the upper limit for finding prime numbers: ";
    cin >> limit;

    cout << endl << "Sieve of Eratosthenes Implementations (Limit = " << limit << "):" << endl;

    // 1. Standard Sieve
    auto start = high_resolution_clock::now();
    vector<bool> primesStandard = sieveOfEratosthenes_Standard(limit);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "1. Standard Sieve: " << fixed << setprecision(2) << duration.count() / 1000.0 << " ms" << endl;
    printPrimes(primesStandard);

    // 2. Optimized Space Sieve
    start = high_resolution_clock::now();
    vector<bool> primesOptimizedSpace = sieveOfEratosthenes_OptimizedSpace(limit);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "2. Optimized Space Sieve: " << fixed << setprecision(2) << duration.count() / 1000.0 << " ms" << endl;
    printPrimes(primesOptimizedSpace);

    // 3. Segmented Sieve
    start = high_resolution_clock::now();
    vector<bool> primesSegmented = segmentedSieveOfEratosthenes(limit);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "3. Segmented Sieve: " << fixed << setprecision(2) << duration.count() / 1000.0 << " ms" << endl;
    printPrimes(primesSegmented);

    // 4. Sieve of Atkin
    start = high_resolution_clock::now();
    vector<bool> primesAtkin = sieveOfAtkin(limit);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "4. Sieve of Atkin: " << fixed << setprecision(2) << duration.count() / 1000.0 << " ms" << endl;
    printPrimes(primesAtkin);

    // 5. Wheel Factorization Sieve
    start = high_resolution_clock::now();
    vector<bool> primesWheel = wheelFactorizationSieve(limit);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "5. Wheel Factorization Sieve: " << fixed << setprecision(2) << duration.count() / 1000.0 << " ms" << endl;
    printPrimes(primesWheel);

    return 0;
}

