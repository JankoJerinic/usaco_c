/*
ID: janko.j1
PROG:gift1 
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNP 10
#define MAXNAMELEN 15
char names[MAXNP][MAXNAMELEN];
int funds[MAXNP];

static const char * infile = "gift1.in";

int idofname(int np, const char * name) {
	for (int i = 0; i < np; ++i) {
		const char * p1 = name;
		const char * p2 = &names[i][0];
		while (*p1 != 0 && *p2 != 0 && *p1 == *p2) {
			p1++;
			p2++;
		};
		if (*p1 == 0 && *p2 == 0)
			return i;
	}
	return -1;
}

int main() {
	FILE *fin = fopen(infile, "r");
	FILE *fout = fopen("gift1.out", "w");
	int np = 0;
	fscanf(fin, "%d\r\n", &np);
	for (int i = 0; i < np; ++i) {
		fscanf(fin, "%s", names[i]);
	}
	 
	char namesrc[MAXNAMELEN];
	char namedst[MAXNAMELEN];
	memset(funds, 0, sizeof(funds));
	
	for (int i = 0; i < np; ++i) {
		fscanf(fin, "%s", namesrc);
		int idsrc = idofname(np, namesrc);
#if DEBUG
		printf("Processing players '%s' at position %d...\n", namesrc, idsrc);
#endif

		int fund, ndiv;
		fscanf(fin, "%d%d", &fund, &ndiv);
#if DEBUG
		printf("Player distributing %d funds to %d players.\n", fund, ndiv);
#endif
		if (fund > 0 && ndiv > 0) {
			int deduct = ndiv * (fund / ndiv);
			funds[idsrc] -=  ndiv * (fund / ndiv);

			for (int j = 0; j < ndiv; ++j) { 
				fscanf(fin, "%s", namedst);
				int iddst = idofname(np, namedst);
				funds[iddst] += fund / ndiv;
			}
		}
	}

	for (int i = 0; i < np; ++i) {
		fprintf(fout, "%s %d\n", names[i], funds[i]);
	}
	
	exit(0);
}
