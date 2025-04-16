/*
    Min Stack Problem:

    Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

    Implement a MinStack class with the following methods:

    -   push(val): Pushes the element val onto the stack.
    -   pop(): Removes the element on the top of the stack.
    -   top(): Gets the top element of the stack.
    -   getMin(): Retrieves the minimum element in the stack.

    Constraints:
    -   O(1) time complexity for all operations.

    Here are five different approaches to solve this problem, each with a slightly different trade-off:
*/

console.log("Min Stack Implementations in JavaScript");

// --------------------------------------------------------------------------
// 1.  Using a Pair (Value and Minimum)
// --------------------------------------------------------------------------
//   -   Store each element along with the minimum value seen so far.
//   -   push():  If the new value is smaller than the current minimum, update the minimum.
//   -   pop():   The minimum for the previous element is stored with that element.
//   -   top():   Return the value of the top pair.
//   -   getMin(): Return the minimum of the top pair.
//   -   Advantage:  Simple and efficient.
//   -   Disadvantage: Uses a bit more space as it duplicates minimum values.
class MinStack1 {
    constructor() {
        this.stack = [];
    }

    push(val) {
        const min = this.stack.length === 0 ? val : Math.min(val, this.getMin());
        this.stack.push({ value: val, min: min });
        console.log(`MinStack1: push(${val}), stack:`, this.stack);
    }

    pop() {
        if (this.stack.length > 0) {
            this.stack.pop();
        }
        console.log('MinStack1: pop(), stack:', this.stack);
    }

    top() {
        if (this.stack.length > 0) {
            const topElement = this.stack[this.stack.length - 1];
            console.log('MinStack1: top()', topElement.value);
            return topElement.value;
        }
        return undefined;
    }

    getMin() {
        if (this.stack.length > 0) {
            const topElement = this.stack[this.stack.length - 1];
            console.log('MinStack1: getMin()', topElement.min);
            return topElement.min;
        }
        return undefined;
    }
}

// --------------------------------------------------------------------------
// 2. Using Two Stacks (Value Stack and Minimum Stack)
// --------------------------------------------------------------------------
//   -   Use one stack to store the values and another stack to store the minimums.
//   -   push():  Push the value onto the value stack.  Push the minimum onto the minimum stack.
//   -   pop():   Pop from both stacks.
//   -   top():   Return the top of the value stack.
//   -   getMin(): Return the top of the minimum stack.
//   -    Advantage: Clean separation of values and minimums.
//   -   Disadvantage: Requires extra space for the minimum stack.
class MinStack2 {
    constructor() {
        this.valueStack = [];
        this.minStack = [];
    }

    push(val) {
        this.valueStack.push(val);
        if (this.minStack.length === 0 || val <= this.getMin()) {
            this.minStack.push(val);
        }
        console.log(`MinStack2: push(${val}), valueStack:`, this.valueStack, "minStack:", this.minStack);

    }

    pop() {
        if (this.valueStack.length > 0) {
            const poppedValue = this.valueStack.pop();
            if (poppedValue === this.getMin()) {
                this.minStack.pop();
            }
        }
        console.log('MinStack2: pop(), valueStack:', this.valueStack, "minStack:", this.minStack);
    }

    top() {
        if (this.valueStack.length > 0) {
            const topValue = this.valueStack[this.valueStack.length - 1];
            console.log('MinStack2: top()', topValue);
            return topValue;
        }
        return undefined;
    }

    getMin() {
        if (this.minStack.length > 0) {
            const minVal = this.minStack[this.minStack.length - 1];
            console.log('MinStack2: getMin()', minVal);
            return minVal;
        }
        return undefined;
    }
}

// --------------------------------------------------------------------------
// 3. Optimized Two Stacks (Minimum Stack Only When Needed)
// --------------------------------------------------------------------------
//   -   Similar to approach 2, but the minimum stack only stores *decreasing* minimums.
//   -   push():  Push the value onto the value stack.  If the new value is <= the current minimum, push it onto the minimum stack.
//   -   pop():   Pop from the value stack.  If the popped value was the minimum, pop from the minimum stack.
//   -   top():   Return the top of the value stack.
//   -   getMin(): Return the top of the minimum stack.
//   -   Advantage: More space-efficient than the previous approach, especially with many duplicates or increasing sequences.
//   -   Disadvantage: Slightly more complex logic.
class MinStack3 {
    constructor() {
        this.valueStack = [];
        this.minStack = [];
    }

    push(val) {
        this.valueStack.push(val);
        if (this.minStack.length === 0 || val <= this.minStack[this.minStack.length - 1]) {
            this.minStack.push(val);
        }
        console.log(`MinStack3: push(${val}), valueStack:`, this.valueStack, "minStack:", this.minStack);
    }

    pop() {
        if (this.valueStack.length > 0) {
            const poppedValue = this.valueStack.pop();
            if (poppedValue === this.minStack[this.minStack.length - 1]) {
                this.minStack.pop();
            }
        }
        console.log('MinStack3: pop(), valueStack:', this.valueStack, "minStack:", this.minStack);
    }

