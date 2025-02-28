# 2048 Line Sliding

This project implements the sliding and merging mechanics of the 2048 game on a single horizontal line.

## Task

Given an array of integers, we want to be able to slide & merge it to the left or to the right. Identical numbers, if they are contiguous or separated by zeros, should be merged.

The function `slide_line` slides and merges an array of integers in the specified direction (left or right).

### Function Prototype

```c
int slide_line(int *line, size_t size, int direction);
```

Where:
- `line` points to an array of integers containing `size` elements
- `direction` can be either `SLIDE_LEFT` or `SLIDE_RIGHT`

The function returns 1 upon success, or 0 upon failure.

## Example
