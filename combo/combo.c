/*
ID: janko.j1
PROG: combo
LANG: C
*/
#define __PROGNAME__ "combo"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100
#define ND 3
int comb[2][ND];
int hmap[2][5*5*5];
int hn[2];
int tempcomb[ND];
int N;

void sort(int *a, int l, int r);

// Hash function
int hash(int *c) {
	return (c[0]*N + c[1])*N + c[2];
}

int gen_hashes(int icomb, int idigit) {
	if (idigit == ND) {
		hmap[icomb][hn[icomb]++] = hash(tempcomb);
	} else {
		// Produce an array of allowed digits 
		int digits[5];
		int nd = 0;
		for (int d = -2; d <= 2; ++d) {
			int l = comb[icomb][idigit] + d;
			if (l < 1) l = N + l;
			else if (l > N) l = l - N;
			if (l >= 1 && l <= N) 
				digits[nd++] = l;
		}

		// Sort the digit array, so that we can extract unique values
		sort(digits, 0, nd-1);

		for (int id = 0; id < nd; ) {
			int l = digits[id];
			tempcomb[idigit] = l;
			gen_hashes(icomb, idigit + 1);

			// Skip over duplicates
			while (id < 5 && digits[id] == l) id++;
		}
	}
}

void sort(int *a, int l, int r) {
	int i = l, j = r, p=a[(l+r) >> 1];
	do {
		while (a[i] < p) ++i;
		while (a[j] > p) --j;
		if (i <= j) {
			int t = a[i]; a[i] = a[j]; a[j] = t;
			++i; --j; 
		}
	} while (i <= j);
	if (l < j) sort(a, l, j);
	if (i < r) sort(a, i, r);
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	fscanf(fin, "%d", &N);
	assert(1 <= N && N <= 100);

	for (int i = 0; i < 2; ++i) {
		fscanf(fin, "%d %d %d", &comb[i][0], &comb[i][1], &comb[i][2]);

		gen_hashes(i, 0);

		// Sort the hashes, we may have up to 5**3 hash values
		sort(hmap[i], 0, hn[i]-1);
	}

	// "Merge" the sorted arrays of hash values, producing the number of unique hashes
	int n = 0, i = 0, j = 0;
	for (; i < hn[0] && j < hn[1]; ) {
		if (hmap[0][i] < hmap[1][j])  ++i;
		else if (hmap[0][i] > hmap[1][j]) ++j;
		else {
			// Move both cursors, but still count as single hash
			++i; ++j;
		}
		++n;
	}
	// Count any outstanding hashes
	if (i < hn[0]) n += hn[0] - i;
	if (j < hn[1]) n += hn[1] - j;

	fprintf(fout, "%d\n", n);
	exit(0);
}
