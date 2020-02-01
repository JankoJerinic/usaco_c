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

#define DEBUG 0
#define MAXN 12
typedef struct Hole {
	int x;
	int y;
	int id;
	int next;
} Hole;

int N;
static int NL;
static int NC;
Hole holes[MAXN];

void printHoles();
int cmpHoles(const void *p, const void *q);

#if DEBUG
#define debug(...) do {  printf(__VA_ARGS__); } while (0)
#else
#define debug ;
#endif

#define isset(bitmask, id) ((bitmask) & (1 << (id)))
#define setbit(bitmask, id) bitmask |= (1 << (id))
#define unsetbit(bitmask, id) bitmask &= ~(1 << (id))
#define visited(id) isset(bitmask, (id))
#define visit(id) setbit(bitmask, (id))
#define leave(id) unsetbit(bitmask, (id))
#define repeat(s, n) for (int __x = 0; __x < (n); ++__x) printf("%s",(s))

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

bool findloop() {
	bool loop = false;
	for (int src = 0; src < N && !loop; ++src) {
		int bitmask = 0;
		debug(ANSI_COLOR_CYAN "Starting search from hole %d.\n" ANSI_COLOR_RESET, src);
		int current = src;
		while (current != -1) {
			visit(current);
			int next = holes[current].next;
			debug("  Jumping from %d to %d.\n", current, next);

			if (next < N - 1 && holes[next+1].y == holes[next].y) {
				current = next + 1;
				debug("  Continuing from next hole on +X axis: %d.\n", current);

				if (visited(current)) {
					debug("  Hole %d already visited! Loop found!\n", next);
					loop = true;
					break;
				}
			}
			else {
				debug("  No hole on +X axis. Exiting!\n");
				current = -1;
			}
		}
	}
	return loop;
}

void explore(int src, int bitmask, int npairs) {
	if (npairs == N/2) {
		++NC;
		// Check cycles
		printHoles();
		
		if (findloop()) {
			++NL;
			debug(ANSI_COLOR_RED "Loop found!\n" ANSI_COLOR_RESET);
		}
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

				debug(" Pairing %d and %d.\n", src, dst);

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
	debug(ANSI_COLOR_YELLOW "PROGRAM BEGIN.\n" ANSI_COLOR_RESET);
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
	debug("Total combinations found: %d\n", NC);
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

void printHoles() {
	int i = 0;
	for (i = 0; i < N; ++i)
		debug("[%d: (%d, %d) -> %d] ",holes[i].id, holes[i].x, holes[i].y, holes[i].next);
	debug("\n");
}
