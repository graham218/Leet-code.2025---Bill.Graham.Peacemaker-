// Stack Implementation (Used in some Binary Search approaches)

class Stack {
  constructor() {
    this.items = [];
    this.count = 0;
  }

  push(element) {
    this.items[this.count] = element;
    this.count += 1;
  }

  pop() {
    if (this.count === 0) return undefined;
    const deleteItem = this.items[this.count - 1];
    this.count -= 1;
    this.items.length = this.count;
    return deleteItem;
  }

  peek() {
    if (this.count === 0) return undefined;
    return this.items[this.count - 1];
  }

  isEmpty() {
    return this.count === 0;
  }

  size() {
    return this.count;
  }

  clear() {
    this.items = [];
    this.count = 0;
  }

  toArray() {
      return this.items.slice();
  }
}

// 1. Binary Search - Iterative Approach (Basic)
//   - Real-world use case: Searching for a specific entry in a sorted database table.
//   - Example: Searching for a product ID in an e-commerce catalog.
function binarySearchIterative(array, target) {
  let low = 0;
  let high = array.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    const element = array[mid];

    if (element === target) {
      return mid;
    } else if (element < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// 2. Binary Search - Recursive Approach (Basic)
//   - Real-world use case: Implementing a search function in a file system (though often optimized iteratively in practice).
//   - Example: Searching within a sorted configuration file.
function binarySearchRecursive(array, target, low, high) {
  if (low > high) return -1;

  const mid = Math.floor((low + high) / 2);
  const element = array[mid];

  if (element === target) {
    return mid;
  } else if (element < target) {
    return binarySearchRecursive(array, target, mid + 1, high);
  } else {
    return binarySearchRecursive(array, target, low, mid - 1);
  }
}

// 3. Binary Search - Iterative with Stack (Simulating Recursion)
//   - Real-world use case:  Useful in environments with limited recursion depth or when converting recursive algorithms to iterative ones for performance.
//   - Example:  Converting a recursive search in a deeply nested data structure to avoid stack overflow.
function binarySearchIterativeWithStack(array, target) {
    const stack = new Stack();
    stack.push({ low: 0, high: array.length - 1 });

    while (!stack.isEmpty()) {
        const { low, high } = stack.pop();

        if (low > high) continue;

        const mid = Math.floor((low + high) / 2);
        const element = array[mid];

        if (element === target) {
            return mid;
        } else if (element < target) {
            stack.push({ low: mid + 1, high });
        } else {
            stack.push({ low, high: mid - 1 });
        }
    }
    return -1;
}

// 4. Binary Search - Finding the First Occurrence (Iterative)
//    - Real-world use case:  Searching for the start of a range in a sorted dataset.
//    - Example: Finding the first occurrence of a specific date in a log file.
function binarySearchFirstOccurrence(array, target) {
  let low = 0;
  let high = array.length - 1;
  let result = -1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    const element = array[mid];

    if (element === target) {
      result = mid;
      high = mid - 1; // Continue searching on the left side
    } else if (element < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return result;
}

// 5. Binary Search - Finding the Last Occurrence (Iterative)
//    - Real-world use case: Searching for the end of a range in a sorted dataset.
//    - Example: Finding the last occurrence of a specific event in a time-series data.
function binarySearchLastOccurrence(array, target) {
    let low = 0;
    let high = array.length - 1;
    let result = -1;

    while (low <= high) {
        const mid = Math.floor((low + high) / 2);
        const element = array[mid];

        if (element === target) {
            result = mid;
            low = mid + 1; // Continue searching on the right side
        } else if (element < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result;
}

// Test Cases
const sortedArray = [2, 5, 7, 8, 11, 12, 13, 15, 18, 20, 22, 23, 26, 29, 30];
const targetValue = 13;
const arrayWithDuplicates = [1, 3, 5, 5, 5, 7, 9, 9, 11];
const targetDuplicate = 5;

console.log("--- Binary Search Tests ---");
console.log("Sorted Array:", sortedArray);
console.log("Target Value:", targetValue);

console.log("\n1. Iterative Binary Search:");
console.log("Index of", targetValue, ":", binarySearchIterative(sortedArray, targetValue)); // Output: 6

console.log("\n2. Recursive Binary Search:");
console.log("Index of", targetValue, ":", binarySearchRecursive(sortedArray, targetValue, 0, sortedArray.length - 1)); // Output: 6

console.log("\n3. Iterative Binary Search with Stack:");
console.log("Index of", targetValue, ":", binarySearchIterativeWithStack(sortedArray, targetValue)); // Output: 6

console.log("\n--- Binary Search with Duplicates ---");
console.log("Array with Duplicates:", arrayWithDuplicates);
console.log("Target Value:", targetDuplicate);

console.log("\n4. Find First Occurrence:");
console.log("First occurrence of", targetDuplicate, ":", binarySearchFirstOccurrence(arrayWithDuplicates, targetDuplicate)); // Output: 2

console.log("\n5. Find Last Occurrence:");
console.log("Last occurrence of", targetDuplicate, ":", binarySearchLastOccurrence(arrayWithDuplicates, targetDuplicate)); // Output: 4
