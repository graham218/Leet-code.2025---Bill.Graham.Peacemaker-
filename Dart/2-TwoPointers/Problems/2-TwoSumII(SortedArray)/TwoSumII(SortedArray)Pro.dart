void main() {
  List<int> prices = [600, 100, 350, 400, 500, 200]; //Unsorted list
  int budget = 750;

  print("Available prices: $prices");
  print("Budget: $budget");

  prices.sort(); // Sort the prices list
  print("Sorted prices: $prices");

  List<int>? result = findAffordableItems(prices, budget);
  if (result != null) {
    print(
        "You can buy items at indices: ${result[0]} and ${result[1]} within your budget. Total cost: ${prices[result[0]] + prices[result[1]]}");
  } else {
    print("No exact combination found within budget. Trying the closest match...");
    List<int>? closest = findClosestAffordableItems(prices, budget);
    if (closest != null) {
      print(
          "Closest affordable items are at indices: ${closest[0]} and ${closest[1]} with total cost ${prices[closest[0]] + prices[closest[1]]}");
    } else {
      print("No items fit within budget.");
    }
  }
}

// Finding two items that exactly match the budget
List<int>? findAffordableItems(List<int> prices, int budget) {
  if (prices.length < 2) return null; // Handle empty or single-element list
  int left = 0, right = prices.length - 1;
  while (left < right) {
    int totalCost = prices[left] + prices[right];
    print("Checking: indices $left and $right -> Total: $totalCost");
    if (totalCost == budget) {
      print("Match found at indices: $left, $right");
      return [left, right];
    } else if (totalCost < budget) {
      left++;
    } else {
      right--;
    }
  }
  print("No exact match found.");
  return null;
}

// Finding two items with the closest match within budget
List<int>? findClosestAffordableItems(List<int> prices, int budget) {
  if (prices.length < 2) return null; // Handle empty or single-element list
  int left = 0, right = prices.length - 1;
  int closestSum = 0;
  List<int>? closestPair;

  while (left < right) {
    int totalCost = prices[left] + prices[right];
    print("Checking closest match: indices $left and $right -> Total: $totalCost");
    if (totalCost <= budget && totalCost > closestSum) {
      closestSum = totalCost;
      closestPair = [left, right];
      print("New closest match found: indices $left, $right with sum $closestSum");
    }
    if (totalCost < budget) {
      left++;
    } else {
      right--;
    }
  }
  return closestPair;
}