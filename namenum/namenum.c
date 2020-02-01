/*
ID: janko.j1
PROG: namenum
LANG: C
*/
#define __PROGNAME__ "namenum"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 0
#define MAXNAMES 5000
#define MAXNAMELEN 12
char names[MAXNAMES][MAXNAMELEN + 1];
int dictsize;

bool isValidName(const char * name, char (*dict)[MAXNAMELEN + 1], int dictsize) {
	int l = 0, r = dictsize - 1;
	while (l <= r) {
		int m = (l + r) >> 1;
		const char *dictname = dict[m];
#if DEBUG
		printf("Comparing %s at index %d [left = %d, right = %d]\n", dictname, m, l, r);
		}
#endif
		int cmp = strcmp(name, dictname);
		if (cmp == 0)
			return true;
		else if (cmp < 0) {
			r = m - 1;
		} else {
			l = m + 1;
		}
	}
	return false;
}

char nummap[][3] = {
	{'A', 'B', 'C'}, // 2
	{'D', 'E', 'F'}, // 3
	{'G', 'H', 'I'}, // 4
	{'J', 'K', 'L'}, // 5
	{'M', 'N', 'O'}, // 6
	{'P', 'R', 'S'}, // 7
	{'T', 'U', 'V'}, // 8
	{'W', 'X', 'Y'}  // 9
}; 

void search(int curr, char *num, char *tmp, int *ids, int n, FILE *fout) {
	if (curr == n) {
		if (isValidName(tmp, names, dictsize))
			fprintf(fout, "%s\n", tmp);
	} else {
		while (ids[curr] < 3) {
			tmp[curr] = nummap[num[curr] - '2'][ids[curr]];
			ids[curr]++;
			search(curr + 1, num, tmp, ids, n, fout);
		}
		ids[curr] = 0;
	}
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	FILE *fdict = fopen("dict.txt", "r");
	dictsize = 0;
	while (!feof(fdict)) {
		fscanf(fdict, "%s", names[dictsize++]);
	}

	assert(isValidName("AARON", names, dictsize));
	assert(isValidName("ZYTA", names, dictsize));

	char num[MAXNAMELEN];
	char tmp[MAXNAMELEN];
	int ids[MAXNAMELEN] = {0};
	
	fscanf(fin, "%s", num);
	int n = strlen(num);
	tmp[n] = '\0';

	search(0, num, tmp, ids, n, fout);
	if (ftell(fout) == 0)
		fprintf(fout, "NONE\n");

	exit(0);
}

