// import 'dart:io';
import 'dart:math';
import 'package:collection/collection.dart'; // Import the collection package

void main() {
  String text = "GEEKS FOR GEEKS FOR GEEKS";
  String pattern = "GEEKS";

  // 1. Suffix Array for Genome Sequence Analysis (Real-world)
  print("1. Suffix Array for Genome Sequence Analysis:");
  String genome = "AGCTAGCTAGCTAGCTAGCTAGCT"; // Example genome sequence
  List<int> suffixArrayGenome = buildSuffixArrayDartSort(genome);
  print("   Suffix Array: $suffixArrayGenome");

  // Simulate finding a specific gene sequence (pattern)
  String geneSequence = "AGCTA";
  List<int> geneOccurrences =
  findPatternBinarySearch(genome, geneSequence, suffixArrayGenome);
  print("   Gene '$geneSequence' occurrences: $geneOccurrences");

  // 2. Suffix Array for Text Indexing in Search Engines (Real-world)
  print("\n2. Suffix Array for Text Indexing:");
  String document =
      "This is a sample document. We want to index this document for fast searching.";
  List<int> suffixArraySearchEngine = buildSuffixArrayDartSort(document);
  print("   Suffix Array: $suffixArraySearchEngine");

  // Simulate a simple search query
  String query = "document";
  List<int> queryOccurrences =
  findPatternBinarySearch(document, query, suffixArraySearchEngine);
  print("   Query '$query' occurrences: $queryOccurrences");

  // 3. Z-Algorithm for Intrusion Detection (Real-world)
  print("\n3. Z-Algorithm for Intrusion Detection:");
  String networkTraffic =
      "GET /index.html HTTP/1.1 200 OK\nPOST /login.php HTTP/1.1 302 Found\nGET /index.html HTTP/1.1 200 OK\nGET /flag.txt HTTP/1.1 403 Forbidden";
  String signature = "GET /flag.txt"; // An attack signature
  List<int> intrusionAlerts = findPatternZAlgorithm(networkTraffic, signature);
  if (intrusionAlerts.isNotEmpty) {
    print("   Intrusion detected! Signature '$signature' found at indices: $intrusionAlerts");
  } else {
    print("   No intrusion detected for signature '$signature'.");
  }

  // 4. Suffix Array for Longest Repeated Substring (Real-world - Bioinformatics)
  print("\n4. Suffix Array for Longest Repeated Substring:");
  String dnaSequence = "ATAGATAGATAGCTAG";
  String longestRepeat =
  findLongestRepeatedSubstring(dnaSequence); // Using Suffix Array
  print("   Longest repeated substring: $longestRepeat");

  // 5. Z-Algorithm for Data Compression (Real-world - variation)
  print("\n5. Z-Algorithm for Data Compression (Simplified):");
  String data = "ABABABABCB";
  List<int> zArrayCompression = calculateZArray(data);
  print("   Z-Array: $zArrayCompression");
  String compressedData =
  compressData(data, zArrayCompression); //basic compression
  print("   Compressed Data: $compressedData");
  String decompressedData = decompressData(
      compressedData); // very basic decompression for demo only.
  print("   Decompressed Data: $decompressedData");

  // 6. Suffix Array for Plagiarism Detection (Real-world)
  print("\n6. Suffix Array for Plagiarism Detection:");
  String text1 =
      "The quick brown fox jumps over the lazy dog. This is a sample text.";
  String text2 =
      "A quick brown fox jumps over the lazy dog.  This is sample text.";
  double similarity =
  calculateTextSimilarity(text1, text2); // Using Suffix Array
  print("   Similarity between text1 and text2: ${similarity.toStringAsFixed(2)}");
}

// 1. Suffix Array for Genome Sequence Analysis
// (Uses the optimized Dart's sort version)

// 2. Suffix Array for Text Indexing in Search Engines
// (Uses the optimized Dart's sort version)

// 3. Z-Algorithm for Intrusion Detection
// (Same as the general Z-Algorithm implementation)

// 4. Suffix Array for Longest Repeated Substring
String findLongestRepeatedSubstring(String text) {
  int n = text.length;
  List<int> suffixArray = buildSuffixArrayDartSort(text);
  int maxLength = 0;
  int maxIndex = -1;

  for (int i = 0; i < n - 1; i++) {
    int length = getLCP(text, suffixArray[i], suffixArray[i + 1]);
    if (length > maxLength) {
      maxLength = length;
      maxIndex = suffixArray[i];
    }
  }

  if (maxLength > 0) {
    return text.substring(maxIndex, maxIndex + maxLength);
  } else {
    return "No repeated substring found";
  }
}

// Helper function to calculate Longest Common Prefix (LCP)
int getLCP(String text, int i, int j) {
  int length = 0;
  while (i < text.length && j < text.length && text[i] == text[j]) {
    length++;
    i++;
    j++;
  }
  return length;
}

