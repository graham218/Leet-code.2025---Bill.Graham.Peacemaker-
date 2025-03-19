// Advanced Dutch National Flag Algorithm Implementations
// Real-world applications include image segmentation, packet classification, and sorting algorithms.

// Class to represent objects with different priority levels
class Color {
  String name;
  int priority; // 0 = Low, 1 = Medium, 2 = High

  Color(this.name, this.priority);
}

// Approach 1: Sorting Log Levels (Low, Medium, High)
// Used in logging systems to categorize logs into priority levels.
void sortLogLevels(List<Color> logs) {
  int low = 0, mid = 0, high = logs.length - 1;
  while (mid <= high) {
    if (logs[mid].priority == 0) { // Low priority log
      _swap(logs, low, mid);
      low++;
      mid++;
    } else if (logs[mid].priority == 1) { // Medium priority log
      mid++;
    } else { // High priority log
      _swap(logs, mid, high);
      high--;
    }
  }
}

// Approach 2: Network Packet Prioritization (Low, Normal, High)
// Used in networking to prioritize traffic for Quality of Service (QoS).
void prioritizePackets(List<Color> packets) {
  packets.sort((a, b) => a.priority.compareTo(b.priority)); // Simple sort based on priority
}

// Approach 3: Image Segmentation (RGB Sorting by Intensity)
// Used in image processing to classify pixels based on brightness levels.
void sortColorsByIntensity(List<Color> pixels) {
  int low = 0, mid = 0, high = pixels.length - 1;
  while (mid <= high) {
    if (pixels[mid].priority == 0) { // Darker shades
      _swap(pixels, low, mid);
      low++;
      mid++;
    } else if (pixels[mid].priority == 1) { // Medium intensity shades
      mid++;
    } else { // Bright shades
      _swap(pixels, mid, high);
      high--;
    }
  }
}

// Approach 4: Hospital Triage System (Emergency Levels)
// Used in healthcare to sort patients based on the severity of their condition.
void sortPatientsByEmergency(List<Color> patients) {
  patients.sort((a, b) => a.priority.compareTo(b.priority)); // Sorting patients by emergency level
}

// Approach 5: Automated Customer Service Ticket Sorting
// Used in customer support systems to prioritize urgent cases first.
void sortSupportTickets(List<Color> tickets) {
  int low = 0, mid = 0, high = tickets.length - 1;
  while (mid <= high) {
    if (tickets[mid].priority == 0) { // Low-priority tickets
      _swap(tickets, low, mid);
      low++;
      mid++;
    } else if (tickets[mid].priority == 1) { // Normal priority tickets
      mid++;
    } else { // Urgent tickets
      _swap(tickets, mid, high);
      high--;
    }
  }
}

// Helper function to swap elements in a list
void _swap(List<Color> list, int i, int j) {
  Color temp = list[i];
  list[i] = list[j];
  list[j] = temp;
}

void main() {
  // Sample data for testing each approach
  List<Color> logs = [Color("Info", 1), Color("Error", 2), Color("Debug", 0)];
  List<Color> packets = [Color("Low Priority", 0), Color("High Priority", 2), Color("Normal", 1)];
  List<Color> pixels = [Color("Dark", 0), Color("Medium", 1), Color("Bright", 2)];
  List<Color> patients = [Color("Critical", 2), Color("Moderate", 1), Color("Stable", 0)];
  List<Color> tickets = [Color("Urgent", 2), Color("Normal", 1), Color("Low", 0)];

  // Applying different sorting methods
  sortLogLevels(logs);
  prioritizePackets(packets);
  sortColorsByIntensity(pixels);
  sortPatientsByEmergency(patients);
  sortSupportTickets(tickets);

  // Printing sorted outputs
  print("Sorted Logs: ${logs.map((e) => e.name)}");
  print("Sorted Packets: ${packets.map((e) => e.name)}");
  print("Sorted Pixels: ${pixels.map((e) => e.name)}");
  print("Sorted Patients: ${patients.map((e) => e.name)}");
  print("Sorted Tickets: ${tickets.map((e) => e.name)}");
}