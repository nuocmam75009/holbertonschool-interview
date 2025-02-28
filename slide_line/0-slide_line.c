#include "slide_line.h"

/**
 * slide_left - Slides and merges an array of integers to the left
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 *
 * Return: 1 upon success, 0 upon failure
 */
static int slide_left(int *line, size_t size)
{
	size_t i, pos = 0;
	int merged[32] = {0};

	/* First pass: slide non-zero numbers to the left */
	for (i = 0; i < size; i++)
	{
		if (line[i] != 0)
			merged[pos++] = line[i];
	}

	/* Second pass: merge identical numbers */
	for (i = 0; i < pos - 1; i++)
	{
		if (merged[i] == merged[i + 1])
		{
			merged[i] *= 2;
			merged[i + 1] = 0;
		}
	}

	/* Third pass: slide again to fill gaps created by merging */
	pos = 0;
	for (i = 0; i < size; i++)
	{
		if (merged[i] != 0)
			line[pos++] = merged[i];
	}

	/* Fill the rest with zeros */
	for (i = pos; i < size; i++)
		line[i] = 0;

	return (1);
}

/**
 * slide_right - Slides and merges an array of integers to the right
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 *
 * Return: 1 upon success, 0 upon failure
 */
static int slide_right(int *line, size_t size)
{
	int i, pos;
	int merged[32] = {0};

	/* First pass: slide non-zero numbers to the right */
	pos = size - 1;
	for (i = size - 1; i >= 0; i--)
	{
		if (line[i] != 0)
			merged[pos--] = line[i];
	}

	/* Second pass: merge identical numbers */
	for (i = size - 1; i > 0; i--)
	{
		if (merged[i] == merged[i - 1])
		{
			merged[i] *= 2;
			merged[i - 1] = 0;
		}
	}

	/* Third pass: slide again to fill gaps created by merging */
	pos = size - 1;
	for (i = size - 1; i >= 0; i--)
	{
		if (merged[i] != 0)
			line[pos--] = merged[i];
	}

	/* Fill the rest with zeros */
	for (i = pos; i >= 0; i--)
		line[i] = 0;

	return (1);
}

/**
 * slide_line - Slides and merges an array of integers
 * @line: Points to an array of integers
 * @size: Number of elements in @line
 * @direction: SLIDE_LEFT or SLIDE_RIGHT
 *
 * Return: 1 upon success, 0 upon failure
 */
int slide_line(int *line, size_t size, int direction)
{
	if (!line || (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
		return (0);

	if (direction == SLIDE_LEFT)
		return (slide_left(line, size));
	else
		return (slide_right(line, size));
}
