/*
ID: janko.j1
PROG: milk
LANG: C
*/
#define __PROGNAME__ "milk"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXM 5000
typedef struct Farmer {
	int quantity;
	int price;
} Farmer;

int cmpFarmers(const void *farmer1, const void *farmer2) {
	return ((Farmer *)farmer1)->price - ((Farmer *)farmer2)->price;
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	int N, M;
	fscanf(fin, "%d %d", &N, &M);

	Farmer farmers[MAXM];
	for (int i = 0; i < M; ++i) 
		fscanf(fin, "%d %d", &farmers[i].price, &farmers[i].quantity);

	qsort(farmers, M, sizeof(Farmer), cmpFarmers);

	int cost = 0;
	for (int i = 0; i < M && N > 0; ++i) {
		int quantity = farmers[i].quantity < N ? farmers[i].quantity : N;
		cost += quantity * farmers[i].price;
		N -= quantity;
	}

	fprintf(fout, "%d\n", cost);
	exit(0);
}
