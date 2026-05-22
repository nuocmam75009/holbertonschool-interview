#!/usr/bin/python3
"""N Queens problem solver using backtracking."""
import sys


def is_safe(queens, row, col):
    """Check if placing a queen at (row, col) conflicts with existing queens."""
    for r, c in queens:
        if c == col or abs(r - row) == abs(c - col):
            return False
    return True


def solve(n, row, queens):
    """Recursively place queens row by row using backtracking."""
    if row == n:
        print(queens)
        return
    for col in range(n):
        if is_safe(queens, row, col):
            solve(n, row + 1, queens + [[row, col]])


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: nqueens N")
        sys.exit(1)

    try:
        n = int(sys.argv[1])
    except ValueError:
        print("N must be a number")
        sys.exit(1)

    if n < 4:
        print("N must be at least 4")
        sys.exit(1)

    solve(n, 0, [])
