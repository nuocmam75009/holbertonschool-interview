#!/usr/bin/python3
"""
Rain Water Retention
"""


def rain(walls):
    """
    Calculate how many square units of water will be retained after it rains.

    Args:
        walls: List of non-negative integers representing wall heights

    Returns:
        Integer indicating total amount of rainwater retained
    """
    if not walls:
        return 0

    n = len(walls)
    left = 0
    right = n - 1
    left_max = right_max = 0
    total_water = 0

    while left < right:
        # Update the maximum height seen so far from both ends
        left_max = max(left_max, walls[left])
        right_max = max(right_max, walls[right])

        # If left wall is smaller, calculate water at left position
        if walls[left] < walls[right]:
            # Water at current position = min(left_max, right_max) - current_height
            total_water += left_max - walls[left]
            left += 1
        else:
            # Water at current position = min(left_max, right_max) - current_height
            total_water += right_max - walls[right]
            right -= 1

    return total_water