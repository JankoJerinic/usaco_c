/*
ID: janko.j1
PROG: wormhole 
LANG: C
*/
#define __PROGNAME__ "wormhole"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 12
typedef struct Hole {
	int x;
	int y;
	int id;
	int next;
} Hole;

int N;
static int NL;
Hole holes[MAXN];

void printHoles();
int cmpHoles(const void *p, const void *q);

#define isset(bitmask, id) ((bitmask) & (1 << (id)))
#define setbit(bitmask, id) bitmask |= (1 << (id))
#define unsetbit(bitmask, id) bitmask &= ~(1 << (id))
#define visited(id) isset(bitmask, (id))
#define visit(id) setbit(bitmask, (id))
#define leave(id) unsetbit(bitmask, (id))


bool findloop() {
	bool loop = false;
	for (int src = 0; src < N && !loop; ++src) {
		int bitmask = 0;
		int current = src;
		while (current != -1) {
			visit(current);
			int next = holes[current].next;

			if (next < N - 1 && holes[next+1].y == holes[next].y) {
				current = next + 1;

				if (visited(current)) {
					loop = true;
					break;
				}
			}
			else {
				current = -1;
			}
		}
	}
	return loop;
}

void explore(int src, int bitmask, int npairs) {
	if (npairs == N/2) {
		if (findloop()) 
			++NL;
	} else {
		visit(src);
		int srcnext = holes[src].next;

		for (int dst = src + 1; dst < N; ++dst) {
			if (!visited(dst)) {
				visit(dst);
			
				// Pair src and dst wormhole
				holes[src].next = dst;
				int dstnext = holes[dst].next;
				holes[dst].next = src;

				int next = src + 1; 
				while (dst == next || visited(next)) 
					++next;
				
				explore(next, bitmask, npairs + 1);

				leave(dst);
				holes[dst].next = dstnext;
			}
		}

		holes[src].next = srcnext;
		unsetbit(bitmask, src);
	}
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");

	fscanf(fin, "%d", &N);
	assert(N >= 2 && N <= 12);
	for (int i = 0; i < N; ++i) {
		fscanf(fin, "%d %d", &holes[i].x, &holes[i].y);
		holes[i].next = -1;
	}

	qsort(holes, N, sizeof(Hole), cmpHoles);
	for (int i = 0; i < N; ++i) {
		holes[i].id = i;
		if (i < N - 1) { 
			if (holes[i].y == holes[i+1].y)
				holes[i].next = i + 1;
		}
	}

	explore(0, 0, 0);
	fprintf(fout, "%d\n", NL);

	exit(0);
}

int cmpHoles(const void *p, const void *q) {
	const Hole *l = (const Hole *)p;
	const Hole *r = (const Hole *)q;
	int d = l->y - r->y;
	if (d != 0)
		return d;
	return l->x - r->x;
}
