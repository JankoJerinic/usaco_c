/*
ID: janko.j1
PROG: beads
LANG: C
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0
#define PRINTID 0
#define MAXN 350
#define WHITE ('w')
#define RED ('r')
#define BLUE ('b')

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

int main() {
	FILE *fin = fopen("beads.in", "r");
	FILE *fout = fopen("beads.out", "w");
	int N;
	fscanf(fin, "%d", &N);
	fscanf(fin, "%s", necklace);
#if DEBUG
	printf("%s\n", necklace);
#endif

	// Create a linked list of ranges of same-colored beads.
	BeadRange *head = NULL, *tail = NULL;
	for (int i = 0; i < N; ) {
		char cur_col = necklace[i];
		int iRangeStart = i;
		for (; necklace[i] == cur_col && i < N; ++i) ;
		int iRangeEnd = i;

		BeadRange *range = newBeadRange(cur_col, iRangeEnd - iRangeStart);

		if (head == NULL)
			head = range;
		if (tail == NULL)
			tail = head;
		else
			setNext(tail, range);
		tail = range;
	}

	int max = 0;
	if (head == tail || head->next == tail) {
		// If we have one, or two ranges, then maximum is the entire necklace.
		max = N;
	} else {
		// Make a circular list
		tail->next = head;
		head->prev = tail;
#if DEBUG
		printf("Necklace as initial linked list:\n");
		printBeadRanges(head);
#endif

		// In the first pass, paint all the white beads that sit between two ranges
		// of the same color, e.g. [1 r]->[2 w]->[3 r] should become [1 r]->[2 r]->[3 r]
		BeadRange *prev = tail, *curr = head, *next = head->next;
		while (next != head) {
			if (prev->color == next->color) {
				if (curr->color == WHITE) {
					assert(prev->color == RED || prev->color == BLUE);
					curr->color = prev->color;
				}
			}
			curr = curr->next; prev = prev->next; next = next->next;
		}
#if DEBUG
		printf("Necklace after painting eligible white ranges:\n");
		printBeadRanges(head);
#endif
		// Now we know that there are no white ranges that sit between same colored ranges.
		// We proceed to merge all chains of same-colored ranges into a single range.
		curr = head; next = head->next;
		while (curr != tail) {
			while (curr != tail && next->color == curr->color) {
#if DEBUG
				printf("Merging ranges %d and %d. Resulting range %d with length %d.\n", curr->id, next->id, curr->id, curr->length + next->length);
#endif
				// Merge the next range.
				curr->length += next->length;
				BeadRange *temp = next->next;
				if (tail == next) {
					tail = curr;
				}
				free(next);
				curr->next = temp;
				temp->prev = curr;
				next = temp;
			}
			curr = next;
			next = curr->next;
		}

#if DEBUG
		printf("Necklace before final merging:\n");
		printf("Head ID = %d, Tail ID = %d.\n", head->id, tail->id);
		printBeadRanges(head);
#endif
		// Check if head and tail are of the same color, then merge them.
		if (tail->color == head->color) {
			tail->length += head->length;

			BeadRange *temp = head->next;
			free(head);
			tail->next = temp;
			temp->prev = tail;
			head = temp;
		}
#if DEBUG
		printf("Necklace after final merging:\n");
		printf("Head ID = %d, Tail ID = %d.\n", head->id, tail->id);
		printBeadRanges(head);
#endif
		// If we are left with 1 or 2 ranges, maximum is the entire necklace.
		if (tail == head || head->next == tail || head->next == tail->prev) {
			max = N;
		} else {
			BeadRange *beg_left = tail, *beg_right = head;
			do {
				BeadRange *curr_left = beg_left, *curr_right = beg_right;
				int len_left = curr_left->length;
#if DEBUG
				printf("Collecting left starting from [%d %c], initial length = %d.\n", curr_left->length, curr_left->color, len_left);
#endif
				char col_left = curr_left->color;
				curr_left = curr_left->prev;
				if (col_left == WHITE) {
					assert(curr_left->color != WHITE);
					col_left = curr_left->color;
					len_left += curr_left->length;
#if DEBUG
				printf("Collected left [%d %c], new length = %d.\n", curr_left->length, curr_left->color, len_left);
#endif
					curr_left = curr_left->prev;
				}
				while ((curr_left->color == col_left || curr_left->color == WHITE) && curr_left != curr_right) {
					len_left += curr_left->length;
#if DEBUG
				printf("Collected left [%d %c], new length = %d.\n", curr_left->length, curr_left->color, len_left);
#endif
					curr_left = curr_left->prev;
				}

				int len_right = curr_right->length;
#if DEBUG
				printf("Collecting right starting from [%d %c], initial length = %d.\n", curr_right->length, curr_right->color, len_right);
#endif
				char col_right = curr_right->color;
				curr_right = curr_right->next;
				if (col_right == WHITE) {
					assert(curr_right->color != WHITE);
					col_right = curr_right->color;
					len_right += curr_right->length;
#if DEBUG
				printf("Collected right [%d %c], new length = %d.\n", curr_right->length, curr_right->color, len_right);
#endif
					curr_right = curr_right->next;
				}
				while ((curr_right->color == col_right || curr_right->color == WHITE) && curr_left != curr_right) {
					len_right += curr_right->length;
#if DEBUG
				printf("Collected right [%d %c], new length = %d.\n", curr_right->length, curr_right->color, len_right);
#endif
					curr_right = curr_right->next;
				}


				if (len_left + len_right > max)
					max = len_left + len_right;

				beg_right = beg_right->next;
				beg_left = beg_left->next;

			} while (beg_right != head);
		}
	}

	fprintf(fout, "%d\n", max);

	exit(0);
}
