import 'dart:math';
import 'package:collection/collection.dart'; // Import the collection package.

void main() {
  String text = "ABABDABACDABABCABAB";
  String pattern = "ABABCABAB";
  // String text = "GEEKS FOR GEEKS";
  // String pattern = "GEEK";

  print("Text: $text");
  print("Pattern: $pattern");

  // 1. Basic Rabin-Karp
  print("\n1. Basic Rabin-Karp:");
  List<int> basicResults = rabinKarpBasic(text, pattern);
  print("Pattern found at indices: $basicResults");

  // 2. Rabin-Karp with Prime Modulo
  print("\n2. Rabin-Karp with Prime Modulo:");
  List<int> primeModuloResults = rabinKarpPrimeModulo(text, pattern);
  print("Pattern found at indices: $primeModuloResults");

  // 3. Rabin-Karp with Rolling Hash Optimization
  print("\n3. Rabin-Karp with Rolling Hash Optimization:");
  List<int> rollingHashResults = rabinKarpRollingHash(text, pattern);
  print("Pattern found at indices: $rollingHashResults");

  // 4. Rabin-Karp with Custom Hash Function
  print("\n4. Rabin-Karp with Custom Hash Function:");
  List<int> customHashResults = rabinKarpCustomHash(text, pattern);
  print("Pattern found at indices: $customHashResults");

  // 5. Rabin-Karp with Multiple Hashes (Double Hashing)
  print("\n5. Rabin-Karp with Multiple Hashes (Double Hashing):");
  List<int> doubleHashResults = rabinKarpDoubleHash(text, pattern);
  print("Pattern found at indices: $doubleHashResults");

  // 6. Rabin-Karp with Large Input Optimization (Chunking)
  print("\n6. Rabin-Karp with Large Input Optimization (Chunking):");
  List<int> chunkedResults = rabinKarpChunked(text, pattern, chunkSize: 1024); // Example chunk size
  print("Pattern found at indices (Chunked): $chunkedResults");
}

// 1. Basic Rabin-Karp (Same as before)
List<int> rabinKarpBasic(String text, String pattern) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  int patternHash = pattern.hashCode;

  for (int i = 0; i <= n - m; i++) {
    String subText = text.substring(i, i + m);
    int subTextHash = subText.hashCode;
    if (subTextHash == patternHash) {
      if (subText == pattern) {
        results.add(i);
      }
    }
  }
  return results;
}

// 2. Rabin-Karp with Prime Modulo (Same as before)
List<int> rabinKarpPrimeModulo(String text, String pattern) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  int q = 101; // A prime number
  int d = 256; // Number of characters in the input alphabet
  int patternHash = 0;
  int textHash = 0;
  int h = 1;

  // Calculate h
  for (int i = 0; i < m - 1; i++) {
    h = (h * d) % q;
  }

  // Calculate initial hash values
  for (int i = 0; i < m; i++) {
    patternHash = (d * patternHash + pattern.codeUnitAt(i)) % q;
    textHash = (d * textHash + text.codeUnitAt(i)) % q;
  }

  // Slide the pattern over the text
  for (int i = 0; i <= n - m; i++) {
    // Check the hash values
    if (patternHash == textHash) {
      // Check for actual match
      if (text.substring(i, i + m) == pattern) {
        results.add(i);
      }
    }

    // Calculate hash value for the next window of text
    if (i < n - m) {
      textHash = ((d * (textHash - text.codeUnitAt(i) * h) + text.codeUnitAt(i + m))) % q;
      // Make sure textHash is non-negative
      if (textHash < 0) {
        textHash = (textHash + q);
      }
    }
  }
  return results;
}

// 3. Rabin-Karp with Rolling Hash Optimization (Same as before)
List<int> rabinKarpRollingHash(String text, String pattern) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  const int base = 256; // Or any suitable base
  const int modulus = 1000000007; // A large prime number for modulo

  // Calculate hash value of pattern and first window of text
  int patternHash = 0;
  int textHash = 0;
  for (int i = 0; i < m; i++) {
    patternHash = (patternHash * base + pattern.codeUnitAt(i)) % modulus;
    textHash = (textHash * base + text.codeUnitAt(i)) % modulus;
  }

  // Precompute base^(m-1) % modulus for efficient rolling hash calculation
  int h = 1;
  for (int i = 0; i < m - 1; i++) {
    h = (h * base) % modulus;
  }

  // Slide window through text
  for (int i = 0; i <= n - m; i++) {
    if (patternHash == textHash) {
      if (text.substring(i, i + m) == pattern) {
        results.add(i);
      }
    }
    if (i < n - m) {
      // Calculate next text hash using rolling hash
      textHash = (textHash - text.codeUnitAt(i) * h + text.codeUnitAt(i + m)) % modulus;
      textHash = (textHash * base) % modulus;
      if (textHash < 0) textHash += modulus; // Ensure non-negative
    }
  }
  return results;
}

