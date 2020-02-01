/*
ID: janko.j1
PROG: crypt1
LANG: C
*/
#define __PROGNAME__ "crypt1"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int digitmap[10] = {0};
bool checkdigits(int n) {
	for (; n > 0 && digitmap[n % 10]; n /= 10);
	return n == 0;
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	int N;
	fscanf(fin, "%d", &N);
	int digits[9];
	for (int i = 0; i < N; ++i) {
		fscanf(fin, "%d", digits + i);
		digitmap[digits[i]] = 1;	
	}

	int nsol = 0;
	for (int a = 0; a < N; ++a)
	for (int b = 0; b < N; ++b)
	for (int c = 0; c < N; ++c)
	for (int d = 0; d < N; ++d)
	for (int e = 0; e < N; ++e)
	{
		int x = 100*digits[a] + 10*digits[b] + digits[c];
		int p1 = digits[d] * x;
		int p2 = digits[e] * x;
		int p = 10*p1 + p2;
		if (p1 < 1000 && p2 < 1000 && p > 1000 && p < 10000 && checkdigits(p1) && checkdigits(p2) && checkdigits(p)) {
			nsol++;
		}
	}

	fprintf(fout, "%d\n", nsol);
	exit(0);
}
