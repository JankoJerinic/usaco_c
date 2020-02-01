/*
ID: janko.j1
PROG: milk3
LANG: C
*/
#define __PROGNAME__ "milk3"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAXV 20
#define N 3
static int capacity[N];
static int volume[N];
static int solutions[1 + MAXV];
static unsigned char hash[1 + MAXV*MAXV*MAXV];

void printState(void) {
	printf("A:%d, B:%d, C:%d\n", volume[0], volume[1], volume[2]);
}

int getHash(void) {
	int c = 1, hash = 0;
	for (int i = 0; i < N; ++i) {
		hash += volume[i] * c;
		c *= MAXV;
	}
	return hash;
}

int getv(int src, int dst) {
	return volume[src] < capacity[dst] - volume[dst] ? 
		volume[src] :
		capacity[dst] - volume[dst];
}

void move(int v, int src, int dst) {
	volume[src] -= v;
	volume[dst] += v;
	assert(volume[src] >= 0 && volume[src] <= capacity[src]);
	assert(volume[dst] >= 0 && volume[dst] <= capacity[dst]);
}

#define setVisited() \
	/*printf("State [%d, %d, %d] marked as visited, hash = %d.\n", volume[0], volume[1], volume[2], getHash()); */\
	hash[getHash()] = 1;

void search(void) {
	// We allow the recursion to go one level deep because coming back to the original state is legitimate.
	if (hash[getHash()] > 0) {
		return; 
	}

	// Mark state as visited
	setVisited();
	
	for (int src = 0; src < N; ++src)
		for (int dst = 0; dst < N; ++dst) {
			if (src == dst) continue;

			int v = getv(src, dst);
			move(v, src, dst);

			if (volume[0] == 0) {
				// Law of conservation of milk :)
				assert(volume[1] + volume[2] == capacity[2]);
				solutions[volume[2]] = 1;
			}

			search();
			move(v, dst, src); // Undo
		}
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");

	fscanf(fin, "%d %d %d", capacity, capacity + 1, capacity + 2);
	volume[0] = volume[1] = 0;
	volume[2] = capacity[2];

	search();
	
	int n = 0;
	for (int v = 0; v <= MAXV; ++v) {
		if (solutions[v] > 0) {
			solutions[n++] = v;
		}
	}

	for (int i = 0; i < n; ++i) {
		fprintf(fout, "%d", solutions[i]);
		if (i < n - 1)
			fprintf(fout, " ");
	}
	fprintf(fout, "\n");
	exit(0);
}
