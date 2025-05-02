#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric> // For std::accumulate

// Approach 1: Basic Rabin-Karp with a prime modulus
// This is the most straightforward implementation.  It's likely to have collisions
// (false positives) if the prime is not large enough, or the strings have
// certain patterns.
void rabinKarpBasic(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return;

    const int prime = 101; // A prime number for the modulus.  Often chosen to be large.
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1; // h is pow(prime, m-1) % prime
    std::cout << "(Basic) Pattern Hash: ";


    // Calculate h = prime^(m-1) % prime.  This is used for efficiently
    // removing the leading character's hash value.
    for (int i = 0; i < m - 1; i++){
        h = (h * prime) % prime;
        std::cout << h << " ";
    }
    std::cout << std::endl;

    // Calculate the hash value of pattern and the first window of text.
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
    }
     std::cout << "(Basic) Text Hash: " << textHash << std::endl;

    // Slide the window through the text.
    for (int i = 0; i <= n - m; i++) {
        // If the hash values match, check for a true match (to handle collisions).
        if (patternHash == textHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                std::cout << "Pattern found at index " << i << " (Basic)\n";
            }
        }
        // Calculate the hash value for the next window of text.
        if (i < n - m) {
            textHash = (textHash - text[i] * h + text[i + m]) % prime;
            // Ensure the hash value is non-negative.
            if (textHash < 0)
                textHash = (textHash + prime);
             std::cout << "(Basic) Text Hash: " << textHash << std::endl;
        }
    }
}

// Approach 2: Rabin-Karp with a larger prime modulus
//   This approach uses a larger prime number to reduce the probability of hash collisions.
//   Larger primes generally distribute the hash values more evenly.
void rabinKarpLargePrime(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return;

    const int prime = 1000000007; // A larger prime number
    long long patternHash = 0;
    long long textHash = 0;
    long long h = 1;
     std::cout << "(Large Prime) Pattern Hash: ";

    for (int i = 0; i < m - 1; i++){
        h = (h * prime) % prime;
        std::cout << h << " ";
    }
     std::cout << std::endl;

    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
    }
     std::cout << "(Large Prime) Text Hash: " << textHash << std::endl;

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
                std::cout << "Pattern found at index " << i << " (Large Prime)\n";
            }
        }
        if (i < n - m) {
            textHash = (textHash - text[i] * h + text[i + m]) % prime;
            if (textHash < 0)
                textHash = (textHash + prime);
             std::cout << "(Large Prime) Text Hash: " << textHash << std::endl;
        }
    }
}

// Approach 3: Rabin-Karp with double hashing
// To further reduce collisions, this approach uses two different hash functions (two different primes).
// A match is only considered valid if both hash values match.
void rabinKarpDoubleHash(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return;

    const int prime1 = 1000000007;
    const int prime2 = 1000000009; // Using two different large primes
    long long patternHash1 = 0, patternHash2 = 0;
    long long textHash1 = 0, textHash2 = 0;
    long long h1 = 1, h2 = 1;
    std::cout << "(Double Hash) Pattern Hash1: ";
    std::cout << "(Double Hash) Pattern Hash2: ";

    for (int i = 0; i < m - 1; i++) {
        h1 = (h1 * prime1) % prime1;
        h2 = (h2 * prime2) % prime2;
        std::cout << h1 << " ";
        std::cout << h2 << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < m; i++) {
        patternHash1 = (patternHash1 * prime1 + pattern[i]) % prime1;
        patternHash2 = (patternHash2 * prime2 + pattern[i]) % prime2;
        textHash1 = (textHash1 * prime1 + text[i]) % prime1;
        textHash2 = (textHash2 * prime2 + text[i]) % prime2;
    }
    std::cout << "(Double Hash) Text Hash1: " << textHash1 << std::endl;
    std::cout << "(Double Hash) Text Hash2: " << textHash2 << std::endl;

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
                std::cout << "Pattern found at index " << i << " (Double Hash)\n";
            }
        }
        if (i < n - m) {
            textHash1 = (textHash1 - text[i] * h1 + text[i + m]) % prime1;
            textHash2 = (textHash2 - text[i] * h2 + text[i + m]) % prime2;
            if (textHash1 < 0) textHash1 = (textHash1 + prime1);
            if (textHash2 < 0) textHash2 = (textHash2 + prime2);
             std::cout << "(Double Hash) Text Hash1: " << textHash1 << std::endl;
             std::cout << "(Double Hash) Text Hash2: " << textHash2 << std::endl;
        }
    }
}

// Approach 4: Rabin-Karp using rolling hash with unsigned long long
//      This approach attempts to reduce collisions by using unsigned long long,
//      which allows for larger hash values and reduces the need for explicit modulo operations.
//      It relies on the implicit modulo behavior of unsigned integer overflow.
void rabinKarpUnsignedLongLong(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return;

    const unsigned long long prime = 101;
    unsigned long long patternHash = 0;
    unsigned long long textHash = 0;
    unsigned long long h = 1;
    std::cout << "(Unsigned Long Long) Pattern Hash: ";

    for (int i = 0; i < m - 1; i++){
        h = h * prime;
        std::cout << h << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < m; i++) {
        patternHash = patternHash * prime + pattern[i];
        textHash = textHash * prime + text[i];
    }
    std::cout << "(Unsigned Long Long) Text Hash: " << textHash << std::endl;

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
                std::cout << "Pattern found at index " << i << " (Unsigned Long Long)\n";
            }
        }
        if (i < n - m) {
            textHash = textHash - text[i] * h + text[i + m];
             std::cout << "(Unsigned Long Long) Text Hash: " << textHash << std::endl;
        }
    }
}

// Approach 5: Rabin-Karp with precomputed powers of prime
// This approach precomputes the powers of the prime number to avoid redundant calculations
// within the loop.  This can improve performance, especially for larger patterns.
void rabinKarpPrecomputedPowers(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    if (m > n) return;

    const int prime = 101;
    long long patternHash = 0;
    long long textHash = 0;
    std::vector<long long> powers(m); // Array to store powers of prime
    std::cout << "(Precomputed Powers) Powers: ";

    // Precompute powers of prime modulo prime.
    powers[0] = 1;
    for (int i = 1; i < m; i++) {
        powers[i] = (powers[i - 1] * prime) % prime;
        std::cout << powers[i] << " ";
    }
    std::cout << std::endl;

    // Calculate hash values for pattern and initial text window
    for (int i = 0; i < m; i++) {
        patternHash = (patternHash * prime + pattern[i]) % prime;
        textHash = (textHash * prime + text[i]) % prime;
    }
    std::cout << "(Precomputed Powers) Text Hash: " << textHash << std::endl;

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
                std::cout << "Pattern found at index " << i << " (Precomputed Powers)\n";
            }
        }
        if (i < n - m) {
            textHash = (textHash - text[i] * powers[m - 1] + text[i + m]) % prime;
            if (textHash < 0)
                textHash = (textHash + prime);
            std::cout << "(Precomputed Powers) Text Hash: " << textHash << std::endl;
        }
    }
}

int main() {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABC";

    std::cout << "Text: " << text << "\n";
    std::cout << "Pattern: " << pattern << "\n\n";

    rabinKarpBasic(text, pattern);
    std::cout << std::endl;
    rabinKarpLargePrime(text, pattern);
     std::cout << std::endl;
    rabinKarpDoubleHash(text, pattern);
     std::cout << std::endl;
    rabinKarpUnsignedLongLong(text, pattern);
     std::cout << std::endl;
    rabinKarpPrecomputedPowers(text, pattern);

    return 0;
}
