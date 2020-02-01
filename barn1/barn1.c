/*
ID: janko.j1
PROG: barn1
LANG: C
*/
#define __PROGNAME__ "barn1"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0

int cmp(const void *i1, const void *i2) {
	return (*(int *)i1) - (*(int *)i2);
}

#if DEBUG
void printarr(const int *arr, int n) {
	printf("[");
	for (int i = 0; i < n-1; ++i)
		printf("%d, ", arr[i]);
	printf("%d]\n", arr[n-1]);
}
#endif

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	int M, S, C;
	fscanf(fin, "%d %d %d", &M, &S, &C);
	int *cows = (int *)malloc(C * sizeof(int));
	for (int i = 0; i < C; ++i)
		fscanf(fin, "%d", cows + i);
	qsort(cows, C, sizeof(int), cmp);
#if DEBUG
	printarr(cows, C);
#endif

#define MAXS 200
#define MAXM 50
	 int B[1+MAXM][MAXS];
	 memset(B, 0, MAXS * MAXM * sizeof(int));

	 // No point in using more boards than cows. 
	 if (M > C) M = C;

	 // B[c][m] - how many stalls we've blocked with m boards if we've blocked up to cow C
	 // Optimum is reached for some k where:
	 // B[c][m] = B[k][m-1] + (1 + cows[c] - cows[k])
	 // With a single board, we block all stalls from 1..cows[i]
	 for (int i = 0; i < C; ++i) {
		 B[1][i] = cows[i] - cows[0] + 1;
	 }

	 for (int m = 2; m <= M; ++m) {
		for (int c = m-1; c < C; ++c) {
			// Theoretical maximum is board everything up to current stall
			int min = cows[c] - cows[0] + 1;

			for (int k = m-2; k < c; ++k) {
				// Expand the boarding by the next segment.
				// We've boarded up to cows[k] with m - 1 plan and are now considering how to 
				// board up to cows[c] with an additional plank. This extra segment is 
				// (cows[c] - cows[k+1] + 1) long. 
				// k is strictly less than c, for k == c-1 edge case, we add a unit long board.
				int newmin = B[m-1][k] + (1 + cows[c] - cows[k+1]);

				if (min > newmin)
					min = newmin;
			}

			B[m][c] = min; 
		}
	 }

#if DEBUG
	 for (int i = 1; i <= M; ++i) {
		 printf("%d: ", i);
		 printarr(B[i], C);
	 }
#endif

	fprintf(fout, "%d\n", B[M][C-1]);
	free(cows);
	exit(0);
}