    top() {
        if (this.valueStack.length > 0) {
            const topValue = this.valueStack[this.valueStack.length - 1];
            console.log('MinStack3: top()', topValue);
            return topValue;
        }
        return undefined;
    }

    getMin() {
        if (this.minStack.length > 0) {
            const minVal = this.minStack[this.minStack.length - 1];
            console.log('MinStack3: getMin()', minVal);
            return minVal;
        }
        return undefined;
    }
}

// --------------------------------------------------------------------------
// 4. Using a Linked List Node
// --------------------------------------------------------------------------
//    -  Use a custom linked list node, where each node stores the value and the minimum value seen so far.
//    -  push(): Create a new node and make it the new head.
//    -  pop():  Remove the head.
//    -  top():  Return the value of the head.
//    -  getMin(): Return the min of the head.
//    -  Advantage: Uses only the memory needed.
//    -  Disadvantage: More complex implementation.
class MinStack4 {
  constructor() {
    this.head = null;
  }

  push(val) {
    const min = this.head ? Math.min(val, this.head.min) : val;
    const newNode = {
      value: val,
      min: min,
      next: this.head,
    };
    this.head = newNode;
    console.log(`MinStack4: push(${val}), head:`, this.head);
  }

  pop() {
    if (this.head) {
      this.head = this.head.next;
    }
    console.log("MinStack4: pop(), head:", this.head);
  }

  top() {
    if (this.head) {
      console.log("MinStack4: top()", this.head.value);
      return this.head.value;
    }
    return undefined;
  }

  getMin() {
    if (this.head) {
      console.log("MinStack4: getMin()", this.head.min);
      return this.head.min;
    }
    return undefined;
  }
}

// --------------------------------------------------------------------------
// 5. Using a Single Stack and Encoding Minimum
// --------------------------------------------------------------------------
//   -   Store the actual value and the minimum value in a single stack, but encode them together.
//   -   push(x):
//       -   If the stack is empty, push (x, x).
//       -   Otherwise, push (x, min(x, currentMin)).
//   -   pop():
//       -   When popping, the top element contains (value, currentMin).
//       -   The previous minimum is stored *before* the current minimum.
//   -    Advantage: Uses only one stack.
//   -    Disadvantage: Can lead to integer overflow issues in some languages, and is more complex.
class MinStack5 {
    constructor() {
        this.stack = [];
    }

    push(val) {
        if (this.stack.length === 0) {
            this.stack.push(val); // Push the value
            this.stack.push(val); // And the minimum
        } else {
            const currentMin = this.getMin();
            this.stack.push(val);
            this.stack.push(Math.min(val, currentMin));
        }
        console.log(`MinStack5: push(${val}), stack:`, this.stack);
    }

    pop() {
        if (this.stack.length > 0) {
            this.stack.pop(); // Pop min
            this.stack.pop(); // Pop value
        }
        console.log('MinStack5: pop(), stack:', this.stack);
    }

    top() {
        if (this.stack.length > 0) {
            const topValue = this.stack[this.stack.length - 2]; // Get the value (2nd from the top)
             console.log('MinStack5: top()', topValue);
            return topValue;
        }
        return undefined;
    }

    getMin() {
        if (this.stack.length > 0) {
            const minValue = this.stack[this.stack.length - 1];
            console.log('MinStack5: getMin()', minValue);
            return minValue;
        }
        return undefined;
    }
}



// --- Example Usage ---
console.log("\n--- Example Usage ---");

const minStack1 = new MinStack1();
minStack1.push(-2);
minStack1.push(0);
minStack1.push(-3);
console.log("Min of Stack1:", minStack1.getMin()); // return -3
minStack1.pop();
console.log("Top of Stack1:", minStack1.top());    // return 0
console.log("Min of Stack1:", minStack1.getMin()); // return -2

const minStack2 = new MinStack2();
minStack2.push(-2);
minStack2.push(0);
minStack2.push(-3);
console.log("Min of Stack2:", minStack2.getMin());
minStack2.pop();
console.log("Top of Stack2:", minStack2.top());
console.log("Min of Stack2:", minStack2.getMin());

const minStack3 = new MinStack3();
minStack3.push(-2);
minStack3.push(0);
minStack3.push(-3);
console.log("Min of Stack3:", minStack3.getMin());
minStack3.pop();
console.log("Top of Stack3:", minStack3.top());
console.log("Min of Stack3:", minStack3.getMin());

const minStack4 = new MinStack4();
minStack4.push(-2);
minStack4.push(0);
minStack4.push(-3);
console.log("Min of Stack4:", minStack4.getMin());
minStack4.pop();
console.log("Top of Stack4:", minStack4.top());
console.log("Min of Stack4:", minStack4.getMin());

const minStack5 = new MinStack5();
minStack5.push(-2);
minStack5.push(0);
minStack5.push(-3);
console.log("Min of Stack5:", minStack5.getMin());
minStack5.pop();
console.log("Top of Stack5:", minStack5.top());
console.log("Min of Stack5:", minStack5.getMin());
