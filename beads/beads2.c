/*
ID: janko.j1
PROG: beads
LANG: C
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 350
char necklace[MAXN];

struct BeadRange_t {
	char color;
	unsigned int length;
	struct BeadRange_t *next;
	struct BeadRange_t *prev;
#if DEBUG
	int id;
#endif
}; 

typedef struct BeadRange_t BeadRange;

BeadRange *newBeadRange(char color, int length) {
	BeadRange *br = (BeadRange *)malloc(sizeof(BeadRange));
	br->color = color;
	br->length = length;
	br->next = br->prev = NULL;
#if DEBUG
	br->id = 0;
#endif
	return br;
}

void deleteList(BeadRange *head) {
	BeadRange *current = head->next;
	while (current != head && current != NULL) {
		BeadRange *temp = current;
		current = current->next;
		free(temp);
	}
	free (head);
}

void setNext(BeadRange *prev, BeadRange *next) {
	prev->next = next;
	if (next != NULL)
		next->prev = prev;
#if DEBUG
	next->id = prev->id + 1;
#endif
}

void printBeadRanges(BeadRange *head) {
	BeadRange *current = head;
	do {
#if PRINTID
		printf("[%d %c (%d)]", current->length, current->color, current->id);
#else
		printf("[%d %c]", current->length, current->color);
#endif
		current = current->next;
		if (current != head && current != NULL)
			printf("->");
	 } while (current != head && current != NULL);
	printf("\n");
}

bool debug = false;
int main(int argc, char **argv) {
	if (argc > 1 && 0 == strcmp(argv[1], "-d"))
		debug = true;

	FILE *fin = fopen("beads.in", "r");
	FILE *fout = fopen("beads.out", "w");
	int N;
	fscanf(fin, "%d", &N);
	fscanf(fin, "%s", necklace);

	if (debug)
		printf("%s\n", necklace);


	int max = 0;
	fprintf(fout, "%d\n", max);
	exit(0);
}
