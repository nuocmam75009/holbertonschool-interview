#ifndef SANDPILES_H
#define SANDPILES_H

/**
 * sandpiles_sum - Computes the sum of two sandpiles
 * @grid1: First 3x3 grid
 * @grid2: Second 3x3 grid
 *
 * Description: The function adds grid2 to grid1 and stabilizes grid1
 * A sandpile is stable when no cell contains more than 3 grains
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3]);

#endif /* SANDPILES_H */
