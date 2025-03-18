class HashMapSetOperations {
  /// Approach 1: Basic HashMap Operations (CRUD)
  void basicHashMapOperations() {
    Map<String, int> ageMap = {};

    // Insertion
    ageMap['Alice'] = 25;
    ageMap['Bob'] = 30;
    ageMap['Charlie'] = 28;
    print("HashMap after insertion: $ageMap");

    // Retrieval
    print("Alice's age: ${ageMap['Alice']}");

    // Update
    ageMap['Alice'] = 26;
    print("Updated Alice's age: ${ageMap['Alice']}");

    // Deletion
    ageMap.remove('Charlie');
    print("HashMap after deletion: $ageMap");
  }

  /// Approach 2: HashMap Iteration
  void iterateHashMap(Map<String, int> data) {
    print("Iterating over HashMap:");
    data.forEach((key, value) {
      print("$key: $value");
    });
  }

  /// Approach 3: HashSet Operations (Unique Elements Handling)
  void hashSetOperations() {
    Set<int> uniqueNumbers = {1, 2, 3, 4, 5};

    // Adding elements
    uniqueNumbers.add(6);
    uniqueNumbers.add(3); // Duplicate element, won't be added
    print("HashSet after adding elements: $uniqueNumbers");

    // Checking for an element
    print("Contains 4? ${uniqueNumbers.contains(4)}");

    // Removing an element
    uniqueNumbers.remove(2);
    print("HashSet after removal: $uniqueNumbers");
  }

  /// Approach 4: HashMap for Frequency Count (Useful in Data Analysis)
  Map<int, int> frequencyCount(List<int> nums) {
    Map<int, int> freqMap = {};
    for (var num in nums) {
      freqMap[num] = (freqMap[num] ?? 0) + 1;
    }
    return freqMap;
  }

  /// Approach 5: HashSet for Duplicate Detection (Efficient Lookups)
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
  HashMapSetOperations operations = HashMapSetOperations();

  // Basic HashMap operations
  operations.basicHashMapOperations();

  // Iterating over a HashMap
  Map<String, int> sampleMap = {'John': 22, 'Emma': 29, 'Lucas': 31};
  operations.iterateHashMap(sampleMap);

  // HashSet operations
  operations.hashSetOperations();

  // Frequency count example
  List<int> numbers = [1, 2, 3, 1, 2, 3, 4, 5, 1];
  print("Frequency count: ${operations.frequencyCount(numbers)}");

  // Duplicate detection example
  print("Has duplicates? ${operations.hasDuplicate(numbers)}");
}
