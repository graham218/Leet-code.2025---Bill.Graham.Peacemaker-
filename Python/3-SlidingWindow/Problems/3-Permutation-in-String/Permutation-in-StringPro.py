'''
Advanced Sliding Window: Permutation in String - Real-World Applications

Problem Statement:
Given two strings s1 and s2, determine if s2 contains any permutation of s1 using real-world implementations.
'''

from collections import Counter

# 1. Cybersecurity - Detecting Anomalous Login Patterns (O(n))
def detect_anomalous_login_pattern(s1, s2):
    """
    Detects anomalous login patterns by checking if a given pattern (s1) is a permutation of any substring within a login sequence (s2).
    This can help identify suspicious user behavior, such as repeated login attempts with slightly varied credentials, which could indicate an attack.

    Args:
        s1 (str): The pattern to search for (e.g., a sequence of characters representing a suspicious login pattern).
        s2 (str): The string to search within (e.g., a user's login history).

    Returns:
        bool: True if s2 contains a permutation of s1, indicating a potential anomaly, False otherwise.
    """
    required_pattern = Counter(s1)  # Create a Counter to store the character frequencies of the pattern s1.
    current_window = Counter()  # Create a Counter to store the character frequencies of the current window in s2.
    left = 0  # Initialize the left pointer of the sliding window.

    for right in range(len(s2)):  # Iterate through the string s2 using the right pointer.
        current_window[s2[right]] += 1  # Add the current character to the window's frequency count.

        if right - left + 1 > len(s1):  # If the window size exceeds the length of the pattern s1:
            current_window[s2[left]] -= 1  # Remove the leftmost character from the window's frequency count.
            if current_window[s2[left]] == 0:  # If the frequency of the leftmost character becomes 0:
                del current_window[s2[left]]  # Remove it from the Counter to keep it clean.
            left += 1  # Move the left pointer to slide the window.

        if current_window == required_pattern:  # If the character frequencies in the current window match the required pattern:
            return True  # A permutation of the pattern is found, indicating an anomaly.
    return False  # If no permutation is found, return False.

# 2. DNA Sequence Matching in Bioinformatics (O(n))
def match_dna_sequences(dna1, dna2):
    """
    Matches DNA sequences to find if a given sequence (dna1) is a permutation of a substring within a larger DNA sequence (dna2).
    This is useful in bioinformatics for identifying gene sequences or mutations.

    Args:
        dna1 (str): The target DNA sequence (e.g., a short gene sequence).
        dna2 (str): The larger DNA sequence to search within (e.g., a chromosome).

    Returns:
        bool: True if dna2 contains a permutation of dna1, indicating a match, False otherwise.
    """
    dna1_count = Counter(dna1)  # Counter for the target DNA sequence.
    window_count = Counter(dna2[:len(dna1)-1]) # Counter for the initial window in the larger sequence.
    for i in range(len(dna1)-1, len(dna2)):
        window_count[dna2[i]] += 1
        if window_count == dna1_count:
            return True
        window_count[dna2[i - len(dna1) + 1]] -= 1
        if window_count[dna2[i - len(dna1) + 1]] == 0:
            del window_count[dna2[i - len(dna1) + 1]]
    return False

# 3. Financial Fraud Detection - Suspicious Transaction Patterns (O(n))
def detect_suspicious_transactions(pattern, transactions):
    """
    Detects suspicious transaction patterns by checking if a given pattern of transactions occurs as a permutation
    within a larger sequence of transactions.  This can help identify fraudulent activities, such as sequences of
    transactions designed to avoid detection.

    Args:
        pattern (str): The pattern of transactions to search for (e.g., "A-B-C").
        transactions (str): The sequence of transactions to analyze.

    Returns:
        bool: True if the transactions contain a permutation of the pattern, False otherwise.
    """
    pattern_map = Counter(pattern)  # Counter for the suspicious transaction pattern.
    transaction_window = Counter()  # Counter for the current transaction window.
    left = 0
    for right in range(len(transactions)):
        transaction_window[transactions[right]] += 1
        if right - left + 1 > len(pattern):
            transaction_window[transactions[left]] -= 1
            if transaction_window[transactions[left]] == 0:
                del transaction_window[transactions[left]]
            left += 1
        if transaction_window == pattern_map:
            return True
    return False

# 4. Content Moderation - Detecting Offensive Word Patterns (O(n))
def detect_offensive_language(keyword, text):
    """
    Detects offensive language by searching for permutations of a given keyword within a text.
    This can help identify variations of offensive words or phrases that might be used to evade simple filtering.

    Args:
        keyword (str): The offensive keyword to search for.
        text (str): The text to analyze.

    Returns:
        bool: True if the text contains a permutation of the keyword, False otherwise.
    """
    keyword_map = Counter(keyword)  # Counter for the offensive keyword.
    text_map = Counter()  # Counter for the current window in the text.
    left = 0
    for right in range(len(text)):
        text_map[text[right]] += 1
        if right - left + 1 > len(keyword):
            text_map[text[left]] -= 1
            if text_map[text[left]] == 0:
                del text_map[text[left]]
            left += 1
        if text_map == keyword_map:
            return True
    return False

# 5. Network Security - Identifying Malicious Packet Sequences (O(n))
def detect_malicious_packets(signature, packets):
    """
    Identifies malicious packet sequences by checking if a given signature (a pattern of packet types or data)
    is a permutation of a substring within a larger sequence of network packets.

    Args:
        signature (str): The signature of the malicious packet sequence.
        packets (str): The sequence of network packets.

    Returns:
        bool: True if the packet sequence contains a permutation of the signature, False otherwise.
    """
    signature_map = Counter(signature)  # Counter for the malicious packet signature.
    packet_map = Counter()  # Counter for the current window of packets.
    left = 0
    for right in range(len(packets)):
        packet_map[packets[right]] += 1
        if right - left + 1 > len(signature):
            packet_map[packets[left]] -= 1
            if packet_map[packets[left]] == 0:
                del packet_map[packets[left]]
            left += 1
        if packet_map == signature_map:
            return True
    return False

# 6. AI Chatbot - Detecting Predefined Command Patterns (O(n))
def detect_command_pattern(command, conversation):
    """
    Detects predefined command patterns in a conversation by checking if a given command sequence
    is a permutation of a substring within the conversation history.  This can be useful for
    identifying specific user intents or detecting misuse of the chatbot.

    Args:
        command (str): The predefined command pattern to detect.
        conversation (str): The conversation history.

    Returns:
        bool: True if the conversation contains a permutation of the command pattern, False otherwise.
    """
    command_map = Counter(command)  # Counter for the predefined command pattern.
    conversation_map = Counter()  # Counter for the current window in the conversation.
    left = 0
    for right in range(len(conversation)):
        conversation_map[conversation[right]] += 1
        if right - left + 1 > len(command):
            conversation_map[conversation[left]] -= 1
            if conversation_map[conversation[left]] == 0:
                del conversation_map[conversation[left]]
            left += 1
        if conversation_map == command_map:
            return True
    return False

# Test Cases
s1 = "abc"
s2 = "eidbacooo"
print("Cybersecurity Login Pattern Detection:", detect_anomalous_login_pattern(s1, s2))
print("DNA Sequence Matching:", match_dna_sequences(s1, s2))
print("Fraud Detection:", detect_suspicious_transactions(s1, s2))
print("Content Moderation:", detect_offensive_language(s1, s2))
print("Network Security:", detect_malicious_packets(s1, s2))
print("AI Chatbot Commands:", detect_command_pattern(s1, s2))
