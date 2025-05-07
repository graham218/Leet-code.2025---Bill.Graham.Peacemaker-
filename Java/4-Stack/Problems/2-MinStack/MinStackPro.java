import java.util.Stack;
import java.util.ArrayList;
import java.util.List;
import java.util.EmptyStackException;
import java.util.Collections;

// Class to demonstrate different implementations of a Min Stack
public class MinStackImplementations {

    public static void main(String[] args) {
        // Example usage of each MinStack implementation
        System.out.println("Min Stack Implementations in Java\n");

        // Approach 1: Using a Pair Class
        System.out.println("Approach 1: Using a Pair Class");
        MinStackWithPair stack1 = new MinStackWithPair();
        testMinStack(stack1);

        // Approach 2: Using Two Stacks
        System.out.println("\nApproach 2: Using Two Stacks");
        MinStackWithTwoStacks stack2 = new MinStackWithTwoStacks();
        testMinStack(stack2);

        // Approach 3: Optimized Single Stack
        System.out.println("\nApproach 3: Optimized Single Stack");
        MinStackOptimized stack3 = new MinStackOptimized();
        testMinStack(stack3);

        // Approach 4: Using a List
        System.out.println("\nApproach 4: Using a List");
        MinStackWithList stack4 = new MinStackWithList();
        testMinStack(stack4);

        // Approach 5: Using Collections.min
        System.out.println("\nApproach 5: Using Collections.min");
        MinStackWithCollectionsMin stack5 = new MinStackWithCollectionsMin();
        testMinStack(stack5);
    }

    // Helper method to test the MinStack implementations
    private static void testMinStack(MinStackInterface stack) {
        stack.push(3);
        System.out.println("Pushed 3, Current Min: " + stack.getMin()); // Expected: 3
        stack.push(5);
        System.out.println("Pushed 5, Current Min: " + stack.getMin()); // Expected: 3
        stack.push(2);
        System.out.println("Pushed 2, Current Min: " + stack.getMin()); // Expected: 2
        stack.push(1);
        System.out.println("Pushed 1, Current Min: " + stack.getMin()); // Expected: 1

        System.out.println("Top: " + stack.top()); // Expected: 1
        System.out.println("Min: " + stack.getMin()); // Expected: 1

        stack.pop();
        System.out.println("Popped, Current Min: " + stack.getMin()); // Expected: 2
        stack.pop();
        System.out.println("Popped, Current Min: " + stack.getMin()); // Expected: 3
        System.out.println("Top: " + stack.top());
    }

    // Interface for MinStack to ensure all implementations adhere to the same methods
    interface MinStackInterface {
        void push(int val);
        void pop();
        int top();
        int getMin();
    }

    // Approach 1: Using a Pair Class
    // Uses a custom Pair class to store both the value and the minimum value at that point in the stack.
    static class MinStackWithPair implements MinStackInterface {
        private static class Pair {
            int value;
            int min;

            Pair(int value, int min) {
                this.value = value;
                this.min = min;
            }
        }

        private Stack<Pair> stack;

        public MinStackWithPair() {
            this.stack = new Stack<>();
        }

        @Override
        public void push(int val) {
            if (stack.isEmpty()) {
                stack.push(new Pair(val, val));
            } else {
                Pair top = stack.peek();
                stack.push(new Pair(val, Math.min(val, top.min)));
            }
        }

        @Override
        public void pop() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            stack.pop();
        }

        @Override
        public int top() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            return stack.peek().value;
        }

        @Override
        public int getMin() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            return stack.peek().min;
        }
    }

    // Approach 2: Using Two Stacks
    // Uses one stack to store the values and another stack to store the minimum values.
    static class MinStackWithTwoStacks implements MinStackInterface {
        private Stack<Integer> stack;
        private Stack<Integer> minStack;

        public MinStackWithTwoStacks() {
            this.stack = new Stack<>();
            this.minStack = new Stack<>();
        }

        @Override
        public void push(int val) {
            stack.push(val);
            if (minStack.isEmpty() || val <= minStack.peek()) {
                minStack.push(val);
            }
        }

        @Override
        public void pop() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            int popped = stack.pop();
            if (!minStack.isEmpty() && popped == minStack.peek()) {
                minStack.pop();
            }
        }

        @Override
        public int top() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            return stack.peek();
        }

        @Override
        public int getMin() {
            if (minStack.isEmpty()) {
                throw new EmptyStackException();
            }
            return minStack.peek();
        }
    }

    // Approach 3: Optimized Single Stack
    // Uses a single stack, but stores the difference between the value and the current minimum
    // if the value is smaller than the current minimum.
    static class MinStackOptimized implements MinStackInterface {
        private Stack<Long> stack;
        private long min; // Use long to handle potential overflow when subtracting

        public MinStackOptimized() {
            this.stack = new Stack<>();
        }

        @Override
        public void push(int val) {
            if (stack.isEmpty()) {
                min = val;
                stack.push(0L); // Store 0 to indicate the first element
            } else {
                long diff = val - min;
                stack.push(diff);
                if (diff < 0) {
                    min = val;
                }
            }
        }

        @Override
        public void pop() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            long diff = stack.pop();
            if (diff < 0) {
                min = min - diff; // Correctly restore the previous min
            }
        }

        @Override
        public int top() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            long diff = stack.peek();
            if (diff < 0) {
                return (int) min;
            } else {
                return (int) (min + diff);
            }
        }

        @Override
        public int getMin() {
            if (stack.isEmpty()) {
                throw new EmptyStackException();
            }
            return (int) min;
        }
    }

    // Approach 4: Using a List
    // Uses a List to store the elements and calculates the minimum on demand.
    static class MinStackWithList implements MinStackInterface {
        private List<Integer> list;

        public MinStackWithList() {
            this.list = new ArrayList<>();
        }

        @Override
        public void push(int val) {
            list.add(val);
        }

        @Override
        public void pop() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            list.remove(list.size() - 1);
        }

        @Override
        public int top() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            return list.get(list.size() - 1);
        }

        @Override
        public int getMin() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            int min = list.get(0);
            for (int i = 1; i < list.size(); i++) {
                if (list.get(i) < min) {
                    min = list.get(i);
                }
            }
            return min;
        }
    }

    // Approach 5: Using Collections.min
    // Uses a List and the Collections.min() method to find the minimum.
    static class MinStackWithCollectionsMin implements MinStackInterface {
        private List<Integer> list;

        public MinStackWithCollectionsMin() {
            this.list = new ArrayList<>();
        }

        @Override
        public void push(int val) {
            list.add(val);
        }

        @Override
        public void pop() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            list.remove(list.size() - 1);
        }

        @Override
        public int top() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            return list.get(list.size() - 1);
        }

        @Override
        public int getMin() {
            if (list.isEmpty()) {
                throw new EmptyStackException();
            }
            return Collections.min(list);
        }
    }
}