// 5. Z-Algorithm for Data Compression (Simplified)
String compressData(String data, List<int> zArray) {
  String compressed = "";
  for (int i = 0; i < data.length; i++) {
    if (zArray[i] > 0) {
      compressed += "<${zArray[i]}>"; // simple encoding.  Real impl would be more complex
      i += zArray[i] - 1; // Skip the matched part
    } else {
      compressed += data[i];
    }
  }
  return compressed;
}

String decompressData(String compressedData) {
  String decompressed = "";
  for (int i = 0; i < compressedData.length; i++) {
    if (compressedData[i] == '<') {
      int j = i + 1;
      String numStr = "";
      while (j < compressedData.length &&
          compressedData[j] != '>') { // Extract the number
        numStr += compressedData[j];
        j++;
      }
      if (numStr.isNotEmpty) {
        int num = int.parse(numStr);
        // Check for valid num before using it.
        if (num <= decompressed.length && num > 0) {
          String prev = decompressed.substring(
              decompressed.length - num, decompressed.length);
          decompressed += prev;
        } else {
          // Handle the error:  The number is out of bounds.
          decompressed +=
          ""; // Or some other sensible default, or throw an exception.  For now, add nothing.
        }

        i = j; // Skip past the '>'
      }
    } else {
      decompressed += compressedData[i];
    }
  }
  return decompressed;
}

// 6. Suffix Array for Plagiarism Detection
double calculateTextSimilarity(String text1, String text2) {
  // Normalize texts (remove punctuation, lowercase, etc.)
  text1 = _normalizeText(text1);
  text2 = _normalizeText(text2);

  List<String> words1 = text1.split(" ");
  List<String> words2 = text2.split(" ");

  // Build suffix array for the first text
  List<int> suffixArray1 = buildSuffixArrayDartSort(text1);

  int commonLength = 0;
  for (String word in words2) {
    // Find if the word (or a suffix starting with the word) exists in text1
    if (_containsWord(text1, word, suffixArray1)) {
      commonLength += word.length;
    }
  }

  // Calculate a similarity score (simple example)
  num totalLength = text1.length + text2.length;
  return (2.0 * commonLength) / totalLength;
}

// Helper function to normalize text
String _normalizeText(String text) {
  return text.toLowerCase().replaceAll(RegExp(r'[^\w\s]'), '');
}

// Helper function to check if a word exists using the suffix array
bool _containsWord(String text, String word, List<int> suffixArray) {
  for (int index in suffixArray) {
    if (text.substring(index).startsWith(word)) {
      return true;
    }
  }
  return false;
}

// -------------------
// Suffix Array and Z-Algorithm Implementations (Reused)
// -------------------

List<int> buildSuffixArrayDartSort(String text) {
  int n = text.length;
  List<int> suffixArray = List.generate(n, (i) => i);
  suffixArray.sort((a, b) {
    String suffixA = text.substring(a);
    String suffixB = text.substring(b);
    return suffixA.compareTo(suffixB);
  });
  return suffixArray;
}

List<int> findPatternBinarySearch(
    String text, String pattern, List<int> suffixArray) {
  int n = text.length;
  int m = pattern.length;
  List<int> occurrences = [];
  int low = 0, high = n - 1;

  int first = -1;
  while (low <= high) {
    int mid = low + (high - low) ~/ 2;
    if (text.substring(suffixArray[mid]).startsWith(pattern)) {
      first = mid;
      high = mid - 1;
    } else if (text.substring(suffixArray[mid]).compareTo(pattern) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  int last = -1;
  low = 0;
  high = n - 1;
  while (low <= high) {
    int mid = low + (high - low) ~/ 2;
    if (text.substring(suffixArray[mid]).startsWith(pattern)) {
      last = mid;
      low = mid + 1;
    } else if (text.substring(suffixArray[mid]).compareTo(pattern) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  if (first != -1 && last != -1) {
    for (int i = first; i <= last; i++) {
      occurrences.add(suffixArray[i]);
    }
  }
  return occurrences;
}

List<int> calculateZArray(String str) {
  int n = str.length;
  List<int> z = List<int>.filled(n, 0);
  int left = 0, right = 0;

  for (int i = 1; i < n; i++) {
    if (i > right) {
      left = right = i;
      while (right < n && str[right - left] == str[right]) {
        right++;
      }
      z[i] = right - left;
      right--;
    } else {
      int k = i - left;
      if (z[k] < right - i + 1) {
        z[i] = z[k];
      } else {
        left = i;
        while (right < n && str[right - left] == str[right]) {
          right++;
        }
        z[i] = right - left;
        right--;
      }
    }
  }
  return z;
}

List<int> findPatternZAlgorithm(String text, String pattern) {
  String combined = pattern + text;
  List<int> z = calculateZArray(combined);
  int m = pattern.length;
  List<int> occurrences = [];
  for (int i = m; i < combined.length; i++) {
    if (z[i] == m) {
      occurrences.add(i - m);
    }
  }
  return occurrences;
}
