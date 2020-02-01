/*
ID: janko.j1
PROG: ride
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int hash(const char* s) {
	int h = 1;
	for (int i = 0; s[i] && isalpha(s[i]); ++i)
		h = (h * (s[i] - 'A' + 1)) % 47;
	return h;
}

int main() {
	FILE *fin, *fout;
	fin = fopen("ride.in", "r");
	fout = fopen("ride.out", "w");
	
	char comet[100], group[100];
	fgets(comet, sizeof comet, fin);
	fgets(group, sizeof group, fin);
	
	if (hash(comet) == hash(group))
		fputs("GO\n", fout);
	else
		fputs("STAY\n", fout);

	exit(0);
}
