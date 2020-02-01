/*
ID: janko.j1
PROG: milk2 
LANG: C
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1

const int MAXN = 5000;

typedef struct MilkEvent {
	int time;
	bool start;
#if DEBUG
	int id;
#endif
} MilkEvent;

#if DEBUG
void setEvent(MilkEvent *event, int time, bool start, int id) {
#else
void setEvent(MilkEvent *event, int time, bool start) {
#endif
	assert(event != NULL);
	event->time = time;
	event->start = start;
#if DEBUG
	event->id = id;
#endif
}

int cmpEvents(const void *ptr1, const void *ptr2) {
	const MilkEvent *event1 = (MilkEvent *)ptr1;
	const MilkEvent *event2 = (MilkEvent *)ptr2;
	int timediff = event1->time - event2->time;
	if (timediff != 0)
		return timediff;
	else if (event1->start ^ event2->start)
		return event1 ? 1 : -1;
	else
		return 0;
}


#if DEBUG
void printEvent(const MilkEvent event) {
	printf("Farmer %d %s milking at time %d.\n", event.id, event.start ? "starts" : "stops", event.time);	
}
#endif

int main(int argc, char **argv) {
	FILE *fin = fopen("milk2.in", "r");
	FILE *fout = fopen("milk2.out", "w");

	int N;
	fscanf(fin, "%d", &N);
	MilkEvent *events = malloc(2 * N * sizeof(MilkEvent));
	for (int i = 0, k = 0; i < N; ++i) {
		int milk_start, milk_stop;
		fscanf(fin, "%d %d", &milk_start, &milk_stop);
#if DEBUG
		setEvent(&events[k++], milk_start, true, i);
		setEvent(&events[k++], milk_stop, false, i);
#else
		setEvent(&events[k++], milk_start, true);
		setEvent(&events[k++], milk_stop, false);
#endif
	}

	int NEvents = 2 * N;

	// Sort events, earliest to latest
	qsort(events, NEvents, sizeof(MilkEvent), cmpEvents);

	int milkingStartTime = -1, milkingEndTime = -1;
	int maxMilkingTime = 0, maxNotMilkingTime = 0;
	int nMilking = 0;
	for (int i = 0; i < NEvents;) {
		int time = events[i].time;
		int delta = 0;
		while (i < NEvents && time == events[i].time) {
			if (events[i].start) delta++; else delta--;
			time = events[i++].time;
		}

		if (nMilking == 0) {
			// Beginning of a new milking range
			assert(delta > 0);
			milkingStartTime = time;
			if (milkingEndTime >= 0) {
				int notMilkingTime = milkingStartTime - milkingEndTime;
				if (notMilkingTime > maxNotMilkingTime)
					maxNotMilkingTime = notMilkingTime;
			}
		} else {
			assert(nMilking > 0 && milkingStartTime >= 0);
			if (nMilking + delta == 0) {
				milkingEndTime = time;
				int milkingTime = milkingEndTime - milkingStartTime;
				if (milkingTime > maxMilkingTime)
					maxMilkingTime = milkingTime;
				}
			}
		nMilking += delta;
	}

	free(events);
	fprintf(fout, "%d %d\n", maxMilkingTime, maxNotMilkingTime);

	exit(0);
}
