#!/usr/bin/python3
"""
Island Perimeter module
"""


def island_perimeter(grid):
    """
    Calculates the perimeter of an island in a grid.

    Args:
        grid (list): A list of lists of integers where:
            0 represents water
            1 represents land

    Returns:
        int: The perimeter of the island
    """
    if not grid or not isinstance(grid, list):
        return 0

    perimeter = 0
    rows = len(grid)
    cols = len(grid[0]) if rows > 0 else 0

    for i in range(rows):
        for j in range(cols):
            if grid[i][j] == 1:
                # Each land cell contributes 4 to the perimeter
                perimeter += 4

                # Subtract 2 for each shared edge with another land cell
                # Check top neighbor
                if i > 0 and grid[i - 1][j] == 1:
                    perimeter -= 2

                # Check left neighbor
                if j > 0 and grid[i][j - 1] == 1:
                    perimeter -= 2

    return perimeter