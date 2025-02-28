#include <stdlib.h>
#include <stdio.h>
#include "sandpiles.h"

/**
 * print_grid - Print 3x3 grid
 * @grid: 3x3 grid
 *
 */
static void print_grid(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
 * is_stable - Check if a sandpile is stable
 * @grid: 3x3 grid
 *
 * Return: 1 if stable, 0 if unstable
 */
static int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
				return (0);
		}
	}
	return (1);
}

/**
 * topple - Topple unstable cells in a sandpile
 * @grid: 3x3 grid to topple
 *
 * Return: 1 if any cell was toppled, 0 otherwise
 */
static int topple(int grid[3][3])
{
	int i, j;
	int tmp[3][3] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	int toppled = 0;

	/* First pass: identify unstable cells and compute their effect */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
			{
				toppled = 1;
				grid[i][j] -= 4;

				/* Add to neighbors */
				if (i > 0)
					tmp[i - 1][j] += 1;
				if (i < 2)
					tmp[i + 1][j] += 1;
				if (j > 0)
					tmp[i][j - 1] += 1;
				if (j < 2)
					tmp[i][j + 1] += 1;
			}
		}
	}

	/* Second pass: apply the effect to the grid */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid[i][j] += tmp[i][j];
		}
	}

	return (toppled);
}

/**
 * sandpiles_sum - Computes the sum of two sandpiles
 * @grid1: First 3x3 grid
 * @grid2: Second 3x3 grid
 *
 * Description: The function adds grid2 to grid1 and stabilizes grid1
 * A sandpile is stable when no cell contains more than 3 grains
 * grid1 is printed before each toppling round if it's unstable
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	/* Add grid2 to grid1 */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid1[i][j] += grid2[i][j];
		}
	}

	/* Stabilize grid1 */
	while (!is_stable(grid1))
	{
		printf("=\n");
		print_grid(grid1);
		topple(grid1);
	}
}
