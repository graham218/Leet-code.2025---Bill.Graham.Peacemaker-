import 'dart:math';

void main() {
  // Example usage:
  List<int> arr = [1, 3, 5, 7, 9, 11];

  // Approach 1: Using a Class
  SegmentTreeClass stClass = SegmentTreeClass(arr);
  print("Approach 1 - Range Sum (1, 3): ${stClass.query(1, 3)}"); // Output: 15
  stClass.update(1, 2);
  print("Approach 1 - Range Sum (1, 3) after update: ${stClass.query(1, 3)}"); // Output: 13

  // Approach 2: Using Functions
  List<int> stFunc = buildSegmentTreeFunc(arr);
  print("Approach 2 - Range Sum (1, 3): ${queryFunc(stFunc, arr.length, 1, 3)}"); // Output: 15
  updateFunc(stFunc, arr.length, 1, 2);
  print("Approach 2 - Range Sum (1, 3) after update: ${queryFunc(stFunc, arr.length, 1, 3)}"); // Output: 13

  // Approach 3: Iterative Segment Tree
  SegmentTreeIterative stIter = SegmentTreeIterative(arr);
  print("Approach 3 - Range Sum (1, 3): ${stIter.query(1, 3)}"); // Output: 15
  stIter.update(1, 2);
  print("Approach 3 - Range Sum (1, 3) after update: ${stIter.query(1, 3)}"); // Output: 13

  // Approach 4: Using Extension Methods
  List<int> stExtension = arr.buildSegmentTreeExtension();
  print("Approach 4 - Range Sum (1, 3): ${stExtension.queryExtension(arr.length, 1, 3)}");
  arr.updateExtension(stExtension, 1, 2);
  print("Approach 4 - Range Sum (1, 3) after update: ${stExtension.queryExtension(arr.length, 1, 3)}");

  // Approach 5: Optimized iterative
  SegmentTreeIterativeOptimized stOpt = SegmentTreeIterativeOptimized(arr);
  print("Approach 5 - Range Sum (1, 3): ${stOpt.query(1, 3)}"); // Output: 15
  stOpt.update(1, 2);
  print("Approach 5 - Range Sum (1, 3) after update: ${stOpt.query(1, 3)}"); // Output: 13
}

// Approach 1: Segment Tree using a Class
class SegmentTreeClass {
  late List<int> _st;
  late List<int> _array; //keep a copy

  SegmentTreeClass(List<int> arr) {
    _array = List.from(arr); // important to copy
    int n = arr.length;
    _st = List<int>.filled(4 * n, 0); // Max size of segment tree is 4*n
    _build(arr, 0, n - 1, 0);
  }

  void _build(List<int> arr, int low, int high, int pos) {
    if (low == high) {
      _st[pos] = arr[low];
      return;
    }
    int mid = (low + high) ~/ 2;
    _build(arr, low, mid, 2 * pos + 1);
    _build(arr, mid + 1, high, 2 * pos + 2);
    _st[pos] = _st[2 * pos + 1] + _st[2 * pos + 2];
  }

  void update(int index, int value) {
    _update(0, _array.length - 1, 0, index, value);
    _array[index] = value; //keep array updated
  }

  void _update(int low, int high, int pos, int index, int value) {
    if (low == high) {
      _st[pos] = value;
      return;
    }
    int mid = (low + high) ~/ 2;
    if (index <= mid) {
      _update(low, mid, 2 * pos + 1, index, value);
    } else {
      _update(mid + 1, high, 2 * pos + 2, index, value);
    }
    _st[pos] = _st[2 * pos + 1] + _st[2 * pos + 2];
  }

  int query(int left, int right) {
    return _query(0, _array.length - 1, 0, left, right);
  }

  int _query(int low, int high, int pos, int left, int right) {
    if (left > high || right < low) {
      return 0;
    }
    if (low >= left && high <= right) {
      return _st[pos];
    }
    int mid = (low + high) ~/ 2;
    int l = _query(low, mid, 2 * pos + 1, left, right);
    int r = _query(mid + 1, high, 2 * pos + 2, left, right);
    return l + r;
  }
}

// Approach 2: Segment Tree using Functions
List<int> buildSegmentTreeFunc(List<int> arr) {
  int n = arr.length;
  List<int> st = List<int>.filled(4 * n, 0);
  _buildFunc(arr, 0, n - 1, 0, st);
  return st;
}

void _buildFunc(List<int> arr, int low, int high, int pos, List<int> st) {
  if (low == high) {
    st[pos] = arr[low];
    return;
  }
  int mid = (low + high) ~/ 2;
  _buildFunc(arr, low, mid, 2 * pos + 1, st);
  _buildFunc(arr, mid + 1, high, 2 * pos + 2, st);
  st[pos] = st[2 * pos + 1] + st[2 * pos + 2];
}

void updateFunc(List<int> st, int n, int index, int value) {
  _updateFunc(0, n - 1, 0, index, value, st);
}

void _updateFunc(int low, int high, int pos, int index, int value, List<int> st) {
  if (low == high) {
    st[pos] = value;
    return;
  }
  int mid = (low + high) ~/ 2;
  if (index <= mid) {
    _updateFunc(low, mid, 2 * pos + 1, index, value, st);
  } else {
    _updateFunc(mid + 1, high, 2 * pos + 2, index, value, st);
  }
  st[pos] = st[2 * pos + 1] + st[2 * pos + 2];
}

