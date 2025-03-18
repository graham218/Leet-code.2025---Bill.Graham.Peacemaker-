void main() {
  List<Transaction> transactions = [
    Transaction("Alice", 200),
    Transaction("Bob", -100),
    Transaction("Charlie", -100),
    Transaction("Dave", 50),
    Transaction("Eve", 50),
    Transaction("Frank", -50)
  ];

  print("Finding transaction triplets that sum to zero:");
  print("Two Pointers Approach:");
  printZeroSumTriplets(findZeroSumTransactionsTwoPointers(transactions));
  print("\nHashSet Approach:");
  printZeroSumTriplets(findZeroSumTransactionsHashSet(transactions));
  print("\nBrute Force Approach:");
  printZeroSumTriplets(findZeroSumTransactionsBruteForce(transactions));
  print("\nSorting + Binary Search Approach:");
  printZeroSumTriplets(findZeroSumTransactionsBinarySearch(transactions));
  print("\nOptimized HashMap Approach:");
  printZeroSumTriplets(findZeroSumTransactionsOptimized(transactions));
}

class Transaction {
  String name;
  int amount;

  Transaction(this.name, this.amount);
}

void printZeroSumTriplets(List<List<Transaction>> result) {
  for (var triplet in result) {
    print("[${triplet[0].name}, ${triplet[1].name}, ${triplet[2].name}] sums to 0");
  }
}

// Approach 1: Two Pointers (Optimized O(n^2))
List<List<Transaction>> findZeroSumTransactionsTwoPointers(List<Transaction> transactions) {
  transactions.sort((a, b) => a.amount.compareTo(b.amount));
  List<List<Transaction>> result = [];
  for (int i = 0; i < transactions.length - 2; i++) {
    if (i > 0 && transactions[i].amount == transactions[i - 1].amount) continue;
    int left = i + 1, right = transactions.length - 1;
    while (left < right) {
      int sum = transactions[i].amount + transactions[left].amount + transactions[right].amount;
      if (sum == 0) {
        result.add([transactions[i], transactions[left], transactions[right]]);
        while (left < right && transactions[left].amount == transactions[left + 1].amount) { left++; }
        while (left < right && transactions[right].amount == transactions[right - 1].amount) { right--; }
        left++;
        right--;
      } else if (sum < 0) {
        left++;
      } else {
        right--;
      }
    }
  }
  return result;
}

// Approach 2: HashSet for Unique Triplets
List<List<Transaction>> findZeroSumTransactionsHashSet(List<Transaction> transactions) {
  transactions.sort((a, b) => a.amount.compareTo(b.amount));
  Set<List<Transaction>> result = {};
  for (int i = 0; i < transactions.length - 2; i++) {
    Set<int> seen = {};
    for (int j = i + 1; j < transactions.length; j++) {
      int complement = -transactions[i].amount - transactions[j].amount;
      if (seen.contains(complement)) {
        result.add([transactions[i], Transaction("Temp", complement), transactions[j]]);
      }
      seen.add(transactions[j].amount);
    }
  }
  return result.toList();
}

// Approach 3: Brute Force (O(n^3))
List<List<Transaction>> findZeroSumTransactionsBruteForce(List<Transaction> transactions) {
  List<List<Transaction>> result = [];
  for (int i = 0; i < transactions.length - 2; i++) {
    for (int j = i + 1; j < transactions.length - 1; j++) {
      for (int k = j + 1; k < transactions.length; k++) {
        if (transactions[i].amount + transactions[j].amount + transactions[k].amount == 0) {
          result.add([transactions[i], transactions[j], transactions[k]]);
        }
      }
    }
  }
  return result;
}

// Approach 4: Sorting + Binary Search
List<List<Transaction>> findZeroSumTransactionsBinarySearch(List<Transaction> transactions) {
  transactions.sort((a, b) => a.amount.compareTo(b.amount));
  List<List<Transaction>> result = [];
  for (int i = 0; i < transactions.length - 2; i++) {
    for (int j = i + 1; j < transactions.length - 1; j++) {
      int complement = -transactions[i].amount - transactions[j].amount;
      int index = binarySearch(transactions, j + 1, transactions.length - 1, complement);
      if (index != -1) {
        result.add([transactions[i], transactions[j], transactions[index]]);
      }
    }
  }
  return result;
}

int binarySearch(List<Transaction> transactions, int left, int right, int target) {
  while (left <= right) {
    int mid = left + (right - left) ~/ 2;
    if (transactions[mid].amount == target) return mid;
    if (transactions[mid].amount < target) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return -1;
}

// Approach 5: Optimized Using HashMap
List<List<Transaction>> findZeroSumTransactionsOptimized(List<Transaction> transactions) {
  transactions.sort((a, b) => a.amount.compareTo(b.amount));
  List<List<Transaction>> result = [];
  for (int i = 0; i < transactions.length - 2; i++) {
    Map<int, int> map = {};
    for (int j = i + 1; j < transactions.length; j++) {
      int complement = -transactions[i].amount - transactions[j].amount;
      if (map.containsKey(complement)) {
        result.add([transactions[i], Transaction("Temp", complement), transactions[j]]);
      }
      map[transactions[j].amount] = j;
    }
  }
  return result;
}
