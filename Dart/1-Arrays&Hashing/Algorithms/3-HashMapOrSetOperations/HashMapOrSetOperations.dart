class HashMapSetOperations {
  /// Demonstrates basic HashMap operations (Create, Read, Update, Delete).
  void basicHashMapOperations() {
    Map<String, int> ageMap = {};

    // Create (Insert)
    ageMap['Alice'] = 25;
    ageMap['Bob'] = 30;
    ageMap['Charlie'] = 28;
    print("HashMap after insertion: $ageMap");

    // Read (Retrieve)
    print("Alice's age: ${ageMap['Alice']}");

    // Update
    ageMap['Alice'] = 26;
    print("Updated Alice's age: ${ageMap['Alice']}");

    // Delete
    ageMap.remove('Charlie');
    print("HashMap after deletion: $ageMap");
  }

  /// Iterates over a HashMap and prints key-value pairs.
  void iterateHashMap(Map<String, int> data) {
    print("Iterating over HashMap:");
    data.forEach((key, value) {
      print("$key: $value");
    });
  }

  /// Demonstrates basic HashSet operations (Add, Contains, Remove).
  void hashSetOperations() {
    Set<int> uniqueNumbers = {1, 2, 3, 4, 5};

    // Add elements
    uniqueNumbers.add(6);
    uniqueNumbers.add(3); // Duplicate element, won't be added
    print("HashSet after adding elements: $uniqueNumbers");

    // Check for element existence
    print("Contains 4? ${uniqueNumbers.contains(4)}");

    // Remove an element
    uniqueNumbers.remove(2);
    print("HashSet after removal: $uniqueNumbers");
  }

  /// Calculates the frequency of each element in a list using a HashMap.
  Map<int, int> frequencyCount(List<int> nums) {
    Map<int, int> freqMap = {};
    for (var num in nums) {
      freqMap[num] = (freqMap[num] ?? 0) + 1;
    }
    return freqMap;
  }

  /// Checks if a list contains duplicate elements using a HashSet.
  bool hasDuplicate(List<int> nums) {
    Set<int> seen = {};
    for (var num in nums) {
      if (!seen.add(num)) {
        return true; // Found a duplicate
      }
    }
    return false;
  }
}

void main() {
  final operations = HashMapSetOperations(); // use final

  // Basic HashMap operations
  print("\n--- Basic HashMap Operations ---");
  operations.basicHashMapOperations();

  // Iterating over a HashMap
  print("\n--- HashMap Iteration ---");
  final sampleMap = <String, int>{'John': 22, 'Emma': 29, 'Lucas': 31}; //use final and type literal
  operations.iterateHashMap(sampleMap);

  // HashSet operations
  print("\n--- HashSet Operations ---");
  operations.hashSetOperations();

  // Frequency count example
  print("\n--- Frequency Count ---");
  final numbers = <int>[1, 2, 3, 1, 2, 3, 4, 5, 1]; //use final and type literal
  print("Frequency count: ${operations.frequencyCount(numbers)}");

  // Duplicate detection example
  print("\n--- Duplicate Detection ---");
  print("Has duplicates? ${operations.hasDuplicate(numbers)}");
}