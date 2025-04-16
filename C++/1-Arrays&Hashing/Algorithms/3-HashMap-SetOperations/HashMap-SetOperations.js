// 1. Using Object as a HashMap (Basic Approach)
(() => {
  console.log("1. Using Object as a HashMap");

  // Create an empty object to simulate a HashMap
  const hashMap = {};

  // Insert key-value pairs
  hashMap.key1 = "value1";
  hashMap.key2 = "value2";
  hashMap.key3 = "value3";

  console.log("Initial HashMap:", hashMap); // Output: { key1: 'value1', key2: 'value2', key3: 'value3' }

  // Get a value by key
  const value2 = hashMap.key2;
  console.log("Value for key2:", value2); // Output: value2

  // Check if a key exists
  const hasKey2 = hashMap.hasOwnProperty("key2"); // Use hasOwnProperty
  const hasKey4 = hashMap.hasOwnProperty("key4");
  console.log("Has key2:", hasKey2); // Output: true
  console.log("Has key4:", hasKey4); // Output: false

  // Update a value
  hashMap.key2 = "newvalue2";
  console.log("HashMap after update:", hashMap); // Output: { key1: 'value1', key2: 'newvalue2', key3: 'value3' }

  // Delete a key-value pair
  delete hashMap.key1;
  console.log("HashMap after deletion:", hashMap); // Output: { key2: 'newvalue2', key3: 'value3' }

  // Iterate through the keys
  console.log("Iterating through keys:");
  for (const key in hashMap) {
    if (hashMap.hasOwnProperty(key)) { // Important: Check hasOwnProperty in loops
      console.log("Key:", key, "Value:", hashMap[key]);
    }
  }

  // Get all keys
  const keys = Object.keys(hashMap);
  console.log("Keys:", keys); // Output: [ 'key2', 'key3' ]

  // Get all values
  const values = Object.values(hashMap);
  console.log("Values:", values); // Output: [ 'newvalue2', 'value3' ]

  // Size of the HashMap
  const size = Object.keys(hashMap).length;
  console.log("Size of HashMap:", size); // Output: 2

  // Clear the HashMap
  for (const key in hashMap) {
      if (hashMap.hasOwnProperty(key)) {
          delete hashMap[key];
      }
  }
  console.log("HashMap after clear:", hashMap); // Output: {}

})();

// 2. Using JavaScript Map (Recommended for HashMaps)
(() => {
  console.log("\n2. Using JavaScript Map");

  // Create a new Map
  const map = new Map();

  // Insert key-value pairs (using set())
  map.set("key1", "value1");
  map.set("key2", "value2");
  map.set("key3", "value3");

  console.log("Initial Map:", map); // Output: Map { 'key1' => 'value1', 'key2' => 'value2', 'key3' => 'value3' }

  // Get a value by key (using get())
  const value2 = map.get("key2");
  console.log("Value for key2:", value2); // Output: value2

  // Check if a key exists (using has())
  const hasKey2 = map.has("key2");
  const hasKey4 = map.has("key4");
  console.log("Has key2:", hasKey2); // Output: true
  console.log("Has key4:", hasKey4); // Output: false

  // Update a value (using set())
  map.set("key2", "newvalue2");
  console.log("Map after update:", map); // Output: Map { 'key1' => 'value1', 'key2' => 'newvalue2', 'key3' => 'value3' }

  // Delete a key-value pair (using delete())
  map.delete("key1");
  console.log("Map after deletion:", map); // Output: Map { 'key2' => 'newvalue2', 'key3' => 'value3' }

  // Iterate through the Map (using for...of and entries())
  console.log("Iterating through Map:");
  for (const [key, value] of map.entries()) {
    console.log("Key:", key, "Value:", value);
  }
  // Alternative iteration
  console.log("Iterating through Map using forEach:");
  map.forEach((value, key) => {
    console.log("Key:", key, "Value:", value);
  });

  // Get all keys (using keys())
  const keys = Array.from(map.keys()); // Convert iterator to array
  console.log("Keys:", keys); // Output: [ 'key2', 'key3' ]

  // Get all values (using values())
  const values = Array.from(map.values()); // Convert iterator to array
  console.log("Values:", values); // Output: [ 'newvalue2', 'value3' ]

  // Size of the Map (using size property)
  const size = map.size;
  console.log("Size of Map:", size); // Output: 2

  // Clear the Map (using clear())
  map.clear();
  console.log("Map after clear:", map); // Output: Map {}
})();

