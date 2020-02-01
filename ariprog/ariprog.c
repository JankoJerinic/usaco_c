/*
ID: janko.j1
PROG: ariprog
LANG: C
*/
#define __PROGNAME__ "ariprog"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MINN 3
#define MAXN 25
#define MINM 1
#define MAXM 250
static int N, M;
int bisquares[1+2*MAXM*MAXM];

int genbisquares() {
	// Generate a set of all [p*p + q*q] numbers such that 0 <= p, q <= M.
	for (int p = 0; p <= M; ++p)
		for (int q = 0; q <= M; ++q) {
			int n = p*p + q*q;
			bisquares[n] = 1;
		}

	// Compact it into a sorted list.
	int Nbsq = 0;
	for (int n = 0; n <= sizeof(bisquares) / sizeof(int); ++n) 
		if (bisquares[n] == 1) {
			bisquares[Nbsq++] = n;
		}
	return Nbsq;
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");

	fscanf(fin, "%d %d", &N, &M);
	int Nbsq = genbisquares();
	printf("Number of bisquares: %d.\n", Nbsq);


	fprintf(fout, "\n");
	exit(0);
}
