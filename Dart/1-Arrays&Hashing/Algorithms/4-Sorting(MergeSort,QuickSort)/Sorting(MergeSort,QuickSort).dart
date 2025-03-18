class SortingAlgorithms {
  /// Approach 1: Merge Sort (Divide and Conquer)
  List<int> mergeSort(List<int> array) {
    if (array.length <= 1) return array;
    int mid = array.length ~/ 2;
    List<int> left = mergeSort(array.sublist(0, mid));
    List<int> right = mergeSort(array.sublist(mid));
    return _merge(left, right);
  }

  List<int> _merge(List<int> left, List<int> right) {
    List<int> sorted = [];
    int i = 0, j = 0;
    while (i < left.length && j < right.length) {
      if (left[i] <= right[j]) {
        sorted.add(left[i]);
        i++;
      } else {
        sorted.add(right[j]);
        j++;
      }
    }
    sorted.addAll(left.sublist(i));
    sorted.addAll(right.sublist(j));
    return sorted;
  }

  /// Approach 2: Quick Sort (Divide and Conquer)
  List<int> quickSort(List<int> array) {
    if (array.length <= 1) return array;
    int pivot = array[array.length ~/ 2];
    List<int> left = array.where((x) => x < pivot).toList();
    List<int> middle = array.where((x) => x == pivot).toList();
    List<int> right = array.where((x) => x > pivot).toList();
    return [...quickSort(left), ...middle, ...quickSort(right)];
  }

  /// Approach 3: Bubble Sort (Simple but Inefficient)
  List<int> bubbleSort(List<int> array) {
    for (int i = 0; i < array.length - 1; i++) {
      for (int j = 0; j < array.length - i - 1; j++) {
        if (array[j] > array[j + 1]) {
          int temp = array[j];
          array[j] = array[j + 1];
          array[j + 1] = temp;
        }
      }
    }
    return array;
  }

  /// Approach 4: Insertion Sort (Efficient for Small Data)
  List<int> insertionSort(List<int> array) {
    for (int i = 1; i < array.length; i++) {
      int key = array[i];
      int j = i - 1;
      while (j >= 0 && array[j] > key) {
        array[j + 1] = array[j];
        j--;
      }
      array[j + 1] = key;
    }
    return array;
  }

  /// Approach 5: Heap Sort (Efficient for Large Datasets)
  List<int> heapSort(List<int> array) {
    void heapify(List<int> arr, int n, int i) {
      int largest = i;
      int left = 2 * i + 1;
      int right = 2 * i + 2;
      if (left < n && arr[left] > arr[largest]) largest = left;
      if (right < n && arr[right] > arr[largest]) largest = right;
      if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
      }
    }

    int n = array.length;
    for (int i = n ~/ 2 - 1; i >= 0; i--) {
      heapify(array, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
      int temp = array[0];
      array[0] = array[i];
      array[i] = temp;
      heapify(array, i, 0);
    }
    return array;
  }
}

void main() {
  SortingAlgorithms sorting = SortingAlgorithms();
  List<int> data = [34, 7, 23, 32, 5, 62];
  print("Merge Sort: ${sorting.mergeSort(List.from(data))}");
  print("Quick Sort: ${sorting.quickSort(List.from(data))}");
  print("Bubble Sort: ${sorting.bubbleSort(List.from(data))}");
  print("Insertion Sort: ${sorting.insertionSort(List.from(data))}");
  print("Heap Sort: ${sorting.heapSort(List.from(data))}");
}