class SortingAlgorithms {
  /// Merge Sort (Divide and Conquer)
  List<int> mergeSort(List<int> array) {
    if (array.length <= 1) return array;
    final mid = array.length ~/ 2;
    final left = mergeSort(array.sublist(0, mid));
    final right = mergeSort(array.sublist(mid));
    return _merge(left, right);
  }

  List<int> _merge(List<int> left, List<int> right) {
    final merged = <int>[];
    var i = 0, j = 0;
    while (i < left.length && j < right.length) {
      merged.add(left[i] <= right[j] ? left[i++] : right[j++]);
    }
    merged.addAll(left.sublist(i));
    merged.addAll(right.sublist(j));
    return merged;
  }

  /// Quick Sort (Divide and Conquer)
  List<int> quickSort(List<int> array) {
    if (array.length <= 1) return array;
    final pivot = array[array.length ~/ 2];
    final left = array.where((x) => x < pivot).toList();
    final middle = array.where((x) => x == pivot).toList();
    final right = array.where((x) => x > pivot).toList();
    return [...quickSort(left), ...middle, ...quickSort(right)];
  }

  /// Bubble Sort (Simple but Inefficient)
  List<int> bubbleSort(List<int> array) {
    final arr = List<int>.from(array); // Create a copy
    final n = arr.length;
    for (var i = 0; i < n - 1; i++) {
      for (var j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          final temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
        }
      }
    }
    return arr;
  }

  /// Insertion Sort (Efficient for Small Data)
  List<int> insertionSort(List<int> array) {
    final arr = List<int>.from(array); // Create a copy
    final n = arr.length;
    for (var i = 1; i < n; i++) {
      final key = arr[i];
      var j = i - 1;
      while (j >= 0 && arr[j] > key) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = key;
    }
    return arr;
  }

  /// Heap Sort (Efficient for Large Datasets)
  List<int> heapSort(List<int> array) {
    final arr = List<int>.from(array); // Create a copy
    final n = arr.length;

    void heapify(List<int> arr, int n, int i) {
      var largest = i;
      final left = 2 * i + 1;
      final right = 2 * i + 2;
      if (left < n && arr[left] > arr[largest]) largest = left;
      if (right < n && arr[right] > arr[largest]) largest = right;
      if (largest != i) {
        final temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
      }
    }

    for (var i = n ~/ 2 - 1; i >= 0; i--) {
      heapify(arr, n, i);
    }
    for (var i = n - 1; i > 0; i--) {
      final temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;
      heapify(arr, i, 0);
    }
    return arr;
  }
}

void main() {
  final sorting = SortingAlgorithms();
  final data = [34, 7, 23, 32, 5, 62];
  print("Merge Sort: ${sorting.mergeSort(data)}");
  print("Quick Sort: ${sorting.quickSort(data)}");
  print("Bubble Sort: ${sorting.bubbleSort(data)}");
  print("Insertion Sort: ${sorting.insertionSort(data)}");
  print("Heap Sort: ${sorting.heapSort(data)}");
}