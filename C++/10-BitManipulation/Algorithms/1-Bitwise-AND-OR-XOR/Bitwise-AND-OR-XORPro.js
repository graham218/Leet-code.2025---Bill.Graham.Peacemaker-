/*
Bit Manipulation: Bitwise AND, OR, XOR

This code demonstrates bitwise AND, OR, and XOR operations in JavaScript with five different approaches, each simulating a real-world project implementation.  The results of each operation are printed to the console.

1.  **Access Control (AND):** Simulates a system where permissions are stored as bit flags.  The AND operator is used to check if a user has a specific permission.
2.  **Combining Options (OR):** Simulates combining different options or settings, where each option is represented by a bit. The OR operator is used to set multiple options.
3.  **Toggling Features (XOR):** Simulates toggling a feature on or off. The XOR operator is used to flip the state of a specific bit.
4.  **Data Comparison (XOR):** Simulates comparing two sets of data to find the differences. The XOR operator can be used to identify bits that are different between the two sets.
5.  **Efficient Storage (AND, OR):** Simulates a scenario where we are using bits to efficiently store multiple true/false values.
*/

console.log("Bit Manipulation - Bitwise AND, OR, XOR");
console.log("----------------------------------------");

// 1. Access Control (AND)
//   - Permissions are represented as bit flags:
//     - 1 (0b0001): Read
//     - 2 (0b0010): Write
//     - 4 (0b0100): Execute
//     - 8 (0b1000): Delete
const READ    = 1;  // 0b0001
const WRITE   = 2;  // 0b0010
const EXECUTE = 4;  // 0b0100
const DELETE  = 8;  // 0b1000

let userPermissions = READ | WRITE; // User has Read and Write permissions (0b0011)
console.log("\n1. Access Control (AND)");
console.log("User Permissions:", userPermissions.toString(2)); // Output: 11

// Check if the user has Write permission
let hasWritePermission = (userPermissions & WRITE) !== 0;
console.log("Has Write Permission:", hasWritePermission); // Output: true

// Check if user has Delete permission
let hasDeletePermission = (userPermissions & DELETE) !== 0;
console.log("Has Delete Permission:", hasDeletePermission); // Output: false


// 2. Combining Options (OR)
//   - Options for a product configuration:
//     - 1 (0b0001): Color - Red
//     - 2 (0b0010): Size  - Medium
//     - 4 (0b0100): Style - Sport
//     - 8 (0b1000): Feature - GPS
const COLOR_RED    = 1; // 0b0001
const SIZE_MEDIUM  = 2; // 0b0010
const STYLE_SPORT  = 4; // 0b0100
const FEATURE_GPS  = 8; // 0b1000

let productOptions = COLOR_RED | SIZE_MEDIUM;  // Select Red color and Medium size
console.log("\n2. Combining Options (OR)");
console.log("Product Options:", productOptions.toString(2)); // Output: 11

productOptions = productOptions | FEATURE_GPS; // Add GPS feature
console.log("Product Options with GPS:", productOptions.toString(2)); // Output: 1011



// 3. Toggling Features (XOR)
//   - Feature flags for an application:
//     - 1 (0b0001): Dark Mode
//     - 2 (0b0010): Notifications
const DARK_MODE     = 1; // 0b0001
const NOTIFICATIONS = 2; // 0b0010

let appSettings = DARK_MODE; // Initially, Dark Mode is ON
console.log("\n3. Toggling Features (XOR)");
console.log("Initial App Settings:", appSettings.toString(2)); // Output: 1

// Toggle Dark Mode (OFF)
appSettings = appSettings ^ DARK_MODE;
console.log("App Settings after toggling Dark Mode (OFF):", appSettings.toString(2)); // Output: 0

// Toggle Dark Mode (ON) again
appSettings = appSettings ^ DARK_MODE;
console.log("App Settings after toggling Dark Mode (ON):", appSettings.toString(2)); // Output: 1

// Toggle Notifications
appSettings = appSettings ^ NOTIFICATIONS;
console.log("App Settings after toggling Notifications:", appSettings.toString(2)); // Output: 10

// Toggle Notifications again
appSettings = appSettings ^ NOTIFICATIONS;
console.log("App Settings after toggling Notifications again:", appSettings.toString(2)); // Output: 0


// 4. Data Comparison (XOR)
//    - Comparing two data sets (represented as integers) to find differences.
let dataSet1 = 0b11001100; // Example data set 1
let dataSet2 = 0b10101110; // Example data set 2
console.log("\n4. Data Comparison (XOR)");
console.log("Data Set 1:", dataSet1.toString(2));
console.log("Data Set 2:", dataSet2.toString(2));

let differences = dataSet1 ^ dataSet2; // Find the differences
console.log("Differences (XOR Result):", differences.toString(2)); // Output: 01100010
// The '1' bits in the result indicate where the data sets differ.


// 5. Efficient Storage (AND, OR)
//   Storing multiple boolean values (switches) in a single number
const SWITCH_1 = 1; // 0b0001
const SWITCH_2 = 2; // 0b0010
const SWITCH_3 = 4; // 0b0100
const SWITCH_4 = 8; // 0b1000
const SWITCH_5 = 16; // 0b10000

let switchesState = 0; // Initially all switches are off

console.log("\n5. Efficient Storage (AND, OR)");

// Turn on Switch 1 and Switch 3
switchesState = switchesState | SWITCH_1 | SWITCH_3;
console.log("Switches State after turning on 1 and 3:", switchesState.toString(2)); // 0b0101

// Check if Switch 3 is on
const isSwitch3On = (switchesState & SWITCH_3) !== 0;
console.log("Is Switch 3 on?", isSwitch3On); // true

// Turn off Switch 3
switchesState = switchesState ^ SWITCH_3;
console.log("Switches State after turning off 3:", switchesState.toString(2)); // 0b0001

// Check if Switch 3 is on
const isSwitch3OnAfterToggle = (switchesState & SWITCH_3) !== 0;
console.log("Is Switch 3 on after toggle?", isSwitch3OnAfterToggle); // false

// Turn on Switch 5
switchesState = switchesState | SWITCH_5;
console.log("Switches State after turning on Switch 5:", switchesState.toString(2));
