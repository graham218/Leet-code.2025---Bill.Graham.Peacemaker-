import 'package:collection/collection.dart';
import 'package:intl/intl.dart'; // For logging with timestamps
import 'package:async/async.dart'; //For testing

void main() async {
  // --- Configuration ---
  const String text = "AABAACAADAABAABAA";
  const String pattern = "AABA";

  // --- 1. Basic KMP Search ---
  print("\n1. Basic KMP Search:");
  final basicKMPResult = basicKMPSearch(text, pattern);
  print("Basic KMP Search Result: $basicKMPResult");

  // --- 2. KMP Search with Logging ---
  print("\n2. KMP Search with Logging:");
  final loggedKMPResult = kmpSearchWithLogging(text, pattern);
  print("KMP Search with Logging Result: $loggedKMPResult");

  // --- 3. KMP Search with Null Safety and Error Handling ---
  print("\n3. KMP Search with Null Safety and Error Handling:");
  try {
    final nullSafeResult = nullSafeKMP(text, pattern);
    print("Null Safe KMP Search Result: $nullSafeResult");
  } catch (e) {
    print("Error during Null Safe KMP Search: $e");
  }

  // --- 4. KMP Search with Extension and Chaining ---
  print("\n4. KMP Search with Extension and Chaining:");
  final extensionResult = text.kmpSearchExtension(pattern);
  print("Extension KMP Search Result: $extensionResult");

  // --- 5. KMP Search with Performance Measurement ---
  print("\n5. KMP Search with Performance Measurement:");
  await measureKMPPerformance(text, pattern);

  // --- 6. KMP Search with Asynchronous Computation (Simulated) ---
  print("\n6. KMP Search with Asynchronous Computation (Simulated):");
  final asyncResult = await asyncKMPSearch(text, pattern);
  print("Asynchronous KMP Search Result: $asyncResult");
}

// --- 1. Basic KMP Search (As before) ---
List<int> basicKMPSearch(String text, String pattern) {
  final List<int> result = [];
  final int n = text.length;
  final int m = pattern.length;
  if (m == 0) return [0];
  if (n == 0) return [];

  final List<int> lps = computeLPSArray(pattern);
  int i = 0;
  int j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }
    if (j == m) {
      result.add(i - j);
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return result;
}

// --- 2. KMP Search with Logging ---
// Uses intl package for formatted timestamps in logs
List<int> kmpSearchWithLogging(String text, String pattern) {
  final List<int> result = [];
  final int n = text.length;
  final int m = pattern.length;
  final DateFormat isoFormat = DateFormat('yyyy-MM-dd HH:mm:ss.SSS'); // Use ISO 8601 for timestamps

  if (m == 0) {
    log(isoFormat, "Empty pattern, returning [0]");
    return [0];
  }
  if (n == 0) {
    log(isoFormat, "Empty text, returning []");
    return [];
  }

  final List<int> lps = computeLPSArray(pattern);
  int i = 0;
  int j = 0;

  log(isoFormat, "Starting KMP Search. Text: '$text', Pattern: '$pattern'");
  while (i < n) {
    if (pattern[j] == text[i]) {
      log(isoFormat, "Match at text[$i] ('${text[i]}') and pattern[$j] ('${pattern[j]}'). Incrementing i and j.");
      i++;
      j++;
    }
    if (j == m) {
      log(isoFormat, "Pattern found at index ${i - j}. Adding ${i - j} to result.");
      result.add(i - j);
      j = lps[j - 1];
      log(isoFormat, "j updated to ${lps[j - 1]}");
    } else if (i < n && pattern[j] != text[i]) {
      log(isoFormat, "Mismatch at text[$i] ('${text[i]}') and pattern[$j] ('${pattern[j]}')");
      if (j != 0) {
        log(isoFormat, "j updated to ${lps[j - 1]}");
        j = lps[j - 1];
      } else {
        i++;
        log(isoFormat, "j is 0, incrementing i to $i");
      }
    }
  }
  log(isoFormat, "Search complete. Returning result: $result");
  return result;
}

// Helper function for logging
void log(DateFormat formatter, String message) {
  print('${formatter.format(DateTime.now())} - $message');
}

// --- 3. KMP Search with Null Safety and Error Handling ---
// Improved null safety and throws exceptions for invalid input
List<int> nullSafeKMP(String text, String pattern) {
  if (text == null) {
    throw ArgumentError.notNull("text");
  }
  if (pattern == null) {
    throw ArgumentError.notNull("pattern");
  }

  final List<int> result = [];
  final int n = text.length;
  final int m = pattern.length;
  if (m == 0) return [0];
  if (n == 0) return [];

  final List<int> lps = computeLPSArray(pattern);
  int i = 0;
  int j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }
    if (j == m) {
      result.add(i - j);
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return result;
}

// --- 4. KMP Search with Extension and Chaining ---
// Extension method on String for a more fluent API
extension KMPStringSearchExtension on String {
  List<int> kmpSearchExtension(String pattern) {
    // Chain with a null check extension for added safety.
    return this._kmpSearch(pattern);
  }

  List<int> _kmpSearch(String pattern) {
    final List<int> result = [];
    final int n = this.length;
    final int m = pattern.length;
    if (m == 0) return [0];
    if (n == 0) return [];

    final List<int> lps = computeLPSArray(pattern);
    int i = 0;
    int j = 0;
    while (i < n) {
      if (pattern[j] == this[i]) {
        i++;
        j++;
      }
      if (j == m) {
        result.add(i - j);
        j = lps[j - 1];
      } else if (i < n && pattern[j] != this[i]) {
        if (j != 0) {
          j = lps[j - 1];
        } else {
          i++;
        }
      }
    }
    return result;
  }
}

// --- 5. KMP Search with Performance Measurement ---
// Uses Stopwatch to measure execution time
Future<void> measureKMPPerformance(String text, String pattern) async {
  final stopwatch = Stopwatch()..start();
  final result = basicKMPSearch(text, pattern); // Or any other KMP implementation
  stopwatch.stop();

  print('KMP Search Result: $result');
  print('Execution Time: ${stopwatch.elapsedMicroseconds} microseconds');
  print('Execution Time: ${stopwatch.elapsedMilliseconds} milliseconds');
}

// --- 6. KMP Search with Asynchronous Computation (Simulated) ---
// Uses Future.delayed to simulate an asynchronous operation.  In a real
// application, this might involve offloading the KMP computation to
// another isolate or a background thread.
Future<List<int>> asyncKMPSearch(String text, String pattern) async {
  // Simulate asynchronous computation with a delay.
  await Future.delayed(Duration(milliseconds: 10)); // Simulate a short delay

  final List<int> result = [];
  final int n = text.length;
  final int m = pattern.length;
  if (m == 0) return [0];
  if (n == 0) return [];

  final List<int> lps = computeLPSArray(pattern);
  int i = 0;
  int j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }
    if (j == m) {
      result.add(i - j);
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return result;
}

// --- (Helper Function - computeLPSArray) ---
// (As before)
List<int> computeLPSArray(String pattern) {
  final int m = pattern.length;
  final List<int> lps = List<int>.filled(m, 0);
  int len = 0;
  int i = 1;
  lps[0] = 0;
  while (i < m) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}
