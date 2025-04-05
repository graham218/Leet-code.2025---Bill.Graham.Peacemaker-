// 1. Using JavaScript Object as a HashMap (Basic Implementation)
//    - Real-world use case: Storing user preferences in a web application.
//    - Explanation:  JavaScript objects inherently function as hash maps, allowing key-value pair storage.
//                   This example demonstrates setting, getting, checking, and deleting preferences.
function hashMapObjectExample() {
  console.log("1. Using JavaScript Object as a HashMap");
  const userPreferences = {};

  // Set preferences
  userPreferences.theme = 'dark';
  userPreferences.fontSize = 16;
  userPreferences.notificationsEnabled = true;

  console.log("User Preferences (After setting):", userPreferences);

  // Get preferences
  console.log("Theme:", userPreferences.theme);
  console.log("Font Size:", userPreferences.fontSize);

  // Check if a preference exists
  console.log("Notifications Enabled?", 'notificationsEnabled' in userPreferences);
  console.log("Background Color?", 'backgroundColor' in userPreferences);

  // Delete a preference
  delete userPreferences.notificationsEnabled;
  console.log("User Preferences (After deleting notificationsEnabled):", userPreferences);

  // Check the number of keys
  console.log("Number of preferences:", Object.keys(userPreferences).length);

  // Clear all preferences
  for (const key in userPreferences) {
      delete userPreferences[key];
  }
  console.log("User Preferences (After clearing):", userPreferences);
}

// 2. Using JavaScript Map
//    - Real-world use case:  Managing a cache of recently accessed data in a web server.
//    - Explanation:  The Map object provides more features than a basic object, including
//                   guaranteed key order, ability to use objects as keys, and a size property.
function hashMapMapExample() {
  console.log("\n2. Using JavaScript Map");
  const dataCache = new Map();

  // Set cache entries
  dataCache.set('user1', { name: 'Alice', id: 1 });
  dataCache.set('product1', { name: 'Product A', price: 25 });
  dataCache.set('user2', { name: 'Bob', id: 2 });

  console.log("Data Cache (After setting):", dataCache);

  // Get cache entries
  console.log("User 1:", dataCache.get('user1'));
  console.log("Product 1:", dataCache.get('product1'));

  // Check if an entry exists
  console.log("User 2 exists?", dataCache.has('user2'));
  console.log("Product 2 exists?", dataCache.has('product2'));

  // Delete an entry
  dataCache.delete('product1');
  console.log("Data Cache (After deleting product1):", dataCache);

  // Get the number of entries
  console.log("Number of entries:", dataCache.size);

  // Iterate over the Map
  console.log("Iterating over cache:");
  for (const [key, value] of dataCache) {
    console.log(key, ":", value);
  }

  // Clear the Map
  dataCache.clear();
  console.log("Data Cache (After clearing):", dataCache);
}

// 3. Using JavaScript Set
//    - Real-world use case:  Storing unique user IDs for tracking online activity.
//    - Explanation:  The Set object stores a collection of unique values.  This example demonstrates
//                   adding, checking for existence, and deleting user IDs.
function hashSetExample() {
  console.log("\n3. Using JavaScript Set");
  const onlineUsers = new Set();

  // Add user IDs
  onlineUsers.add(123);
  onlineUsers.add(456);
  onlineUsers.add(789);
  onlineUsers.add(123); // Duplicate add, will be ignored

  console.log("Online Users (After adding):", onlineUsers);

  // Check if a user is online
  console.log("User 456 online?", onlineUsers.has(456));
  console.log("User 101 online?", onlineUsers.has(101));

  // Delete a user
  onlineUsers.delete(456);
  console.log("Online Users (After deleting 456):", onlineUsers);

  // Get the number of online users
  console.log("Number of online users:", onlineUsers.size);

  // Iterate over the Set
  console.log("Iterating over online users:");
  onlineUsers.forEach(userId => console.log(userId));

    // Clear the set
    onlineUsers.clear();
    console.log("Online Users (After clearing):", onlineUsers);
}

// 4. Using a custom HashMap class (Chaining for collision resolution)
//    - Real-world use case: Implementing a symbol table in a compiler.
//    - Explanation:  This demonstrates a custom HashMap implementation using chaining to handle collisions.
//                   It includes methods for put (insert/update), get, delete, and displaying the hash table.
class HashMap {
  constructor(size = 10) {
    this.size = size;
    this.table = new Array(size);
  }

  // Hash function (simple modulo)
  hash(key) {
    let hash = 0;
    for (let i = 0; i < key.length; i++) {
      hash += key.charCodeAt(i);
    }
    return hash % this.size;
  }

  // Put (insert/update) a key-value pair
  put(key, value) {
    const index = this.hash(key);
    if (!this.table[index]) {
      this.table[index] = []; // Use an array (chaining) to handle collisions
    }
    // Check if the key already exists, update if it does
    for (let i = 0; i < this.table[index].length; i++) {
      if (this.table[index][i][0] === key) {
        this.table[index][i][1] = value; // Update existing value
        return;
      }
    }
    this.table[index].push([key, value]); // Add new key-value pair
  }

