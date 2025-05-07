import java.util.Stack;

public class MinStack {

    // Approach 1: Using a pair (value, min) in the stack
    // Each element in the stack keeps track of the minimum value seen so far.
    static class MinStack1 {
        private Stack<Pair> stack;

        public MinStack1() {
            stack = new Stack<>();
        }

        public void push(int val) {
            int min = val;
            if (!stack.isEmpty()) {
                min = Math.min(min, stack.peek().min);
            }
            stack.push(new Pair(val, min));
        }

        public void pop() {
            stack.pop();
        }

        public int top() {
            return stack.peek().val;
        }

        public int getMin() {
            return stack.peek().min;
        }

        private static class Pair {
            int val;
            int min;

            public Pair(int val, int min) {
                this.val = val;
                this.min = min;
            }
        }
    }

    // Approach 2: Using two stacks (one for values, one for minimums)
    // One stack stores the values, and the other stores the minimums seen so far.
    static class MinStack2 {
        private Stack<Integer> stack;
        private Stack<Integer> minStack;

        public MinStack2() {
            stack = new Stack<>();
            minStack = new Stack<>();
        }

        public void push(int val) {
            stack.push(val);
            if (minStack.isEmpty() || val <= minStack.peek()) {
                minStack.push(val);
            }
        }

        public void pop() {
            int popped = stack.pop();
            if (!minStack.isEmpty() && popped == minStack.peek()) {
                minStack.pop();
            }
        }

        public int top() {
            return stack.peek();
        }

        public int getMin() {
            return minStack.peek();
        }
    }

    // Approach 3: Optimized two stacks (one for values, one for minimums with duplicates)
    //  The minStack only pushes when a new minimum is found
    static class MinStack3 {
        private Stack<Integer> stack;
        private Stack<Integer> minStack;

        public MinStack3() {
            stack = new Stack<>();
            minStack = new Stack<>();
        }

        public void push(int val) {
            stack.push(val);
            if (minStack.isEmpty() || val < minStack.peek()) { // Changed to '<'
                minStack.push(val);
            } else if (val == minStack.peek()) {
                minStack.push(val); //push duplicates
            }
        }

        public void pop() {
            int popped = stack.pop();
            if (!minStack.isEmpty() && popped == minStack.peek()) {
                minStack.pop();
            }
        }

        public int top() {
            return stack.peek();
        }

        public int getMin() {
            return minStack.peek();
        }
    }

    // Approach 4: Using a single stack and encoding min values
    // This approach uses a single stack, but encodes the current minimum value
    // along with the actual value.  This is a space optimization.
    static class MinStack4 {
        private Stack<Long> stack;
        private long min;

        public MinStack4() {
            stack = new Stack<>();
        }

        public void push(int val) {
            if (stack.isEmpty()) {
                min = val;
                stack.push((long)val); // Store directly as long
            } else {
                if (val < min) {
                    stack.push((long)val * 2 - min);  // Store encoded value
                    min = val;
                } else {
                    stack.push((long)val);
                }
            }
        }

        public void pop() {
            if (!stack.isEmpty()) {
                long top = stack.pop();
                if (top < min) {
                    min = 2 * min - top;  // Decode the minimum value.
                }
            }
        }

        public int top() {
            if (!stack.isEmpty()) {
                long top = stack.peek();
                if (top < min) {
                    return (int)min; // Return current min
                } else {
                    return (int)top;
                }
            }
            return -1; // Or throw an exception
        }

        public int getMin() {
            return (int)min;
        }
    }

    // Approach 5: Using a linked list with min tracking.
    // This approach uses a custom linked list node that also stores the minimum
    // value seen so far.
    static class MinStack5 {

        private static class Node {
            int val;
            int min;
            Node next;

            public Node(int val, int min, Node next) {
                this.val = val;
                this.min = min;
                this.next = next;
            }
        }

        private Node head;

        public MinStack5() {
            head = null;
        }

        public void push(int val) {
            int min = val;
            if (head != null) {
                min = Math.min(min, head.min);
            }
            head = new Node(val, min, head);
        }

        public void pop() {
            if (head != null) {
                head = head.next;
            }
        }

        public int top() {
            if (head != null) {
                return head.val;
            }
            return -1; // Or throw an exception.
        }

        public int getMin() {
            if (head != null) {
                return head.min;
            }
            return -1; // Or throw an exception.
        }
    }

    public static void main(String[] args) {
        // Example Usage for each MinStack implementation.  Added more tests.
        System.out.println("--- MinStack1 (Pair) ---");
        MinStack1 ms1 = new MinStack1();
        ms1.push(3);
        ms1.push(5);
        ms1.push(2);
        ms1.push(1);
        System.out.println("Top: " + ms1.top()); // 1
        System.out.println("Min: " + ms1.getMin()); // 1
        ms1.pop();
        System.out.println("Top: " + ms1.top()); // 2
        System.out.println("Min: " + ms1.getMin()); // 2
        ms1.pop();
        System.out.println("Min: " + ms1.getMin()); // 3

        System.out.println("\n--- MinStack2 (Two Stacks) ---");
        MinStack2 ms2 = new MinStack2();
        ms2.push(3);
        ms2.push(5);
        ms2.push(2);
        ms2.push(1);
        System.out.println("Top: " + ms2.top());
        System.out.println("Min: " + ms2.getMin());
        ms2.pop();
        System.out.println("Top: " + ms2.top());
        System.out.println("Min: " + ms2.getMin());
        ms2.pop();
        System.out.println("Min: " + ms2.getMin());

        System.out.println("\n--- MinStack3 (Two Stacks Optimized) ---");
        MinStack3 ms3 = new MinStack3();
        ms3.push(3);
        ms3.push(5);
        ms3.push(2);
        ms3.push(1);
        ms3.push(1); //push duplicate min
        System.out.println("Top: " + ms3.top());
        System.out.println("Min: " + ms3.getMin());
        ms3.pop();
        System.out.println("Top: " + ms3.top());
        System.out.println("Min: " + ms3.getMin());
        ms3.pop();
        System.out.println("Min: " + ms3.getMin());

        System.out.println("\n--- MinStack4 (Single Stack Encoded) ---");
        MinStack4 ms4 = new MinStack4();
        ms4.push(3);
        ms4.push(5);
        ms4.push(2);
        ms4.push(1);
        System.out.println("Top: " + ms4.top());
        System.out.println("Min: " + ms4.getMin());
        ms4.pop();
        System.out.println("Top: " + ms4.top());
        System.out.println("Min: " + ms4.getMin());
        ms4.pop();
        System.out.println("Min: " + ms4.getMin());

        System.out.println("\n--- MinStack5 (Linked List) ---");
        MinStack5 ms5 = new MinStack5();
        ms5.push(3);
        ms5.push(5);
        ms5.push(2);
        ms5.push(1);
        System.out.println("Top: " + ms5.top());
        System.out.println("Min: " + ms5.getMin());
        ms5.pop();
        System.out.println("Top: " + ms5.top());
        System.out.println("Min: " + ms5.getMin());
        ms5.pop();
        System.out.println("Min: " + ms5.getMin());
    }
}

