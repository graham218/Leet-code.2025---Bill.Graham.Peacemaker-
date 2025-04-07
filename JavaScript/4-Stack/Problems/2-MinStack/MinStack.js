// Approach 1: Using an array to store both values and minimums
class MinStack1 {
  constructor() {
    this.stack = [];
  }

  push(val) {
    if (this.stack.length === 0 || val < this.getMin()) {
      this.stack.push({ val: val, min: val });
    } else {
      this.stack.push({ val: val, min: this.getMin() });
    }
  }

  pop() {
    if (this.stack.length > 0) {
      this.stack.pop();
    }
  }

  top() {
    if (this.stack.length > 0) {
      return this.stack[this.stack.length - 1].val;
    }
    return undefined;
  }

  getMin() {
    if (this.stack.length > 0) {
      return this.stack[this.stack.length - 1].min;
    }
    return Infinity;
  }
}

// Approach 2: Using two arrays, one for values and one for minimums
class MinStack2 {
  constructor() {
    this.stack = [];
    this.minStack = [];
  }

  push(val) {
    this.stack.push(val);
    if (this.minStack.length === 0 || val <= this.getMin()) {
      this.minStack.push(val);
    }
  }

  pop() {
    if (this.stack.length > 0) {
      const popped = this.stack.pop();
      if (popped === this.getMin()) {
        this.minStack.pop();
      }
    }
  }

  top() {
    if (this.stack.length > 0) {
      return this.stack[this.stack.length - 1];
    }
    return undefined;
  }

  getMin() {
    if (this.minStack.length > 0) {
      return this.minStack[this.minStack.length - 1];
    }
    return Infinity;
  }
}

// Approach 3: Using a linked list
class MinStackNode {
  constructor(val, min) {
    this.val = val;
    this.min = min;
    this.next = null;
  }
}

class MinStack3 {
  constructor() {
    this.head = null;
  }

  push(val) {
    if (!this.head || val < this.getMin()) {
      const newNode = new MinStackNode(val, val);
      newNode.next = this.head;
      this.head = newNode;
    } else {
      const newNode = new MinStackNode(val, this.getMin());
      newNode.next = this.head;
      this.head = newNode;
    }
  }

  pop() {
    if (this.head) {
      this.head = this.head.next;
    }
  }

  top() {
    if (this.head) {
      return this.head.val;
    }
    return undefined;
  }

  getMin() {
    if (this.head) {
      return this.head.min;
    }
    return Infinity;
  }
}

// Approach 4: Using a single stack and encoding min
class MinStack4 {
    constructor() {
        this.stack = [];
        this.minVal = Infinity;
    }

    push(val) {
        if (val <= this.minVal) {
            this.stack.push(this.minVal); // Store the previous min
            this.minVal = val;
        }
        this.stack.push(val);
    }

    pop() {
        if (this.stack.length > 0) {
            const popped = this.stack.pop();
            if (popped === this.minVal) {
                this.minVal = this.stack.pop() || Infinity; // Retrieve previous min
            }
        }
    }

    top() {
        if (this.stack.length > 0) {
            return this.stack[this.stack.length - 1];
        }
        return undefined;
    }

    getMin() {
        return this.minVal;
    }
}

// Approach 5: Using a stack and a min variable (optimized for space, handles duplicates correctly)
class MinStack5 {
  constructor() {
    this.stack = [];
    this.min = Infinity;
  }

  push(val) {
    if (val <= this.min) {
      this.stack.push(this.min); // Push the *previous* min
      this.min = val;
    }
    this.stack.push(val);
  }

  pop() {
    if (this.stack.length > 0) {
      const popped = this.stack.pop();
      if (popped === this.min) {
        this.min = this.stack.pop() ?? Infinity; // Use nullish coalescing
      }
    }
  }

  top() {
    if (this.stack.length > 0) {
      return this.stack[this.stack.length - 1];
    }
    return undefined;
  }

  getMin() {
    return this.min;
  }
}

// Test Cases
function runTestCases(MinStackClass, approachName) {
  console.log(`\n--- Test Cases for ${approachName} ---`);
  const minStack = new MinStackClass();

  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  console.log("push -2, 0, -3");
  console.log("getMin()", minStack.getMin()); // Output: -3
  console.log("top()", minStack.top());    // Output: -3
  minStack.pop();
  console.log("pop()");
  console.log("top()", minStack.top());    // Output: 0
  console.log("getMin()", minStack.getMin()); // Output: -2

  const minStack2 = new MinStackClass();
  minStack2.push(5);
  minStack2.push(2);
  minStack2.push(3);
  minStack2.push(1);
  console.log("push 5, 2, 3, 1");
  console.log("getMin()", minStack2.getMin()); // Should be 1
  minStack2.pop();
  console.log("pop()");
  console.log("getMin()", minStack2.getMin()); // Should be 2
  minStack2.pop();
  console.log("pop()");
  console.log("getMin()", minStack2.getMin()); // Should be 2
  minStack2.pop();
  console.log("pop()");
  console.log("getMin()", minStack2.getMin()); // Should be 5

  const minStack3 = new MinStackClass();
  minStack3.push(2);
  minStack3.push(2);
  minStack3.push(2);
  console.log("push 2, 2, 2");
  console.log("getMin()", minStack3.getMin()); // Should be 2
  minStack3.pop();
  console.log("pop()");
  console.log("getMin()", minStack3.getMin()); // Should be 2
  minStack3.pop();
  console.log("pop()");
  console.log("getMin()", minStack3.getMin()); // Should be 2

    const minStack4 = new MinStackClass();
    minStack4.push(3);
    minStack4.push(5);
    minStack4.push(2);
    minStack4.push(4);
    minStack4.push(5);
    minStack4.push(1);
    console.log("push 3, 5, 2, 4, 5, 1");
    console.log("getMin()", minStack4.getMin()); // Should be 1
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be 2
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be 2
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be 2
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be 3
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be 3
    minStack4.pop();
    console.log("pop()");
    console.log("getMin()", minStack4.getMin()); // Should be Infinity
}

// Run test cases for each implementation
runTestCases(MinStack1, "Approach 1: Using one array");
runTestCases(MinStack2, "Approach 2: Using two arrays");
runTestCases(MinStack3, "Approach 3: Using a linked list");
runTestCases(MinStack4, "Approach 4: Using a single stack and encoding min");
runTestCases(MinStack5, "Approach 5: Using a stack and a min variable");