// 4. Rabin-Karp with Custom Hash Function (Same as before)
int customHashFunction(String s, int modulus) {
  int hash = 0;
  for (int i = 0; i < s.length; i++) {
    hash = (hash * 31 + s.codeUnitAt(i)) % modulus; // Using 31 as a multiplier
  }
  return hash;
}

List<int> rabinKarpCustomHash(String text, String pattern) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  const int modulus = 1000000007;

  int patternHash = customHashFunction(pattern, modulus);
  int textHash = customHashFunction(text.substring(0, m), modulus);
  int h = 1;
  for (int i = 0; i < m - 1; ++i) {
    h = (h * 31) % modulus;
  }

  for (int i = 0; i <= n - m; i++) {
    if (patternHash == textHash) {
      if (text.substring(i, i + m) == pattern) {
        results.add(i);
      }
    }
    if (i < n - m) {
      textHash = (textHash - text.codeUnitAt(i) * h + text.codeUnitAt(i + m)) % modulus;
      textHash = (textHash * 31) % modulus;
      if (textHash < 0) textHash += modulus;
    }
  }
  return results;
}

// 5. Rabin-Karp with Multiple Hashes (Double Hashing) (Same as before)
List<int> rabinKarpDoubleHash(String text, String pattern) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  const int modulus1 = 1000000007;
  const int modulus2 = 1000000009;
  const int base = 256;

  int patternHash1 = 0;
  int patternHash2 = 0;
  int textHash1 = 0;
  int textHash2 = 0;
  int h1 = 1;
  int h2 = 1;

  for (int i = 0; i < m - 1; ++i) {
    h1 = (h1 * base) % modulus1;
    h2 = (h2 * base) % modulus2;
  }

  for (int i = 0; i < m; i++) {
    patternHash1 = (patternHash1 * base + pattern.codeUnitAt(i)) % modulus1;
    patternHash2 = (patternHash2 * base + pattern.codeUnitAt(i)) % modulus2;
    textHash1 = (textHash1 * base + text.codeUnitAt(i)) % modulus1;
    textHash2 = (textHash2 * base + text.codeUnitAt(i)) % modulus2;
  }

  for (int i = 0; i <= n - m; i++) {
    if (patternHash1 == textHash1 && patternHash2 == textHash2) {
      if (text.substring(i, i + m) == pattern) {
        results.add(i);
      }
    }
    if (i < n - m) {
      textHash1 = (textHash1 - text.codeUnitAt(i) * h1 + text.codeUnitAt(i + m)) % modulus1;
      textHash1 = (textHash1 * base) % modulus1;
      if (textHash1 < 0) textHash1 += modulus1;

      textHash2 = (textHash2 - text.codeUnitAt(i) * h2 + text.codeUnitAt(i + m)) % modulus2;
      textHash2 = (textHash2 * base) % modulus2;
      if (textHash2 < 0) textHash2 += modulus2;
    }
  }
  return results;
}

// 6. Rabin-Karp with Large Input Optimization (Chunking)
List<int> rabinKarpChunked(String text, String pattern, {required int chunkSize}) {
  List<int> results = [];
  int n = text.length;
  int m = pattern.length;
  const int base = 256;
  const int modulus = 1000000007;

  int patternHash = 0;
  for (int i = 0; i < m; i++) {
    patternHash = (patternHash * base + pattern.codeUnitAt(i)) % modulus;
  }

  int h = 1;
  for (int i = 0; i < m - 1; i++) {
    h = (h * base) % modulus;
  }

  for (int i = 0; i < n; i += chunkSize) {
    int end = min(i + chunkSize, n);
    String chunk = text.substring(i, end);
    int chunkLength = chunk.length;

    if (chunkLength < m) continue; // Skip if chunk is smaller than pattern

    int textHash = 0;
    for (int j = 0; j < m; j++) {
      textHash = (textHash * base + chunk.codeUnitAt(j)) % modulus;
    }

    for (int j = 0; j <= chunkLength - m; j++) {
      if (patternHash == textHash) {
        if (chunk.substring(j, j + m) == pattern) {
          results.add(i + j); // Add the absolute index in the text
        }
      }
      if (j < chunkLength - m) {
        textHash = (textHash - chunk.codeUnitAt(j) * h + chunk.codeUnitAt(j + m)) % modulus;
        textHash = (textHash * base) % modulus;
        if (textHash < 0) textHash += modulus;
      }
    }
  }
  return results;
}
