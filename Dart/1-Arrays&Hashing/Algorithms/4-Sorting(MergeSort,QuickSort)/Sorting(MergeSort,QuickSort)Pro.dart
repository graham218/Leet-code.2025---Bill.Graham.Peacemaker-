import 'dart:math';

class SortingAlgorithms {
  /// Merge Sort (Strings) - Alphabetical Order
  List<String> mergeSortStrings(List<String> array) {
    if (array.length <= 1) return array;
    final mid = array.length ~/ 2;
    final left = mergeSortStrings(array.sublist(0, mid));
    final right = mergeSortStrings(array.sublist(mid));
    return _mergeStrings(left, right);
  }

  List<String> _mergeStrings(List<String> left, List<String> right) {
    final merged = <String>[];
    var i = 0, j = 0;
    while (i < left.length && j < right.length) {
      if (left[i].compareTo(right[j]) <= 0) {
        merged.add(left[i]);
        i++;
      } else {
        merged.add(right[j]);
        j++;
      }
    }
    merged.addAll(left.sublist(i));
    merged.addAll(right.sublist(j));
    return merged;
  }

  /// Quick Sort (Custom Objects) - Sort by Age
  List<Person> quickSortPersons(List<Person> array) {
    if (array.length <= 1) return array;
    final random = Random();
    final pivotIndex = random.nextInt(array.length);
    final pivot = array[pivotIndex];
    final left = <Person>[];
    final middle = <Person>[];
    final right = <Person>[];
    for (final element in array) {
      if (element.age < pivot.age) {
        left.add(element);
      } else if (element.age == pivot.age) {
        middle.add(element);
      } else {
        right.add(element);
      }
    }
    return [...quickSortPersons(left), ...middle, ...quickSortPersons(right)];
  }

  /// Bubble Sort (Doubles) - Ascending Order
  List<double> bubbleSortDoubles(List<double> array) {
    final arr = List<double>.from(array);
    final n = arr.length;
    bool swapped;
    for (var i = 0; i < n - 1; i++) {
      swapped = false;
      for (var j = 0; j < n - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          final temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
          swapped = true;
        }
      }
      if (!swapped) break;
    }
    return arr;
  }

  /// Insertion Sort (Dates) - Chronological Order
  List<DateTime> insertionSortDates(List<DateTime> array) {
    final arr = List<DateTime>.from(array);
    final n = arr.length;
    for (var i = 1; i < n; i++) {
      final key = arr[i];
      var j = i - 1;
      while (j >= 0 && arr[j].isAfter(key)) {
        arr[j + 1] = arr[j];
        j--;
      }
      arr[j + 1] = key;
    }
    return arr;
  }

  /// Heap Sort (Maps) - Sort by Value
  List<Map<String, int>> heapSortMaps(List<Map<String, int>> array, String key) {
    final arr = List<Map<String, int>>.from(array);
    final n = arr.length;

    void heapify(List<Map<String, int>> arr, int n, int i, String key) {
      var largest = i;
      final left = 2 * i + 1;
      final right = 2 * i + 2;
      if (left < n && (arr[left][key] ?? -1) > (arr[largest][key] ?? -1)) largest = left;
      if (right < n && (arr[right][key] ?? -1) > (arr[largest][key] ?? -1)) largest = right;
      if (largest != i) {
        final temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, key);
      }
    }

    for (var i = n ~/ 2 - 1; i >= 0; i--) {
      heapify(arr, n, i, key);
    }
    for (var i = n - 1; i > 0; i--) {
      final temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;
      heapify(arr, i, 0, key);
    }
    return arr;
  }
}

class Person {
  final String name;
  final int age;

  Person(this.name, this.age);

  @override
  String toString() => '$name ($age)';
}

void main() {
  final sorting = SortingAlgorithms();

  final strings = ["banana", "apple", "cherry", "date"];
  print("Merge Sort (Strings): ${sorting.mergeSortStrings(strings)}");

  final persons = [
    Person("Alice", 30),
    Person("Bob", 25),
    Person("Charlie", 35),
    Person("David", 25),
  ];
  print("Quick Sort (Persons): ${sorting.quickSortPersons(persons)}");

  final doubles = [3.14, 1.618, 2.718, 0.577];
  print("Bubble Sort (Doubles): ${sorting.bubbleSortDoubles(doubles)}");

  final dates = [
    DateTime(2023, 10, 20),
    DateTime(2023, 10, 15),
    DateTime(2023, 10, 25),
    DateTime(2023, 10, 10),
  ];
  print("Insertion Sort (Dates): ${sorting.insertionSortDates(dates)}");

  final maps = [
    {"a": 10, "b": 5},
    {"a": 5, "b": 15},
    {"a": 20, "b": 1},
    {"a": 1, "b": 20},
  ];
  print("Heap Sort (Maps): ${sorting.heapSortMaps(maps, "a")}");
}