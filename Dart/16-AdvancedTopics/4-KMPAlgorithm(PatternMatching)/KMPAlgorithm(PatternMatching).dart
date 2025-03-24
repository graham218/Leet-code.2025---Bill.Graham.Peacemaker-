import 'package:collection/collection.dart';

void main() {
  // Example text and pattern
  String text = "ABABDABACDABABCABAB";
  String pattern = "ABABCABAB";

  // 1. Basic KMP Search
  print("\n1. Basic KMP Search:");
  List<int> basicKMPResult = basicKMPSearch(text, pattern);
  print('Pattern found at indices: $basicKMPResult'); // Output: [10]

  // 2. KMP Search with Detailed Output
  print("\n2. KMP Search with Detailed Output:");
  detailedKMPSearch(text, pattern);
  // Output:
  //  text: ABABDABACDABABCABAB
  //  pattern: ABABCABAB
  //  mismatch at text[4] 'D' and pattern[4] 'C'
  //  j updated to 2
  //  ... (more detailed output)
  //  Pattern found at index: 10

  // 3. KMP Search using extension method
  print("\n3. KMP Search using Extension Method:");
  List<int> extensionKMPResult = text.kmpSearch(pattern);
  print('Pattern found at indices: $extensionKMPResult'); // Output: [10]

  // 4. KMP Search with Custom List Implementation
  print("\n4. KMP Search with Custom List Implementation:");
  List<int> customListKMPResult = kmpSearchCustomList(text, pattern);
  print('Pattern found at indices: $customListKMPResult');

  // 5. KMP Search with Null Safety Checks
  print("\n5. KMP Search with Null Safety Checks:");
  List<int> nullSafeKMPResult = nullSafeKMPSearch(text, pattern);
  print('Pattern found at indices: $nullSafeKMPResult');
}

// 1. Basic KMP Search Implementation
List<int> basicKMPSearch(String text, String pattern) {
  List<int> result = [];
  int n = text.length;
  int m = pattern.length;
  if (m == 0) return [0]; //handle empty pattern
  if (n == 0) return [];

  List<int> lps = computeLPSArray(pattern);
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

// 2. KMP Search with Detailed Output
void detailedKMPSearch(String text, String pattern) {
  int n = text.length;
  int m = pattern.length;
  if (m == 0) {
    print("Empty pattern. Found at index 0");
    return;
  }
  if(n==0){
    print("Empty text. Pattern not found");
    return;
  }

  List<int> lps = computeLPSArray(pattern);
  print('text: $text');
  print('pattern: $pattern');
  int i = 0;
  int j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }
    if (j == m) {
      print('Pattern found at index: ${i - j}');
      j = lps[j - 1];
    } else if (i < n && pattern[j] != text[i]) {
      print('mismatch at text[$i] \'${text[i]}\' and pattern[$j] \'${pattern[j]}\'');
      if (j != 0) {
        print('j updated to ${lps[j - 1]}');
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
}

// 3. KMP Search as an Extension Method
extension KMPStringSearch on String {
  List<int> kmpSearch(String pattern) {
    List<int> result = [];
    int n = this.length;
    int m = pattern.length;
    if (m == 0) return [0];
    if (n == 0) return [];
    List<int> lps = computeLPSArray(pattern);
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

// 4. KMP Search with Custom List Implementation
class CustomList<T> {
  List<T?> _list;
  CustomList(int size) : _list = List<T?>.filled(size, null);

  T? operator [](int index) {
    if (index < 0 || index >= _list.length) {
      throw RangeError('Index out of bounds');
    }
    return _list[index];
  }

  void operator []=(int index, T? value) {
    if (index < 0 || index >= _list.length) {
      throw RangeError('Index out of bounds');
    }
    _list[index] = value;
  }

  int get length => _list.length;
}

List<int> kmpSearchCustomList(String text, String pattern) {
  List<int> result = [];
  int n = text.length;
  int m = pattern.length;
  if (m == 0) return [0];
  if (n == 0) return [];

  CustomList<int> lps = computeLPSArrayCustomList(pattern);
  int i = 0;
  int j = 0;
  while (i < n) {
    if (pattern[j] == text[i]) {
      i++;
      j++;
    }
    if (j == m) {
      result.add(i - j);
      j = lps[j - 1]!;
    } else if (i < n && pattern[j] != text[i]) {
      if (j != 0) {
        j = lps[j - 1]!;
      } else {
        i++;
      }
    }
  }
  return result;
}

CustomList<int> computeLPSArrayCustomList(String pattern) {
  int m = pattern.length;
  CustomList<int> lps = CustomList<int>(m);
  lps[0] = 0;
  int len = 0;
  int i = 1;
  while (i < m) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[len - 1]!;
      } else {
        lps[i] = 0;
        i++;
      }
    }
  }
  return lps;
}

// 5. KMP Search with Null Safety
List<int> nullSafeKMPSearch(String? text, String? pattern) {
  if (text == null || pattern == null) {
    return []; // Or throw an exception:  throw ArgumentError("Text and pattern must not be null.");
  }

  List<int> result = [];
  int n = text.length;
  int m = pattern.length;
  if (m == 0) return [0];
  if (n == 0) return [];

  List<int> lps = computeLPSArray(pattern);
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

// Function to compute the Longest Prefix Suffix (LPS) array
List<int> computeLPSArray(String pattern) {
  int m = pattern.length;
  List<int> lps = List<int>.filled(m, 0);
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
