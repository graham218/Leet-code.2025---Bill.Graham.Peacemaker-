import 'dart:collection';

class AhoCorasick {
  // List of patterns to search for.
  final List<String> patterns;
  // Goto function: maps (state, character) to next state.
  final Map<int, Map<String, int>> goto;
  // Failure function: maps state to its failure state.
  final Map<int, int> failure;
  // Output function: maps state to set of patterns found at that state.
  final Map<int, Set<String>> output;

  // Constructor: initializes the data structures and builds the Aho-Corasick automaton.
  AhoCorasick(this.patterns)
      : goto = {},
        failure = {},
        output = {} {
    _buildGoto();
    _buildFailure();
  }

  // Builds the goto function.
  void _buildGoto() {
    // Start with state 0.
    int state = 0;
    // Iterate through each pattern.
    for (var pattern in patterns) {
      // Start at the root state for each pattern.
      int currentState = 0;
      // Iterate through each character in the pattern.
      for (var char in pattern.split('')) {
        // If the current state doesn't have a goto map, create one.
        if (goto[currentState] == null) {
          goto[currentState] = {};
        }
        // If the current state doesn't have a transition for the current character, create one.
        if (!goto[currentState]!.containsKey(char)) {
          // Increment the state counter and create a new state.
          state++;
          goto[currentState]![char] = state;
        }
        // Move to the next state.
        currentState = goto[currentState]![char]!;
      }
      // When the end of the pattern is reached, add the pattern to the output set of the current state.
      if (output[currentState] == null) {
        output[currentState] = {};
      }
      output[currentState]!.add(pattern);
    }
  }

  // Builds the failure function.
  void _buildFailure() {
    // Use a queue for breadth-first traversal.
    var queue = Queue<int>();
    // Initialize the failure function for states reachable from the root state.
    if(goto[0] != null){
      for (var entry in goto[0]!.entries) {
        queue.add(entry.value);
        failure[entry.value] = 0;
      }
    }

    // Process the states in the queue.
    while (queue.isNotEmpty) {
      int r = queue.removeFirst();
      // If the current state has no goto transitions, skip it.
      if (goto[r] == null) continue;
      // Iterate through the transitions of the current state.
      for (var entry in goto[r]!.entries) {
        String a = entry.key;
        int s = entry.value;
        // Add the next state to the queue.
        queue.add(s);
        // Find the failure state for the next state.
        int state = failure[r]!;
        // Follow the failure links until a transition for the current character is found.
        while (state != 0 && goto[state]?[a] == null) {
          state = failure[state]!;
        }
        // Set the failure state for the next state.
        failure[s] = goto[state]?[a] ?? 0;
        // Merge the output sets of the failure state into the output set of the next state.
        if (output[failure[s]!] != null) {
          output[s] ??= {};
          output[s]!.addAll(output[failure[s]!]!);
        }
      }
    }
  }

  // Searches for the patterns in the given text.
  Map<String, List<int>> search(String text) {
    // Initialize the result map.
    Map<String, List<int>> result = {};
    // Start at the root state.
    int state = 0;
    // Iterate through the characters in the text.
    for (int i = 0; i < text.length; i++) {
      String char = text[i];
      // Follow the failure links until a transition for the current character is found.
      while (state != 0 && goto[state]?[char] == null) {
        state = failure[state]!;
      }
      // Move to the next state.
      state = goto[state]?[char] ?? 0;
      // If the current state has an output set, add the patterns to the result map.
      if (output.containsKey(state)) {
        for (var pattern in output[state]!) {
          result[pattern] ??= [];
          // Calculate the starting position of the pattern in the text.
          result[pattern]!.add(i - pattern.length + 1);
        }
      }
    }
    // Return the result map.
    return result;
  }
}

void main() {
  final patterns = ['he', 'she', 'his', 'hers'];
  final text = 'ahishers';

  // Approach 1: Basic Aho-Corasick
  final ac1 = AhoCorasick(patterns);
  print('Approach 1: ${ac1.search(text)}');

  // Approach 2: Aho-Corasick with Case Insensitivity
  final ac2 = AhoCorasick(patterns.map((p) => p.toLowerCase()).toList());
  print('Approach 2: ${ac2.search(text.toLowerCase())}');

  // Approach 3: Aho-Corasick with Partial Matches
  final ac3 = AhoCorasick(patterns);
  print('Approach 3: ${ac3.search(text.substring(0, text.length ~/ 2))}');

  // Approach 4: Aho-Corasick with Multiple Texts
  final ac4 = AhoCorasick(patterns);
  print('Approach 4: ${[text, 'hehe'].map((t) => ac4.search(t)).toList()}');

  // Approach 5: Aho-Corasick with Custom Output Format
  final ac5 = AhoCorasick(patterns);
  final result5 = ac5.search(text);
  final formattedResult5 = result5.entries.map((e) => '${e.key}: ${e.value}').join(', ');
  print('Approach 5: {$formattedResult5}');

  // Approach 6: Aho-Corasick with Debugging
  final ac6 = AhoCorasick(patterns);
  final result6 = ac6.search(text);
  print('Approach 6:');
  result6.forEach((key, value) {
    print('Pattern "$key" found at positions: $value');
  });
}