int queryFunc(List<int> st, int n, int left, int right) {
  return _queryFunc(0, n - 1, 0, left, right, st);
}

int _queryFunc(int low, int high, int pos, int left, int right, List<int> st) {
  if (left > high || right < low) {
    return 0;
  }
  if (low >= left && high <= right) {
    return st[pos];
  }
  int mid = (low + high) ~/ 2;
  int l = _queryFunc(low, mid, 2 * pos + 1, left, right, st);
  int r = _queryFunc(mid + 1, high, 2 * pos + 2, left, right, st);
  return l + r;
}

// Approach 3: Iterative Segment Tree
class SegmentTreeIterative {
  late List<int> _st;
  late int _n;
  late List<int> _array;

  SegmentTreeIterative(List<int> arr) {
    _array = List.from(arr);
    _n = arr.length;
    _st = List<int>.filled(2 * _n, 0); // Size: 2n
    // Copy array to the bottom level of segment tree
    for (int i = 0; i < _n; i++) {
      _st[_n + i] = arr[i];
    }
    // Build the tree from the bottom up
    for (int i = _n - 1; i > 0; i--) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  void update(int index, int value) {
    // Leaf node index in the segment tree
    int i = _n + index;
    _st[i] = value;
    _array[index] = value; //keep track
    // Update the parent nodes
    while (i > 1) {
      int parent = i ~/ 2;
      _st[parent] = _st[2 * parent] + _st[2 * parent + 1];
      i = parent;
    }
  }

  int query(int left, int right) {
    // Leaf node index for left and right
    int l = _n + left;
    int r = _n + right;
    int sum = 0;
    while (l <= r) {
      if (l % 2 == 1) { //if l is odd
        sum += _st[l];
        l++;
      }
      if (r % 2 == 0) { //if r is even
        sum += _st[r];
        r--;
      }
      l ~/= 2;
      r ~/= 2;
    }
    return sum;
  }
}

// Approach 4: Segment Tree using Extension Methods
extension SegmentTreeExtension on List<int> {
  List<int> buildSegmentTreeExtension() {
    int n = this.length;
    List<int> st = List<int>.filled(4 * n, 0);
    _buildExtension(this, 0, n - 1, 0, st);
    return st;
  }

  void _buildExtension(List<int> arr, int low, int high, int pos, List<int> st) {
    if (low == high) {
      st[pos] = arr[low];
      return;
    }
    int mid = (low + high) ~/ 2;
    _buildExtension(arr, low, mid, 2 * pos + 1, st);
    _buildExtension(arr, mid + 1, high, 2 * pos + 2, st);
    st[pos] = st[2 * pos + 1] + st[2 * pos + 2];
  }

  void updateExtension(List<int> st, int index, int value) {
    _updateExtension(0, this.length - 1, 0, index, value, st);
    this[index] = value; //keep original array updated.
  }

  void _updateExtension(int low, int high, int pos, int index, int value, List<int> st) {
    if (low == high) {
      st[pos] = value;
      return;
    }
    int mid = (low + high) ~/ 2;
    if (index <= mid) {
      _updateExtension(low, mid, 2 * pos + 1, index, value, st);
    } else {
      _updateExtension(mid + 1, high, 2 * pos + 2, index, value, st);
    }
    st[pos] = st[2 * pos + 1] + st[2 * pos + 2];
  }

  int queryExtension(int n, int left, int right) {
    return _queryExtension(0, n - 1, 0, left, right, this);
  }

  int _queryExtension(int low, int high, int pos, int left, int right, List<int> st) {
    if (left > high || right < low) {
      return 0;
    }
    if (low >= left && high <= right) {
      return st[pos];
    }
    int mid = (low + high) ~/ 2;
    int l = _queryExtension(low, mid, 2 * pos + 1, left, right, st);
    int r = _queryExtension(mid + 1, high, 2 * pos + 2, left, right, st);
    return l + r;
  }
}

// Approach 5: Iterative Segment Tree Optimized
class SegmentTreeIterativeOptimized {
  late List<int> _st;
  late int _n;
  late List<int> _array;

  SegmentTreeIterativeOptimized(List<int> arr) {
    _array = List.from(arr);
    _n = arr.length;
    _st = List<int>.filled(2 * _n, 0);
    // Copy the input array to the leaves of the segment tree.
    for (int i = 0; i < _n; i++) {
      _st[_n + i] = arr[i];
    }
    // Build the segment tree from the leaves up to the root.
    for (int i = _n - 1; i > 0; i--) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  void update(int index, int value) {
    int i = _n + index;
    _st[i] = value;
    _array[index] = value;
    // Optimized update: iterate and update
    for (i ~/= 2; i > 0; i ~/= 2) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  int query(int left, int right) {
    int l = _n + left, r = _n + right;
    int sum = 0;

    while (l <= r) {
      if ((l & 1) == 1) {  // Check if l is odd using bitwise AND
        sum += _st[l++];
      }
      if ((r & 1) == 0) {  // Check if r is even using bitwise AND
        sum += _st[r--];
      }
      l ~/= 2;
      r ~/= 2;
    }
    return sum;
  }
}
