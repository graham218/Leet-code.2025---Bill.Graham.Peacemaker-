// Binary Search - 5 Different Approaches

// 1. Iterative Binary Search
function binarySearchIterative(arr, target) {
  let low = 0;
  let high = arr.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);

    if (arr[mid] === target) {
      return mid;
    } else if (arr[mid] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

// 2. Recursive Binary Search
function binarySearchRecursive(arr, target, low, high) {
  if (low > high) {
    return -1;
  }

  const mid = Math.floor((low + high) / 2);

  if (arr[mid] === target) {
    return mid;
  } else if (arr[mid] < target) {
    return binarySearchRecursive(arr, target, mid + 1, high);
  } else {
    return binarySearchRecursive(arr, target, low, mid - 1);
  }
}

// 3. Binary Search with Early Exit
function binarySearchEarlyExit(arr, target) {
    let low = 0;
    let high = arr.length - 1;

    while (low < high) { // Changed condition for early exit
        const mid = Math.floor((low + high) / 2);

        if (arr[mid] === target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid; // Changed to high = mid
        }
    }
    //check the last element
    if(arr[low] === target){
        return low;
    }
    return -1;
}

// 4. Binary Search using Array.prototype.slice (Less Efficient)
function binarySearchSlice(arr, target) {
  let low = 0;
  let high = arr.length - 1;

  while (low <= high) {
    const mid = Math.floor((low + high) / 2);
    const midValue = arr[mid];

    if (midValue === target) {
      return mid;
    } else if (midValue < target) {
      low = mid + 1;
      arr = arr.slice(low, high + 1); // Creating a new sub-array
      high = arr.length -1;
      low = 0;
    } else {
      high = mid - 1;
      arr = arr.slice(low, high + 1);  // Creating a new sub-array
      high = arr.length -1;
      low = 0;
    }
  }
  return -1;
}

// 5. Binary Search with ES6 findIndex (Not a true binary search, but uses findIndex)
function binarySearchFindIndex(arr, target) {
  const index = arr.findIndex(item => item === target);
  return index; // findIndex returns -1 if not found
}



// Example Usage:
const sortedArray = [-1, 0, 3, 5, 9, 12];
const targetValue = 9;

console.log("Array: ", sortedArray);
console.log("Target: ", targetValue);
console.log("\n--- Binary Search Results ---");

// 1. Iterative
const result1 = binarySearchIterative(sortedArray, targetValue);
console.log("1. Iterative:", result1); // Output: 4

// 2. Recursive
const result2 = binarySearchRecursive(sortedArray, targetValue, 0, sortedArray.length - 1);
console.log("2. Recursive:", result2); // Output: 4

// 3. Early Exit
const result3 = binarySearchEarlyExit(sortedArray, targetValue);
console.log("3. Early Exit:", result3); // Output: 4

// 4. Using Slice (Less Efficient)
const result4 = binarySearchSlice(sortedArray, targetValue);
console.log("4. Using Slice:", result4); // Output: 4

// 5. Using findIndex (Not a true binary search)
const result5 = binarySearchFindIndex(sortedArray, targetValue);
console.log("5. Using findIndex:", result5); // Output: 4

// Example where target is not found
const targetNotFound = 2;
console.log("\nTarget Not Found Example:");
console.log("Target:", targetNotFound);
console.log("Iterative:", binarySearchIterative(sortedArray, targetNotFound)); // Output: -1
console.log("Recursive:", binarySearchRecursive(sortedArray, targetNotFound, 0, sortedArray.length - 1)); // Output: -1
console.log("Early Exit:", binarySearchEarlyExit(sortedArray, targetNotFound));
console.log("Slice:", binarySearchSlice(sortedArray, targetNotFound));
console.log("findIndex:", binarySearchFindIndex(sortedArray, targetNotFound));
