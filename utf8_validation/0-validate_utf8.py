#!/usr/bin/python3
"""
UTF-8 Validation
"""


def validUTF8(data):
    """
    Determines if a given data set represents a valid UTF-8 encoding.

    Args:
        data: List of integers representing bytes

    Returns:
        True if data is a valid UTF-8 encoding, else False
    """
    # Number of bytes in the current UTF-8 character
    num_bytes = 0

    # Masks for checking the most significant bits
    mask1 = 1 << 7  # 10000000
    mask2 = 1 << 6  # 01000000

    for num in data:
        # Get the 8 least significant bits
        byte = num & 0xFF

        # If this is the start of a new UTF-8 character
        if num_bytes == 0:
            # Count the number of leading 1s
            mask = 1 << 7
            while mask & byte:
                num_bytes += 1
                mask >>= 1

            # Handle invalid cases
            if num_bytes == 0:
                continue  # Single byte character
            if num_bytes == 1 or num_bytes > 4:
                return False  # Invalid UTF-8
        else:
            # Check if this is a continuation byte
            if not (byte & mask1 and not (byte & mask2)):
                return False

        num_bytes -= 1

    # Check if we ended in the middle of a character
    return num_bytes == 0