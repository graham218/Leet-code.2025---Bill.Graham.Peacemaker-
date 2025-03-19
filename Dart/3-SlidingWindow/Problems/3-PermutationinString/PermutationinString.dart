// Dart Solution for "Permutation in String"
// Real-world Applications: Plagiarism detection, Anagram matching, Genetic sequence analysis

import 'dart:collection';

class PermutationChecker {
  String s1;
  String s2;
  PermutationChecker(this.s1, this.s2);

  // Approach 1: Sliding Window with Frequency Count (O(n))
  bool slidingWindow() {
    if (s1.length > s2.length) return false;
    List<int> s1Freq = List.filled(26, 0);
    List<int> s2Freq = List.filled(26, 0);

    for (int i = 0; i < s1.length; i++) {
      s1Freq[s1[i].codeUnitAt(0) - 'a'.codeUnitAt(0)]++;
      s2Freq[s2[i].codeUnitAt(0) - 'a'.codeUnitAt(0)]++;
    }

    for (int i = 0; i <= s2.length - s1.length; i++) {
      if (_matches(s1Freq, s2Freq)) return true;
      if (i + s1.length < s2.length) {
        s2Freq[s2[i].codeUnitAt(0) - 'a'.codeUnitAt(0)]--;
        s2Freq[s2[i + s1.length].codeUnitAt(0) - 'a'.codeUnitAt(0)]++;
      }
    }
    return _matches(s1Freq, s2Freq);
  }

  bool _matches(List<int> freq1, List<int> freq2) {
    for (int i = 0; i < 26; i++) {
      if (freq1[i] != freq2[i]) return false;
    }
    return true;
  }

  // Approach 2: Sorting and Comparing (O(n log n))
  bool sortingMethod() {
    List<String> sortedS1 = s1.split('')..sort();
    for (int i = 0; i <= s2.length - s1.length; i++) {
      List<String> sortedS2 = s2.substring(i, i + s1.length).split('')..sort();
      if (sortedS1.join() == sortedS2.join()) return true;
    }
    return false;
  }

  // Approach 3: HashMap Frequency Count (O(n))
  bool hashMapMethod() {
    if (s1.length > s2.length) return false;
    Map<String, int> s1Map = _getFrequencyMap(s1);
    Map<String, int> windowMap = _getFrequencyMap(s2.substring(0, s1.length));

    for (int i = 0; i <= s2.length - s1.length; i++) {
      if (s1Map.toString() == windowMap.toString()) return true;
      if (i + s1.length < s2.length) {
        windowMap[s2[i]] = (windowMap[s2[i]] ?? 0) - 1;
        if (windowMap[s2[i]] == 0) windowMap.remove(s2[i]);
        windowMap[s2[i + s1.length]] = (windowMap[s2[i + s1.length]] ?? 0) + 1;
      }
    }
    return false;
  }

  Map<String, int> _getFrequencyMap(String str) {
    Map<String, int> freqMap = {};
    for (var char in str.split('')) {
      freqMap[char] = (freqMap[char] ?? 0) + 1;
    }
    return freqMap;
  }

  // Approach 4: Backtracking (Brute Force) (O(n!))
  bool backtracking() {
    return _permute(s1.split(''), 0, s2);
  }

  bool _permute(List<String> arr, int l, String s2) {
    if (l == arr.length) {
      return s2.contains(arr.join());
    }
    for (int i = l; i < arr.length; i++) {
      _swap(arr, l, i);
      if (_permute(arr, l + 1, s2)) return true;
      _swap(arr, l, i);
    }
    return false;
  }

  void _swap(List<String> arr, int i, int j) {
    String temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }

  // Approach 5: Rolling Hash (Rabin-Karp Algorithm) (O(n))
  bool rollingHash() {
    if (s1.length > s2.length) return false;
    int prime = 101;
    int hashS1 = 0, hashS2 = 0, power = 1;

    for (int i = 0; i < s1.length; i++) {
      hashS1 = (hashS1 * prime + s1.codeUnitAt(i)) % 100000;
      hashS2 = (hashS2 * prime + s2.codeUnitAt(i)) % 100000;
      if (i > 0) power = (power * prime) % 100000;
    }

    for (int i = 0; i <= s2.length - s1.length; i++) {
      if (hashS1 == hashS2 && s1.split('').toSet().difference(s2.substring(i, i + s1.length).split('').toSet()).isEmpty) return true;
      if (i + s1.length < s2.length) {
        hashS2 = ((hashS2 - s2.codeUnitAt(i) * power) * prime + s2.codeUnitAt(i + s1.length)) % 100000;
      }
    }
    return false;
  }
}

// Main function to test different approaches
void main() {
  String s1 = "abc";
  String s2 = "eidbacooo";
  PermutationChecker checker = PermutationChecker(s1, s2);

  print("Sliding Window: ${checker.slidingWindow()}");
  print("Sorting Method: ${checker.sortingMethod()}");
  print("HashMap Frequency: ${checker.hashMapMethod()}");
  print("Backtracking: ${checker.backtracking()}");
  print("Rolling Hash: ${checker.rollingHash()}");
}