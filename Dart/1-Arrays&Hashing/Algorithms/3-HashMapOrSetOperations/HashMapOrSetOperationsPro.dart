import 'dart:collection';

class AdvancedHashMapSetOperations {
  /// Approach 1: Optimized HashMap for User Authentication (storing user details securely)
  Map<String, String> userCredentials = HashMap();

  void addUser(String username, String password) {
    userCredentials[username] = password;
  }

  bool authenticate(String username, String password) {
    return userCredentials.containsKey(username) && userCredentials[username] == password;
  }

  /// Approach 2: HashSet for Unique Session Management (tracking active user sessions)
  Set<String> activeSessions = HashSet();

  void addSession(String sessionId) {
    activeSessions.add(sessionId);
  }

  void removeSession(String sessionId) {
    activeSessions.remove(sessionId);
  }

  bool isSessionActive(String sessionId) {
    return activeSessions.contains(sessionId);
  }

  /// Approach 3: HashMap for E-Commerce Inventory Management (fast lookups and stock tracking)
  Map<String, int> inventory = HashMap();

  void addItem(String item, int quantity) {
    inventory[item] = (inventory[item] ?? 0) + quantity;
  }

  bool isItemAvailable(String item) {
    return inventory.containsKey(item) && inventory[item]! > 0;
  }

  void purchaseItem(String item, int quantity) {
    if (isItemAvailable(item) && inventory[item]! >= quantity) {
      inventory[item] = inventory[item]! - quantity;
    }
  }

  /// Approach 4: HashSet for Preventing Duplicate User Registrations (ensuring uniqueness)
  Set<String> registeredEmails = HashSet();

  bool registerUser(String email) {
    if (registeredEmails.contains(email)) {
      return false; // Email already registered
    }
    registeredEmails.add(email);
    return true;
  }

  /// Approach 5: HashMap for Log Data Aggregation (tracking API request frequency)
  Map<String, int> apiUsageTracker = HashMap();

  void logApiRequest(String endpoint) {
    apiUsageTracker[endpoint] = (apiUsageTracker[endpoint] ?? 0) + 1;
  }

  int getApiUsage(String endpoint) {
    return apiUsageTracker[endpoint] ?? 0;
  }
}

void main() {
  AdvancedHashMapSetOperations operations = AdvancedHashMapSetOperations();

  // User Authentication Example
  operations.addUser("john_doe", "password123");
  print("User authenticated: ${operations.authenticate("john_doe", "password123")}");

  // Session Management Example
  operations.addSession("session_123");
  print("Session active: ${operations.isSessionActive("session_123")}");
  operations.removeSession("session_123");
  print("Session active after removal: ${operations.isSessionActive("session_123")}");

  // Inventory Management Example
  operations.addItem("Laptop", 10);
  print("Is Laptop available? ${operations.isItemAvailable("Laptop")}");
  operations.purchaseItem("Laptop", 2);
  print("Remaining stock for Laptop: ${operations.inventory["Laptop"]}");

  // Unique User Registration Example
  print("User registered: ${operations.registerUser("test@example.com")}");
  print("User registered again: ${operations.registerUser("test@example.com")}");

  // API Usage Tracking Example
  operations.logApiRequest("/login");
  operations.logApiRequest("/login");
  print("Login endpoint usage count: ${operations.getApiUsage("/login")}");
}
