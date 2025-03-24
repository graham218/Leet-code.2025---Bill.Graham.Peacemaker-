import 'dart:math';

void main() {
  // Example usage:
  List<int> data = [1, 3, 5, 7, 9, 11];

  // 1. Basic Segment Tree (Class)
  SegmentTreeClass stClass = SegmentTreeClass(data);
  print("1. Basic Class - Range Sum (1, 3): ${stClass.query(1, 3)}");
  stClass.update(1, 2);
  print("1. Basic Class - Range Sum (1, 3) after update: ${stClass.query(1, 3)}");

  // 2. Segment Tree (Functions)
  List<int> stFunc = buildSegmentTreeFunc(data);
  print("2. Functions - Range Sum (1, 3): ${queryFunc(stFunc, data.length, 1, 3)}");
  updateFunc(stFunc, data.length, 1, 2);
  print("2. Functions - Range Sum (1, 3) after update: ${queryFunc(stFunc, data.length, 1, 3)}");

  // 3. Iterative Segment Tree
  SegmentTreeIterative stIter = SegmentTreeIterative(data);
  print("3. Iterative - Range Sum (1, 3): ${stIter.query(1, 3)}");
  stIter.update(1, 2);
  print("3. Iterative - Range Sum (1, 3) after update: ${stIter.query(1, 3)}");

  // 4. Segment Tree with Extension Methods
  List<int> stExtension = data.buildSegmentTreeExtension();
  print("4. Extension - Range Sum (1, 3): ${stExtension.queryExtension(data.length, 1, 3)}");
  data.updateExtension(stExtension, 1, 2);
  print("4. Extension - Range Sum (1, 3) after update: ${stExtension.queryExtension(data.length, 1, 3)}");

  // 5. Optimized Iterative Segment Tree
  SegmentTreeIterativeOptimized stOpt = SegmentTreeIterativeOptimized(data);
  print("5. Optimized Iterative - Range Sum (1, 3): ${stOpt.query(1, 3)}");
  stOpt.update(1, 2);
  print("5. Optimized Iterative - Range Sum (1, 3) after update: ${stOpt.query(1, 3)}");

  // 6. Segment Tree for Range Minimum Query (RMQ) - Stock Data Analysis
  List<double> stockPrices = [10.2, 10.5, 10.1, 10.8, 10.6, 10.9, 10.4];
  RmqSegmentTree rmqTree = RmqSegmentTree(stockPrices);
  int startDay = 2; // Day 2
  int endDay = 5;   // Day 5
  double minPrice = rmqTree.query(startDay, endDay);
  print("6. RMQ - Min Price between Day $startDay and $endDay: $minPrice"); // Output: 10.1
  rmqTree.update(3, 11.0); //update day 3 price
  minPrice = rmqTree.query(startDay, endDay);
  print("6. RMQ - Min Price between Day $startDay and $endDay after update: $minPrice");
}

// 1. Segment Tree using a Class
class SegmentTreeClass {
  late List<int> _st;
  late List<int> _array;

  SegmentTreeClass(List<int> arr) {
    _array = List.from(arr);
    int n = arr.length;
    _st = List<int>.filled(4 * n, 0);
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
    _array[index] = value;
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

// 2. Segment Tree using Functions
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

// 3. Iterative Segment Tree
class SegmentTreeIterative {
  late List<int> _st;
  late int _n;
  late List<int> _array;

  SegmentTreeIterative(List<int> arr) {
    _array = List.from(arr);
    _n = arr.length;
    _st = List<int>.filled(2 * _n, 0);
    for (int i = 0; i < _n; i++) {
      _st[_n + i] = arr[i];
    }
    for (int i = _n - 1; i > 0; i--) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  void update(int index, int value) {
    int i = _n + index;
    _st[i] = value;
    _array[index] = value;
    while (i > 1) {
      int parent = i ~/ 2;
      _st[parent] = _st[2 * parent] + _st[2 * parent + 1];
      i = parent;
    }
  }

  int query(int left, int right) {
    int l = _n + left;
    int r = _n + right;
    int sum = 0;
    while (l <= r) {
      if (l % 2 == 1) {
        sum += _st[l];
        l++;
      }
      if (r % 2 == 0) {
        sum += _st[r];
        r--;
      }
      l ~/= 2;
      r ~/= 2;
    }
    return sum;
  }
}

// 4. Segment Tree using Extension Methods
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
    this[index] = value;
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

// 5. Optimized Iterative Segment Tree
class SegmentTreeIterativeOptimized {
  late List<int> _st;
  late int _n;
  late List<int> _array;

  SegmentTreeIterativeOptimized(List<int> arr) {
    _array = List.from(arr);
    _n = arr.length;
    _st = List<int>.filled(2 * _n, 0);
    for (int i = 0; i < _n; i++) {
      _st[_n + i] = arr[i];
    }
    for (int i = _n - 1; i > 0; i--) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  void update(int index, int value) {
    int i = _n + index;
    _st[i] = value;
    _array[index] = value;
    for (i ~/= 2; i > 0; i ~/= 2) {
      _st[i] = _st[2 * i] + _st[2 * i + 1];
    }
  }

  int query(int left, int right) {
    int l = _n + left, r = _n + right;
    int sum = 0;
    while (l <= r) {
      if ((l & 1) == 1) {
        sum += _st[l++];
      }
      if ((r & 1) == 0) {
        sum += _st[r--];
      }
      l ~/= 2;
      r ~/= 2;
    }
    return sum;
  }
}

// 6. Segment Tree for Range Minimum Query (RMQ) - Stock Data Analysis
class RmqSegmentTree {
  late List<double> _st;
  late int _n;
  late List<double> _prices;

  RmqSegmentTree(List<double> prices) {
    _prices = List.from(prices);
    _n = prices.length;
    _st = List<double>.filled(4 * _n, 0);
    _build(0, _n - 1, 0);
  }

  void _build(int low, int high, int pos) {
    if (low == high) {
      _st[pos] = _prices[low];
      return;
    }
    int mid = (low + high) ~/ 2;
    _build(low, mid, 2 * pos + 1);
    _build(mid + 1, high, 2 * pos + 2);
    _st[pos] = min(_st[2 * pos + 1], _st[2 * pos + 2]);
  }

  void update(int index, double value) {
    _update(0, _n - 1, 0, index, value);
    _prices[index] = value;
  }

  void _update(int low, int high, int pos, int index, double value) {
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
    _st[pos] = min(_st[2 * pos + 1], _st[2 * pos + 2]);
  }

  double query(int left, int right) {
    return _query(0, _n - 1, 0, left, right);
  }

  double _query(int low, int high, int pos, int left, int right) {
    if (left > high || right < low) {
      return double.maxFinite;
    }
    if (low >= left && high <= right) {
      return _st[pos];
    }
    int mid = (low + high) ~/ 2;
    double l = _query(low, mid, 2 * pos + 1, left, right);
    double r = _query(mid + 1, high, 2 * pos + 2, left, right);
    return min(l, r);
  }
}
