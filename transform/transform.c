/*
ID: janko.j1
PROG: transform
LANG: C
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 10
typedef struct Square {
	char data[MAXN][MAXN+1];
	int N;
} Square;

typedef void (*fnTransform)(int i, int j, int N, int *k, int *l);

bool iseq(const Square *original, const Square *transform, fnTransform f) {
	int N = original->N;
	int k, l;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			f(i, j, N, &k, &l);
#if DEBUG
			printf("Comparing original[%d][%d] ('%c') to transformed[%d][%d] ('%c')...", i, j, original->data[i][j], k, l, transform->data[k][l]);
			if (original->data[i][j] != transform->data[k][l]) {
				printf("FAILED\n");
				return false;
			}
			printf("OK.\n");
#else
			if (original->data[i][j] != transform->data[k][l])
				return false;
#endif
		}
	}
	return true;
}

void identity(int i, int j, int N, int *k, int *l) { *k = i; *l = j; }
void rot90(int i, int j, int N, int *k, int *l) { *k = j; *l = N - 1 - i; }
void rot180(int i, int j, int N, int *k, int *l) { *k = N - 1 - i; *l = N - 1 - j; }
void rot270(int i, int j, int N, int *k, int *l) { *k = N - 1 - j; *l = i; }
void refl(int i, int j, int N, int *k, int *l) { *k = i; *l = N - 1 - j; }
void comb90(int i, int j, int N, int *k, int *l) { refl(i, j, N, k, l); rot90(*k, *l, N, k, l); }
void comb180(int i, int j, int N, int *k, int *l) { refl(i, j, N, k, l); rot180(*k, *l, N, k, l); }
void comb270(int i, int j, int N, int *k, int *l) { refl(i, j, N, k, l); rot270(*k, *l, N, k, l); }

#define NUMFNS 8
#define INVALIDFN 7
fnTransform fns[NUMFNS] = { rot90, rot180, rot180, refl, comb90, comb180, comb270, identity };
int fnids[NUMFNS] = { 1, 2, 3, 4, 5, 5, 5, 6 };
#if DEBUG
const char *fnnames[NUMFNS] = { "ROT90", "ROT180", "ROT270", "REFL", "COMB90", "COMB180", "COMB270", "IDENTITY" };
#endif

Square original, transformed;

int main(int argc, char **argv) {
	FILE *fin = fopen("transform.in", "r");
	FILE *fout = fopen("transform.out", "w");
	int N;
	fscanf(fin, "%d", &N);
	original.N = transformed.N = N;
	for (int i = 0; i < N; i++)
		fscanf(fin, "%s", original.data[i]);
	for (int i = 0; i < N; i++)
		fscanf(fin, "%s", transformed.data[i]);

	int matchedfn = INVALIDFN;
	for (int i = 0; i < NUMFNS; ++i) {
#if DEBUG
		printf("Matching using function %s.\n", fnnames[i]);
#endif
		if (iseq(&original, &transformed, fns[i])) {
			matchedfn = fnids[i];
			break;
		}
	}

	fprintf(fout, "%d\n", matchedfn);
	exit(0);
}
