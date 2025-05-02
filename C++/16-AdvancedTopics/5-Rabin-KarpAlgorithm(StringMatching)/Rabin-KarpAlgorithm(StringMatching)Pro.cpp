#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

// Approach 1: Basic Rabin-Karp with a single prime modulus
// This is the most straightforward implementation, suitable for smaller texts and patterns.
// It's easy to understand but has a higher chance of spurious hits (false matches).
int rabinKarpBasic(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return -1; // Pattern cannot be longer than text

    const int prime = 101; // A prime number for hashing
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1; // h = prime^(m-1)

    // Calculate hash value for pattern and first window of text
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
        if (i < m - 1)
            h = (h * prime) % prime;
    }

    // Slide the window through the text
    for (int i = 0; i <= n - m; i++) {
        // Check if the hash values match
        if (patternHash == textHash) {
            // Potential match: Verify character by character to avoid spurious hits
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i; // Return the starting index of the match
            }
        }

        // Calculate hash value for the next window of text
        if (i < n - m) {
            textHash = ((textHash - text[i] * h) * prime + text[i + m]) % prime;
            if (textHash < 0) textHash += prime; // Ensure non-negative hash value
        }
    }

    return -1; // No match found
}

// Approach 2: Rabin-Karp with a larger prime modulus
//   - Uses a larger prime number to reduce the probability of spurious hits.
//   - Suitable for medium-sized texts and patterns where a lower collision rate is desired.
int rabinKarpLargePrime(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return -1;

    const long long prime = 1000000007; // A larger prime number
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1;

    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
        if (i < m - 1)
            h = (h * prime) % prime;
    }

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        if (i < n - m) {
            textHash = ((textHash - text[i] * h) * prime + text[i + m]) % prime;
            if (textHash < 0) textHash += prime;
        }
    }
    return -1;
}

// Approach 3: Rabin-Karp with multiple prime moduli (Double Hashing)
//   - Uses two different prime numbers for hashing to significantly reduce the chance of collisions.
//   - This approach is very effective in minimizing spurious hits, making it suitable for larger texts and patterns.
//   - It adds a bit more computational overhead but provides much better accuracy.
int rabinKarpDoubleHash(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return -1;

    const long long prime1 = 1000000007;
    const long long prime2 = 1000000009; // Using two different primes
    long long patternHash1 = 0, patternHash2 = 0;
    long long textHash1 = 0, textHash2 = 0;
    long long h1 = 1, h2 = 1;

    for (int i = 0; i < m; i++) {
        patternHash1 = (patternHash1 * prime1 + pattern[i]) % prime1;
        patternHash2 = (patternHash2 * prime2 + pattern[i]) % prime2;
        textHash1 = (textHash1 * prime1 + text[i]) % prime1;
        textHash2 = (textHash2 * prime2 + text[i]) % prime2;
        if (i < m - 1) {
            h1 = (h1 * prime1) % prime1;
            h2 = (h2 * prime2) % prime2;
        }
    }

    for (int i = 0; i <= n - m; i++) {
        if (patternHash1 == textHash1 && patternHash2 == textHash2) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        if (i < n - m) {
            textHash1 = ((textHash1 - text[i] * h1) * prime1 + text[i + m]) % prime1;
            textHash2 = ((textHash2 - text[i] * h2) * prime2 + text[i + m]) % prime2;
            if (textHash1 < 0) textHash1 += prime1;
            if (textHash2 < 0) textHash2 += prime2;
        }
    }
    return -1;
}

// Approach 4: Rabin-Karp with rolling hash optimization (for long texts)
//  - This approach precomputes the powers of the prime modulus to optimize the rolling hash calculation.
//  - This optimization can be significant for very long texts, as it avoids redundant calculations within the loop.
std::vector<long long> precomputePowers(int m, long long prime) {
    std::vector<long long> powers(m);
    powers[0] = 1;
    for (int i = 1; i < m; ++i) {
        powers[i] = (powers[i - 1] * prime) % prime;
    }
    return powers;
}

int rabinKarpOptimized(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return -1;

    const long long prime = 1000000007;
    long long patternHash = 0;
    long long textHash = 0;

    // Precompute powers of prime
    std::vector<long long> powers = precomputePowers(m, prime);

    // Calculate hash value for pattern and first window of text
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
    }

    // Slide the window through the text
    for (int i = 0; i <= n - m; i++) {
        // Check if the hash values match
        if (patternHash == textHash) {
            // Potential match: Verify character by character to avoid spurious hits
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i; // Return the starting index of the match
            }
        }

        // Calculate hash value for the next window of text
        if (i < n - m) {
            textHash = ((textHash - text[i] * powers[m - 1]) * prime + text[i + m]) % prime;
            if (textHash < 0) textHash += prime; // Ensure non-negative hash value
        }
    }

    return -1; // No match found
}

// Approach 5: Rabin-Karp with string view (C++17 and later)
// Uses string_view for more efficient string handling (avoids unnecessary copying).
#ifdef __cpp_lib_string_view
#include <string_view>
int rabinKarpStringView(std::string_view text, std::string_view pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return -1;

    const int prime = 101;
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1;

    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
        if (i < m - 1)
            h = (h * prime) % prime;
    }

    for (int i = 0; i <= n - m; i++) {
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        if (i < n - m) {
            textHash = ((textHash - text[i] * h) * prime + text[i + m]) % prime;
            if (textHash < 0) textHash += prime;
        }
    }
    return -1;
}
#endif

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::cout << "Text: " << text << std::endl;
    std::cout << "Pattern: " << pattern << std::endl;
    std::cout << std::endl;

    // Approach 1: Basic Rabin-Karp
    int index1 = rabinKarpBasic(text, pattern);
    std::cout << "Approach 1 (Basic): ";
    if (index1 != -1) {
        std::cout << "Pattern found at index " << index1 << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    // Approach 2: Rabin-Karp with a larger prime modulus
    int index2 = rabinKarpLargePrime(text, pattern);
    std::cout << "Approach 2 (Large Prime): ";
    if (index2 != -1) {
        std::cout << "Pattern found at index " << index2 << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    // Approach 3: Rabin-Karp with multiple prime moduli
    int index3 = rabinKarpDoubleHash(text, pattern);
    std::cout << "Approach 3 (Double Hash): ";
    if (index3 != -1) {
        std::cout << "Pattern found at index " << index3 << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    // Approach 4: Rabin-Karp with rolling hash optimization
    int index4 = rabinKarpOptimized(text, pattern);
    std::cout << "Approach 4 (Optimized): ";
    if (index4 != -1) {
        std::cout << "Pattern found at index " << index4 << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    // Approach 5: Rabin-Karp with string view
#ifdef __cpp_lib_string_view
    int index5 = rabinKarpStringView(text, pattern);
    std::cout << "Approach 5 (String View): ";
    if (index5 != -1) {
        std::cout << "Pattern found at index " << index5 << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }
#endif

    return 0;
}