  // Get the value associated with a key
  get(key) {
    const index = this.hash(key);
    if (this.table[index]) {
      for (let i = 0; i < this.table[index].length; i++) {
        if (this.table[index][i][0] === key) {
          return this.table[index][i][1]; // Return the value
        }
      }
    }
    return undefined; // Key not found
  }

  // Delete a key-value pair
  delete(key) {
    const index = this.hash(key);
    if (this.table[index]) {
      for (let i = 0; i < this.table[index].length; i++) {
        if (this.table[index][i][0] === key) {
          this.table[index].splice(i, 1); // Remove the element
          if (this.table[index].length === 0) {
            this.table[index] = null; // Clean up empty buckets
          }
          return true; // Indicate successful deletion
        }
      }
    }
    return false; // Key not found
  }

  // Display the hash table
  display() {
    console.log("HashMap Contents:");
    for (let i = 0; i < this.size; i++) {
      console.log(`Index ${i}:`, this.table[i] || 'Empty');
    }
  }
}

function customHashMapExample() {
  console.log("\n4. Using a custom HashMap class (Chaining)");
  const myHashMap = new HashMap(10);

  // Insert key-value pairs
  myHashMap.put('name', 'John');
  myHashMap.put('age', 30);
  myHashMap.put('city', 'New York');
  myHashMap.put('name', 'Johnny'); // Update existing key
  myHashMap.put('phone', '123-456-7890'); // Add a key that might cause collision

  myHashMap.display();

  // Get values
  console.log("Name:", myHashMap.get('name'));
  console.log("Age:", myHashMap.get('age'));
  console.log("City:", myHashMap.get('city'));
  console.log("Non-existent key:", myHashMap.get('xyz'));

  // Delete a key-value pair
  console.log("Delete 'age':", myHashMap.delete('age'));
  console.log("Delete 'age' again:", myHashMap.delete('age')); // Delete again
  myHashMap.display();
}

// 5.  Using WeakMap
//     - Real-world use case:  Storing private data for objects in a class.
//     - Explanation:  WeakMap holds key-value pairs where keys are objects.  It prevents memory leaks
//                    because keys are weakly referenced (garbage collected if the object is no longer used).
class MyClass {
  constructor(name) {
    this.name = name;
  }

  getName() {
    return this.name;
  }
}

const _privateData = new WeakMap(); // Use WeakMap

class User {
  constructor(name, secret) {
    this.name = name;
    _privateData.set(this, { secret }); // Store secret in WeakMap, using the instance as key.
  }

  getName() {
    return this.name;
  }

  getSecret() {
    return _privateData.get(this).secret; // Access the secret using 'this'
  }
}
function weakMapExample() {
  console.log("\n5. Using WeakMap");

  const user1 = new User('Alice', 'password123');
  const user2 = new User('Bob', 'secret456');

  console.log("User 1 Name:", user1.getName());
  console.log("User 1 Secret:", user1.getSecret());
  console.log("User 2 Name:", user2.getName());
  console.log("User 2 Secret:", user2.getSecret());

  // Here's the key difference with WeakMap.  If user1 and user2 are no longer
  // referenced elsewhere, the entries in _privateData will be garbage collected
  // automatically, preventing memory leaks.  You can't iterate over a WeakMap,
  // or get its size.

  //   _privateData.forEach((value, key) => {  //  Error:  _privateData.forEach is not a function
  //       console.log(key, value);
  //   });
  // console.log("Size of WeakMap:", _privateData.size); // Error:  undefined property 'size'
}

// 6. Using WeakSet
//    - Real-world use case:  Tracking which objects have been processed, without preventing their garbage collection.
//    - Explanation:  WeakSet is like Set, but holds *objects* weakly.  If an object in a WeakSet is no longer
//                   referenced elsewhere, it's removed from the WeakSet and garbage collected.
function weakSetExample() {
  console.log("\n6. Using WeakSet");
  const processedObjects = new WeakSet();

  const obj1 = { id: 1 };
  const obj2 = { id: 2 };
  const obj3 = { id: 3 };

  processedObjects.add(obj1);
  processedObjects.add(obj2);
  processedObjects.add(obj1); // Add same object again.

  console.log("Processed obj1?", processedObjects.has(obj1));
  console.log("Processed obj2?", processedObjects.has(obj2));
  console.log("Processed obj3?", processedObjects.has(obj3));

  // Like WeakMap, WeakSet does not have .size, and is not iterable.
  // processedObjects.forEach(obj => console.log(obj));  // Error: processedObjects.forEach is not a function
  // console.log("Size of WeakSet", processedObjects.size); // Error: undefined property 'size'

  // If obj1 and obj2 are no longer referenced elsewhere, they will be
  // removed from processedObjects and garbage collected.
}

// Run the examples
hashMapObjectExample();
hashMapMapExample();
hashSetExample();
customHashMapExample();
weakMapExample();
weakSetExample();
