import 'dart:collection';

void main() {
  print(isAnagramSorting("rat", "tar")); // Output: true
  print(isAnagramSorting("hello", "world")); // Output: false
  print(isAnagramHashMap("rat", "tar")); // Output: true
  print(isAnagramCharArray("rat", "tar")); // Output: true
  print(isAnagramFrequencyCounter("rat", "tar")); // Output: true
  print(isAnagramBitwise("abc", "bca")); // Output: true
}

// Approach 1: Sorting
// Suitable for small datasets where sorting overhead is manageable.
// Time Complexity: O(n log n), Space Complexity: O(n)
bool isAnagramSorting(String s, String t) {
  if (s.length != t.length) return false;
  return (s.split('')..sort()).join() == (t.split('')..sort()).join();
}

// Approach 2: HashMap
// Efficient for real-world applications, handles case-insensitive comparison.
// Time Complexity: O(n), Space Complexity: O(n)
bool isAnagramHashMap(String s, String t) {
  if (s.length != t.length) return false;

  Map<String, int> charCount = HashMap();
  for (var char in s.toLowerCase().runes) {
    charCount[String.fromCharCode(char)] = (charCount[String.fromCharCode(char)] ?? 0) + 1;
  }
  for (var char in t.toLowerCase().runes) {
    if (!charCount.containsKey(String.fromCharCode(char)) || charCount[String.fromCharCode(char)] == 0) {
      return false;
    }
    charCount[String.fromCharCode(char)] = charCount[String.fromCharCode(char)]! - 1;
  }
  return true;
}

// Approach 3: Character Array
// Optimized for ASCII lowercase, ideal for large-scale applications.
// Time Complexity: O(n), Space Complexity: O(1)
bool isAnagramCharArray(String s, String t) {
  if (s.length != t.length) return false;

  List<int> charCount = List.filled(128, 0);
  for (int i = 0; i < s.length; i++) {
    charCount[s.toLowerCase().codeUnitAt(i)]++;
    charCount[t.toLowerCase().codeUnitAt(i)]--;
  }
  return charCount.every((count) => count == 0);
}

// Approach 4: Frequency Counter
// Uses a direct frequency comparison for efficiency.
// Time Complexity: O(n), Space Complexity: O(n)
bool isAnagramFrequencyCounter(String s, String t) {
  if (s.length != t.length) return false;

  List<int> frequency = List.filled(128, 0);
  for (int i = 0; i < s.length; i++) {
    frequency[s.toLowerCase().codeUnitAt(i)]++;
    frequency[t.toLowerCase().codeUnitAt(i)]--;
  }
  return frequency.every((count) => count == 0);
}

// Approach 5: Bitwise XOR (Limited Use Case)
// Only works for unique lowercase letters without repetition.
// Time Complexity: O(n), Space Complexity: O(1)
bool isAnagramBitwise(String s, String t) {
  if (s.length != t.length) return false;

  int xorValue = 0;
  for (int i = 0; i < s.length; i++) {
    xorValue ^= s.toLowerCase().codeUnitAt(i);
    xorValue ^= t.toLowerCase().codeUnitAt(i);
  }
  return xorValue == 0;
}
