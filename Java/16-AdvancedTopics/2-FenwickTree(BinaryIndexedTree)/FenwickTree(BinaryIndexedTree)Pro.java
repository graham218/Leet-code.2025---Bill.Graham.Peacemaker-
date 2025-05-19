/*
 * Fenwick Tree (Binary Indexed Tree) Implementations in Java
 *
 * Real-world Inspired Approaches:
 * 1. Basic Fenwick Tree for range sum queries (e.g., stock price analysis).
 * 2. Point Updates and Range Queries (e.g., cumulative rainfall analysis).
 * 3. Range Updates and Point Queries (e.g., salary increment adjustments).
 * 4. 2D Fenwick Tree (e.g., image processing - cumulative brightness).
 * 5. Inverse Fenwick Tree for prefix frequency counting (e.g., rank tracking).
 */

// 1. Basic Fenwick Tree for range sum queries (e.g., stock price analysis)
class FenwickTree {
    private int[] tree;

    public FenwickTree(int size) {
        tree = new int[size + 1]; // 1-based indexing
    }

    public void update(int index, int value) {
        while (index < tree.length) {
            tree[index] += value;
            index += index & -index;
        }
    }

    public int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    public int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
    }
}

// 2. Point Updates and Range Queries (e.g., cumulative rainfall analysis)
class FenwickTreeRangeSum {
    private int[] tree;

    public FenwickTreeRangeSum(int size) {
        tree = new int[size + 1];
    }

    public void add(int index, int delta) {
        while (index < tree.length) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    public int prefixSum(int index) {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }

    public int rangeSum(int left, int right) {
        return prefixSum(right) - prefixSum(left - 1);
    }
}

// 3. Range Updates and Point Queries (e.g., salary increment adjustments)
class FenwickTreeRangeUpdate {
    private int[] tree;

    public FenwickTreeRangeUpdate(int size) {
        tree = new int[size + 2];
    }

    public void rangeUpdate(int left, int right, int delta) {
        update(left, delta);
        update(right + 1, -delta);
    }

    private void update(int index, int delta) {
        while (index < tree.length) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    public int pointQuery(int index) {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }
}

// 4. 2D Fenwick Tree (e.g., image processing - cumulative brightness)
class FenwickTree2D {
    private int[][] tree;
    private int rows, cols;

    public FenwickTree2D(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        tree = new int[rows + 1][cols + 1];
    }

    public void update(int row, int col, int delta) {
        for (int i = row; i <= rows; i += i & -i) {
            for (int j = col; j <= cols; j += j & -j) {
                tree[i][j] += delta;
            }
        }
    }

    public int query(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= i & -i) {
            for (int j = col; j > 0; j -= j & -j) {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    public int rangeQuery(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1);
    }
}

// 5. Inverse Fenwick Tree for prefix frequency counting (e.g., rank tracking)
class FenwickTreeFrequency {
    private int[] tree;
    private int size;

    public FenwickTreeFrequency(int size) {
        this.size = size;
        tree = new int[size + 1];
    }

    public void insert(int value) {
        while (value <= size) {
            tree[value] += 1;
            value += value & -value;
        }
    }

    public int count(int value) {
        int result = 0;
        while (value > 0) {
            result += tree[value];
            value -= value & -value;
        }
        return result;
    }

    public int findKth(int k) {
        int low = 1, high = size, ans = -1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (count(mid) >= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
}

// Main method for testing all implementations
public class Main {
    public static void main(String[] args) {
        // 1. Basic Fenwick Tree (stock price example)
        FenwickTree stockPrices = new FenwickTree(10);
        stockPrices.update(1, 100);
        stockPrices.update(2, 120);
        stockPrices.update(3, 130);
        System.out.println("Stock range sum (1 to 3): " + stockPrices.rangeQuery(1, 3));

        // 2. Point Updates and Range Queries (rainfall example)
        FenwickTreeRangeSum rainfall = new FenwickTreeRangeSum(10);
        rainfall.add(2, 15);
        rainfall.add(4, 25);
        System.out.println("Rainfall from 2 to 4: " + rainfall.rangeSum(2, 4));

        // 3. Range Updates and Point Queries (salary adjustment example)
        FenwickTreeRangeUpdate salary = new FenwickTreeRangeUpdate(10);
        salary.rangeUpdate(3, 6, 500);
        System.out.println("Salary at position 5 after increment: " + salary.pointQuery(5));

        // 4. 2D Fenwick Tree (image brightness example)
        FenwickTree2D image = new FenwickTree2D(5, 5);
        image.update(2, 3, 10);
        image.update(3, 4, 20);
        System.out.println("Brightness in region (2,3)-(3,4): " + image.rangeQuery(2, 3, 3, 4));

        // 5. Prefix Frequency Counting (rank tracker example)
        FenwickTreeFrequency ranks = new FenwickTreeFrequency(100);
        ranks.insert(10);
        ranks.insert(20);
        ranks.insert(15);
        System.out.println("Number of values <= 15: " + ranks.count(15));
        System.out.println("Find 2nd smallest value: " + ranks.findKth(2));
    }
}
