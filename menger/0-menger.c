#include <stdio.h>
#include <math.h>

#include "menger.h"

/**
 * is_hole - checks whether a point (col, row) is a hole in the sponge
 * @col: column index
 * @row: row index
 *
 * Return: 1 if the point is a hole, 0 otherwise
 */
static int is_hole(int col, int row)
{
	while (col > 0 || row > 0)
	{
		if ((col % 3 == 1) && (row % 3 == 1))
			return (1);
		col /= 3;
		row /= 3;
	}
	return (0);
}

/**
 * menger - draws a 2D Menger Sponge of a given level
 * @level: the level of the sponge to draw
 */
void menger(int level)
{
	int size;
	int row;
	int col;

	if (level < 0)
		return;

	size = (int)pow(3, level);

	for (row = 0; row < size; row++)
	{
		for (col = 0; col < size; col++)
		{
			if (is_hole(col, row))
				putchar(' ');
			else
				putchar('#');
		}
		putchar('\n');
	}
}
