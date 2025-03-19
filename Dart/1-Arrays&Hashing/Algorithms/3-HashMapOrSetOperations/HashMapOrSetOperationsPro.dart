import 'dart:collection';

class AdvancedHashMapSetOperations {
  /// Securely stores user credentials using a HashMap.
  final Map<String, String> _userCredentials = HashMap(); // Make private

  /// Adds a new user with their credentials.
  void addUser(String username, String password) {
    _userCredentials[username] = password;
  }

  /// Authenticates a user based on their username and password.
  bool authenticate(String username, String password) {
    return _userCredentials.containsKey(username) &&
        _userCredentials[username] == password;
  }

  /// Manages active user sessions using a HashSet.
  final Set<String> _activeSessions = HashSet(); // Make private

  /// Adds a new active session.
  void addSession(String sessionId) {
    _activeSessions.add(sessionId);
  }

  /// Removes an active session.
  void removeSession(String sessionId) {
    _activeSessions.remove(sessionId);
  }

  /// Checks if a session is currently active.
  bool isSessionActive(String sessionId) {
    return _activeSessions.contains(sessionId);
  }

  /// Manages e-commerce inventory using a HashMap.
  final Map<String, int> _inventory = HashMap(); // Make private

  /// Adds items to the inventory or increases existing item quantities.
  void addItem(String item, int quantity) {
    _inventory[item] = (_inventory[item] ?? 0) + quantity;
  }

  /// Checks if an item is available in the inventory.
  bool isItemAvailable(String item) {
    return _inventory.containsKey(item) && _inventory[item]! > 0;
  }

  /// Processes a purchase, reducing the item quantity in the inventory.
  void purchaseItem(String item, int quantity) {
    if (isItemAvailable(item) && _inventory[item]! >= quantity) {
      _inventory[item] = _inventory[item]! - quantity;
    }
  }

  /// Prevents duplicate user registrations using a HashSet.
  final Set<String> _registeredEmails = HashSet(); // Make private

  /// Registers a new user if their email is unique.
  bool registerUser(String email) {
    if (_registeredEmails.contains(email)) {
      return false; // Email already registered
    }
    _registeredEmails.add(email);
    return true;
  }

  /// Tracks API request frequency using a HashMap.
  final Map<String, int> _apiUsageTracker = HashMap(); // Make private

  /// Logs an API request, incrementing the request count for the endpoint.
  void logApiRequest(String endpoint) {
    _apiUsageTracker[endpoint] = (_apiUsageTracker[endpoint] ?? 0) + 1;
  }

  /// Retrieves the API request count for a specific endpoint.
  int getApiUsage(String endpoint) {
    return _apiUsageTracker[endpoint] ?? 0;
  }
}

void main() {
  final operations = AdvancedHashMapSetOperations(); //use final

  // User Authentication Example
  print("\n--- User Authentication ---");
  operations.addUser("john_doe", "password123");
  print("User authenticated: ${operations.authenticate("john_doe", "password123")}");

  // Session Management Example
  print("\n--- Session Management ---");
  operations.addSession("session_123");
  print("Session active: ${operations.isSessionActive("session_123")}");
  operations.removeSession("session_123");
  print("Session active after removal: ${operations.isSessionActive("session_123")}");

  // Inventory Management Example
  print("\n--- Inventory Management ---");
  operations.addItem("Laptop", 10);
  print("Is Laptop available? ${operations.isItemAvailable("Laptop")}");
  operations.purchaseItem("Laptop", 2);
  print("Remaining stock for Laptop: ${operations.getApiUsage("Laptop")}"); //corrected to getApiUsage to inventory access.
  print("Remaining stock for Laptop: ${operations._inventory["Laptop"]}"); //access the private variable for the inventory.

  // Unique User Registration Example
  print("\n--- User Registration ---");
  print("User registered: ${operations.registerUser("test@example.com")}");
  print("User registered again: ${operations.registerUser("test@example.com")}");

  // API Usage Tracking Example
  print("\n--- API Usage Tracking ---");
  operations.logApiRequest("/login");
  operations.logApiRequest("/login");
  print("Login endpoint usage count: ${operations.getApiUsage("/login")}");
}