// 3. Using JavaScript Set (For Sets - Unique Values)
(() => {
  console.log("\n3. Using JavaScript Set");

  // Create a new Set
  const set = new Set();

  // Add values to the Set (using add())
  set.add("value1");
  set.add("value2");
  set.add("value3");
  set.add("value2"); // Duplicate value, will be ignored

  console.log("Initial Set:", set); // Output: Set { 'value1', 'value2', 'value3' }

  // Check if a value exists (using has())
  const hasValue2 = set.has("value2");
  const hasValue4 = set.has("value4");
  console.log("Has value2:", hasValue2); // Output: true
  console.log("Has value4:", hasValue4); // Output: false

  // Delete a value (using delete())
  set.delete("value1");
  console.log("Set after deletion:", set); // Output: Set { 'value2', 'value3' }

  // Iterate through the Set (using for...of)
  console.log("Iterating through Set:");
  for (const value of set) {
    console.log("Value:", value);
  }

  // Get all values (Set doesn't have keys, values are the keys)
  const values = Array.from(set.values()); // or Array.from(set);
  console.log("Values:", values); // Output: [ 'value2', 'value3' ]

  // Size of the Set (using size property)
  const size = set.size;
  console.log("Size of Set:", size); // Output: 2

  // Clear the Set (using clear())
  set.clear();
  console.log("Set after clear:", set); // Output: Set {}
})();

// 4. Using a custom class (Illustrative, not usually recommended for simple cases)
(() => {
  console.log("\n4. Using a Custom Class (Illustrative)");
  class MyHashMap {
    constructor() {
      this.map = {};
      this.count = 0;
    }

    set(key, value) {
      if (!this.has(key)) {
        this.count++;
      }
      this.map[key] = value;
    }

    get(key) {
      return this.has(key) ? this.map[key] : undefined;
    }

    has(key) {
      return this.map.hasOwnProperty(key);
    }

    delete(key) {
      if (this.has(key)) {
        delete this.map[key];
        this.count--;
        return true; // Indicate successful deletion
      }
      return false; // Indicate key not found
    }

    size() {
      return this.count;
    }

    clear() {
      this.map = {};
      this.count = 0;
    }

    keys() {
      return Object.keys(this.map);
    }

    values() {
      return Object.values(this.map);
    }

    forEach(callback) {
      for (const key in this.map) {
        if (this.map.hasOwnProperty(key)) {
          callback(this.map[key], key, this);
        }
      }
    }
  }

  const myHashMap = new MyHashMap();

  myHashMap.set("key1", "value1");
  myHashMap.set("key2", "value2");
  myHashMap.set("key3", "value3");
  console.log("Initial HashMap:", myHashMap);
  console.log("Get key2:", myHashMap.get("key2"));
  console.log("Has key2:", myHashMap.has("key2"));
  console.log("Has key4:", myHashMap.has("key4"));
  myHashMap.set("key2", "newvalue2");
  console.log("After update:", myHashMap);
  myHashMap.delete("key1");
  console.log("After delete:", myHashMap);
  console.log("Size:", myHashMap.size());
  console.log("Keys:", myHashMap.keys());
  console.log("Values:", myHashMap.values());

  console.log("Iterating using forEach:");
  myHashMap.forEach((value, key) => {
    console.log(`Key: ${key}, Value: ${value}`);
  });

  myHashMap.clear();
  console.log("After clear:", myHashMap);
})();

// 5.  Using a Map with non-string keys (Important Demonstration)
(() => {
    console.log("\n5. Using Map with Non-String Keys");

    const map = new Map();

    const obj1 = { name: "Alice" };
    const obj2 = { name: "Bob" };
    const numKey = 123;
    const boolKey = true;

    map.set(obj1, "Alice's Value");
    map.set(obj2, "Bob's Value");
    map.set(numKey, "Number Key Value");
    map.set(boolKey, "Boolean Key Value");

    console.log("Map with objects as keys:", map);

    // Get values using the object keys
    console.log("Value for obj1:", map.get(obj1)); // Output: Alice's Value
    console.log("Value for obj2:", map.get(obj2)); // Output: Bob's Value
    console.log("Value for numKey", map.get(numKey)); //Output: Number Key Value
    console.log("Value for boolKey", map.get(boolKey)); //Output: Boolean Key Value

    // Check for key existence
    console.log("Has obj1:", map.has(obj1)); // Output: true
    console.log("Has {name: 'Alice'}:", map.has({name: 'Alice'})); // Output: false.  Important!  Different object.

    //Iterate
    console.log("Iterating the map");
    for (const [key, value] of map) {
        console.log("Key:", key, "Value:", value);
    }

    // Delete
    map.delete(obj1);
    console.log("Map after deleting obj1", map);

    map.clear();
    console.log("Map after clear", map);

})();
