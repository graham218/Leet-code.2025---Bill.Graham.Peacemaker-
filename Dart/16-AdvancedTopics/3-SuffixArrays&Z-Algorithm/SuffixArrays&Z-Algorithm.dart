import 'dart:math';

void main() {
  String text = "banana";
  String pattern = "ana";

  // 1. Suffix Array - Naive Approach (O(n^2 log n))
  List<int> suffixArrayNaive = buildSuffixArrayNaive(text);
  print("1. Suffix Array (Naive): $suffixArrayNaive");
  List<int> occurrencesNaive =
  findPatternNaive(text, pattern, suffixArrayNaive);
  print("   Pattern '$pattern' occurrences (Naive): $occurrencesNaive");

  // 2. Suffix Array - Using Dart's sort (O(n log^2 n) in worst case, often faster))
  List<int> suffixArrayDartSort = buildSuffixArrayDartSort(text);
  print("\n2. Suffix Array (Dart's sort): $suffixArrayDartSort");
  List<int> occurrencesDartSort =
  findPatternNaive(text, pattern, suffixArrayDartSort); //using naive search
  print("   Pattern '$pattern' occurrences (Dart's sort): $occurrencesDartSort");

  // 3. Z-Algorithm (O(n + m))
  List<int> zArray = calculateZArray(text + pattern);
  print("\n3. Z-Array: $zArray");
  List<int> occurrencesZAlgo = findPatternZAlgorithm(text, pattern);
  print("   Pattern '$pattern' occurrences (Z-Algorithm): $occurrencesZAlgo");

  // 4. Suffix Array with Binary Search (O(m log n), m = pattern length)
  List<int> suffixArrayBinarySearch = buildSuffixArrayDartSort(text); //reuse
  print("\n4. Suffix Array (Binary Search): $suffixArrayBinarySearch");
  List<int> occurrencesBinarySearch =
  findPatternBinarySearch(text, pattern, suffixArrayBinarySearch);
  print(
      "  Pattern '$pattern' occurrences (Binary Search): $occurrencesBinarySearch");

  // 5.  Z-Algorithm for multiple pattern search (variation)
  List<String> patterns = ["ana", "nan"];
  print("\n5. Z-Algorithm for multiple patterns:");
  findMultiplePatternsZAlgorithm(text, patterns);
}

// 1. Suffix Array - Naive Approach
// Time Complexity: O(n^2 log n)
List<int> buildSuffixArrayNaive(String text) {
  int n = text.length;
  List<int> suffixArray = List.generate(n, (i) => i); // Initialize with indices

  // Sort the indices based on the suffixes they represent
  suffixArray.sort((a, b) => text.substring(a).compareTo(text.substring(b)));
  return suffixArray;
}

// Function to find pattern occurrences using a suffix array (Naive search)
List<int> findPatternNaive(String text, String pattern, List<int> suffixArray) {
  int n = text.length;
  int m = pattern.length;
  List<int> occurrences = [];

  for (int i = 0; i < n; i++) {
    if (text.substring(suffixArray[i]).startsWith(pattern)) {
      occurrences.add(suffixArray[i]);
    }
  }
  return occurrences;
}

// 2. Suffix Array - Using Dart's sort (often faster, worst-case O(n log^2 n))
List<int> buildSuffixArrayDartSort(String text) {
  int n = text.length;
  List<int> suffixArray = List.generate(n, (i) => i);
  suffixArray.sort((a, b) {
    // Compare suffixes
    String suffixA = text.substring(a);
    String suffixB = text.substring(b);
    return suffixA.compareTo(suffixB);
  });
  return suffixArray;
}

// 3. Z-Algorithm
// Time Complexity: O(n + m)
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

// Function to find pattern occurrences using Z-Algorithm
List<int> findPatternZAlgorithm(String text, String pattern) {
  String combined = pattern + text; // Concatenate pattern and text
  List<int> z = calculateZArray(combined);
  int m = pattern.length;
  List<int> occurrences = [];
  for (int i = m; i < combined.length; i++) {
    if (z[i] == m) {
      occurrences.add(i - m); // Adjust index to point to start in text
    }
  }
  return occurrences;
}

// 4. Suffix Array with Binary Search
// Time Complexity: O(m log n)
List<int> findPatternBinarySearch(
    String text, String pattern, List<int> suffixArray) {
  int n = text.length;
  int m = pattern.length;
  List<int> occurrences = [];
  int low = 0, high = n - 1;

  // Binary search for the first occurrence
  int first = -1;
  while (low <= high) {
    int mid = low + (high - low) ~/ 2;
    if (text.substring(suffixArray[mid]).startsWith(pattern)) {
      first = mid;
      high = mid - 1; // Try to find an earlier occurrence
    } else if (text.substring(suffixArray[mid]).compareTo(pattern) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  // Binary search for the last occurrence
  int last = -1;
  low = 0;
  high = n - 1;
  while (low <= high) {
    int mid = low + (high - low) ~/ 2;
    if (text.substring(suffixArray[mid]).startsWith(pattern)) {
      last = mid;
      low = mid + 1; // Try to find a later occurrence
    } else if (text.substring(suffixArray[mid]).compareTo(pattern) < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  // Collect all occurrences between first and last
  if (first != -1 && last != -1) {
    for (int i = first; i <= last; i++) {
      occurrences.add(suffixArray[i]);
    }
  }
  return occurrences;
}

// 5. Z-Algorithm for Multiple Pattern Search
void findMultiplePatternsZAlgorithm(String text, List<String> patterns) {
  for (String pattern in patterns) {
    String combined = pattern + text;
    List<int> z = calculateZArray(combined);
    int m = pattern.length;
    List<int> occurrences = [];
    for (int i = m; i < combined.length; i++) {
      if (z[i] == m) {
        occurrences.add(i - m);
      }
    }
    print("   Pattern '$pattern': $occurrences");
  }
}
