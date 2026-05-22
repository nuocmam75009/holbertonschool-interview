#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * print_subarray - prints elements of a subarray separated by ", "
 * @array: pointer to the first element
 * @size: number of elements to print
 */
static void print_subarray(int *array, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
	{
		if (i > 0)
			printf(", ");
		printf("%d", array[i]);
	}
	printf("\n");
}

/**
 * merge - merges two sorted halves of array into itself using a temp buffer
 * @array: the array containing both halves contiguously
 * @left_size: number of elements in the left half
 * @right_size: number of elements in the right half
 * @buf: temporary buffer of at least (left_size + right_size) elements
 */
static void merge(int *array, size_t left_size, size_t right_size, int *buf)
{
	size_t i = 0, j = 0, k = 0;
	int *left = array;
	int *right = array + left_size;
	size_t total = left_size + right_size;

	printf("Merging...\n");
	printf("[left]: ");
	print_subarray(left, left_size);
	printf("[right]: ");
	print_subarray(right, right_size);

	while (i < left_size && j < right_size)
	{
		if (left[i] <= right[j])
			buf[k++] = left[i++];
		else
			buf[k++] = right[j++];
	}
	while (i < left_size)
		buf[k++] = left[i++];
	while (j < right_size)
		buf[k++] = right[j++];

	for (k = 0; k < total; k++)
		array[k] = buf[k];

	printf("[Done]: ");
	print_subarray(array, total);
}

/**
 * merge_recursive - recursively splits and merges subarrays
 * @array: pointer to the current subarray within the original array
 * @size: number of elements in this subarray
 * @buf: shared temporary buffer
 */
static void merge_recursive(int *array, size_t size, int *buf)
{
	size_t left_size;
	size_t right_size;

	if (size < 2)
		return;

	left_size = size / 2;
	right_size = size - left_size;

	merge_recursive(array, left_size, buf);
	merge_recursive(array + left_size, right_size, buf);
	merge(array, left_size, right_size, buf);
}

/**
 * merge_sort - sorts an array in ascending order using merge sort
 * @array: the array to sort
 * @size: number of elements in the array
 */
void merge_sort(int *array, size_t size)
{
	int *buf;

	if (!array || size < 2)
		return;

	buf = malloc(sizeof(int) * size);
	if (!buf)
		return;

	merge_recursive(array, size, buf);

	free(buf);
}
