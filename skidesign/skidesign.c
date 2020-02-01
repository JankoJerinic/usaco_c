/*
ID: janko.j1
PROG: skidesign 
LANG: C
*/
#define __PROGNAME__ "skidesign"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define SQR(x) ((x) * (x))
#define MAXN_HILLS 1000
#define MAX_HEIGHT 100
#define MAXD 17
static int N, NH;
static int hills[1+MAX_HEIGHT];
static int heights[1+MAX_HEIGHT][2];

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");

	fscanf(fin, "%d", &N);
	for (int i = 0, h; i < N; ++i) {
		fscanf(fin, "%d", &h);
		++hills[h];
	}

	for (int h = 0; h <= MAX_HEIGHT; ++h) {
		if (hills[h]) {
			heights[NH][0] = h;
			heights[NH][1] = hills[h];
			++NH;
		}
	}

	int cost_min = INT_MAX;
	for (int hbottom = 0; hbottom <= MAX_HEIGHT - MAXD; ++hbottom) {
		int htop = hbottom + MAXD;
		int cost = 0;
		for (int j = 0, h; j < NH; ++j) {
			h = heights[j][0];
			if (h < hbottom)
				cost += heights[j][1] * SQR(hbottom - h);
			else if (h > htop)
				cost += heights[j][1] * SQR(h - htop);
		}

		if (cost_min > cost)
			cost_min = cost;
	}

	fprintf(fout, "%d\n", cost_min);
	exit(0);
}
