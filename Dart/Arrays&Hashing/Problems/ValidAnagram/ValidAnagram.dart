void main() {
  print(isAnagramSorting("listen", "silent")); // Output: true
  print(isAnagramSorting("hello", "world"));  // Output: false
  print(isAnagramSorting("anagram", "nagaram")); // Output: true

  print(isAnagramHashMap("listen", "silent")); // Output: true
  print(isAnagramHashMap("hello", "world"));  // Output: false
  print(isAnagramHashMap("anagram", "nagaram")); // Output: true

  print(isAnagramCharArray("listen", "silent")); // Output: true
  print(isAnagramCharArray("hello", "world"));  // Output: false
  print(isAnagramCharArray("anagram", "nagaram")); // Output: true

  print(isAnagramFrequencyCounter("listen", "silent")); // Output: true
  print(isAnagramFrequencyCounter("hello", "world"));  // Output: false
  print(isAnagramFrequencyCounter("anagram", "nagaram")); // Output: true

  print(isAnagramBitwise("abc", "bca")); // Output: true
  print(isAnagramBitwise("hello", "world")); // Output: false
}

// Approach 1: Sorting
// Time Complexity: O(n log n), Space Complexity: O(n)
bool isAnagramSorting(String s, String t) {
  if (s.length != t.length) return false;
  return (s.split('')..sort()).join() == (t.split('')..sort()).join();
}

// Approach 2: HashMap (Using character frequency map)
// Time Complexity: O(n), Space Complexity: O(n)
bool isAnagramHashMap(String s, String t) {
  if (s.length != t.length) return false;

  Map<String, int> charCount = {};
  for (var char in s.split('')) {
    charCount[char] = (charCount[char] ?? 0) + 1;
  }
  for (var char in t.split('')) {
    if (!charCount.containsKey(char) || charCount[char] == 0) {
      return false;
    }
    charCount[char] = charCount[char]! - 1;
  }
  return true;
}

// Approach 3: Character Array (Fixed size for lowercase a-z)
// Time Complexity: O(n), Space Complexity: O(1)
bool isAnagramCharArray(String s, String t) {
  if (s.length != t.length) return false;

  List<int> charCount = List.filled(26, 0);
  for (int i = 0; i < s.length; i++) {
    charCount[s.codeUnitAt(i) - 'a'.codeUnitAt(0)]++;
    charCount[t.codeUnitAt(i) - 'a'.codeUnitAt(0)]--;
  }

  return charCount.every((count) => count == 0);
}

// Approach 4: Frequency Counter (Optimized hashmap usage)
// Time Complexity: O(n), Space Complexity: O(n)
bool isAnagramFrequencyCounter(String s, String t) {
  if (s.length != t.length) return false;

  List<int> frequency = List.filled(128, 0);
  for (int i = 0; i < s.length; i++) {
    frequency[s.codeUnitAt(i)]++;
    frequency[t.codeUnitAt(i)]--;
  }
  return frequency.every((count) => count == 0);
}

// Approach 5: Bitwise XOR (Only works for a-z lowercase unique anagrams)
// Time Complexity: O(n), Space Complexity: O(1)
bool isAnagramBitwise(String s, String t) {
  if (s.length != t.length) return false;

  int xorValue = 0;
  for (int i = 0; i < s.length; i++) {
    xorValue ^= s.codeUnitAt(i);
    xorValue ^= t.codeUnitAt(i);
  }
  return xorValue == 0;
}
