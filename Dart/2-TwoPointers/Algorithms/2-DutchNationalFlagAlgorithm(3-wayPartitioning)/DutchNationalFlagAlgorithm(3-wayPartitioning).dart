class ListNode {
  int value;
  ListNode? next;
  ListNode(this.value, [this.next]);
}

// Approach 1: Classic Dutch National Flag Algorithm (Three-way Partitioning)
// Efficient for sorting an array with three distinct values like {0,1,2}.
void dutchNationalFlag(List<int> arr) {
  int low = 0, mid = 0, high = arr.length - 1;
  while (mid <= high) {
    if (arr[mid] == 0) {
      _swap(arr, low, mid);
      low++;
      mid++;
    } else if (arr[mid] == 1) {
      mid++;
    } else {
      _swap(arr, mid, high);
      high--;
    }
  }
}

// Approach 2: Counting Sort Variant (Count and Overwrite)
// Useful when modifying the array in-place is not allowed.
void countingSortVariant(List<int> arr) {
  int count0 = 0, count1 = 0, count2 = 0;
  for (int num in arr) {
    if (num == 0) {
      count0++;
    } else if (num == 1) {
      count1++;
    } else {
      count2++;
    }
  }
  for (int i = 0; i < count0; i++) {
    arr[i] = 0;
  }
  for (int i = count0; i < count0 + count1; i++) {
    arr[i] = 1;
  }
  for (int i = count0 + count1; i < arr.length; i++) {
    arr[i] = 2;
  }
}

// Approach 3: QuickSort-style Partitioning (Hoare’s Partition)
// Inspired by quicksort partitioning for three-way sorting.
void quickSortPartition(List<int> arr) {
  int low = -1, high = arr.length;
  int pivot = 1;
  int i = 0;
  while (i < high) {
    if (arr[i] < pivot) {
      _swap(arr, ++low, i);
    } else if (arr[i] > pivot) {
      _swap(arr, i, --high);
      continue;
    }
    i++;
  }
}

// Approach 4: Bucket Sort Style (Using Separate Buckets)
// Creates separate lists and merges them back in order.
void bucketSortStyle(List<int> arr) {
  List<int> zeroBucket = [], oneBucket = [], twoBucket = [];
  for (int num in arr) {
    if (num == 0) {
      zeroBucket.add(num);
    } else if (num == 1) {
      oneBucket.add(num);
    } else {
      twoBucket.add(num);
    }
  }
  arr.clear();
  arr.addAll(zeroBucket);
  arr.addAll(oneBucket);
  arr.addAll(twoBucket);
}

// Approach 5: Iterative Dutch National Flag
// Prevents stack overflow from recursion.
void iterativeDutchFlag(List<int> arr) {
  int low = 0, mid = 0, high = arr.length - 1;
  while (mid <= high) {
    if (arr[mid] == 0) {
      _swap(arr, low, mid);
      low++;
      mid++;
    } else if (arr[mid] == 2) {
      _swap(arr, mid, high);
      high--;
    } else {
      mid++;
    }
  }
}

// Helper function to swap elements in an array
void _swap(List<int> arr, int i, int j) {
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

// Main function to test different approaches
void main() {
  List<int> arr1 = [2, 0, 2, 1, 1, 0];
  List<int> arr2 = List.from(arr1);
  List<int> arr3 = List.from(arr1);
  List<int> arr4 = List.from(arr1);
  List<int> arr5 = List.from(arr1);

  dutchNationalFlag(arr1);
  print("Dutch National Flag Algorithm: $arr1");

  countingSortVariant(arr2);
  print("Counting Sort Variant: $arr2");

  quickSortPartition(arr3);
  print("QuickSort Partitioning: $arr3");

  bucketSortStyle(arr4);
  print("Bucket Sort Style: $arr4");

  iterativeDutchFlag(arr5);
  print("Iterative Dutch National Flag: $arr5");
}
