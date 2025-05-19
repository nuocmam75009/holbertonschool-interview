#!/usr/bin/python3

"""
Module that determines if all the boxes from a list can be opened.
"""


def canUnlockAll(boxes):
    """
    Determines if all boxes can be unlocked.

    Args:
        boxes (list of lists): a list of boxes with keys to other boxes.

    Returns:
        bool: True if all boxes can be unlocked, False otherwise.
    """
    # Set to track opened boxes. Box 0 starts as unlocked.
    open_boxes = {0}
    # List of keys we have. Start with the key to box 0.
    keys = [0]

    # Loop while we have keys to use.
    while keys:
        # Take the last key (box number) from the list.
        current_box = keys.pop()

        # Check each key in the current box.
        for key in boxes[current_box]:
            # If the box is not open and the key is valid.
            if key not in open_boxes and key < len(boxes):
                # Open the box and add it to opened boxes.
                open_boxes.add(key)
                # Add the key to check that box later.
                keys.append(key)

    # Check if the number of opened boxes equals the total number of boxes.
    return len(open_boxes) == len(boxes)