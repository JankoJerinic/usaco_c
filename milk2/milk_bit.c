/*
ID: janko.j1
PROG: 
LANG: C
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void printbin(int d) {
	if (d == 0) printf("0\n");
	else if (d < 0) { printf("-"); d = -d; }
	
	int nbd = 0, dt = d;
	while (dt > 0) { nbd++; dt >>= 1; }

	char *out = alloca((1 + nbd) * sizeof(char));
	out[nbd] = '\0';
	while (d > 0) { out[--nbd] = '0' + (d & 1); d >>= 1; }
	printf("%s\n", out);
}

void testbit() {
	int x = 251;
	while (x > 0) {
		printbin(x);
		x -= (x & -x);
	}

	x = 45;
	while (x < 5000) {
		printbin(x);
		x += (x & -x);
	}
}

const int MAXN = 5000;
int times[2*MAXN];

void update(int *tree, int value, int i, int maxval) {
	while (i <= maxval) {
		tree[i] += value;
		i += (i & -i);
	}
}

int read(int *tree, int i) {
	int sum = 0;
	while (i > 0) {
		sum += tree[i];
		i -= i & i;
	}
	return sum;
}

int main(int argc, char **argv) {
	FILE *fin = fopen("milk2.in", "r");
	FILE *fout = fopen("milk2.out", "w");
	int N, M = 0;

	fscanf(fin, "%d", &N);
	for (int i = 0, k = 0; i < N; ++i) {
		int milk_start, milk_stop;
		fscanf(fin, "%d %d", &milk_start, &milk_stop);
		times[k++] = milk_start;
		times[k++] = milk_stop;
		if (milk_start > M) M = milk_start;
		if (milk_stop > M) M = milk_stop;
	}

	int *bit = (int *)malloc((M + 2) * sizeof(int));
	memset(bit, 0, (M + 2) * sizeof(int));

	for (int i = 0; i < N; ) {
		update(bit, 1, times[i++], N+1);
		update(bit, -1, times[i++], N+1);
	}

	exit(0);
}
