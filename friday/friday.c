/*
ID: janko.j1
PROG:friday 
LANG: C
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_YEAR (1900)

static int freq[7];
typedef int bool;
#define false 0
#define true 1

//#define DEBUG 1

bool is_leap(int idyear) {
	int year = START_YEAR + idyear;
	if (year % 4 != 0)
		return false;
	else 
		return (year % 100 != 0) || (year % 400 == 0);
}

int next_day_of_week(int dayofweek, int delta) {
	return (dayofweek + (delta % 7)) % 7;
}

int deltas_normal[] = { 12, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 };
int deltas_leap[] = { 12, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 };
char *days[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

int process_year(int idyear, int first_day) {
	bool leap = is_leap(idyear);
	int * deltas = leap ? &deltas_leap[0] : &deltas_normal[0];
	int idday = 1; int dayofweek = first_day;
	for (int i = 0; i < 12; ++i) {
		idday += deltas[i];
		dayofweek = (dayofweek + (deltas[i] % 7)) % 7;
#if DEBUG
		printf("%d/13/%d was a %s.\n", 1+i, 1900 + idyear, days[dayofweek]);
#endif
		freq[dayofweek]++;
	}

#if DEBUG
		printf("1/1/%d was a %s.\n", 1901 + idyear, days[next_day_of_week(first_day, leap ? 365 : 364)]);
#endif
	return next_day_of_week(first_day, leap ? 366 : 365);
}

int main() {
	FILE *fin = fopen("friday.in", "r");
	FILE *fout = fopen("friday.out", "w");
	int N;
	fscanf(fin, "%d", &N);
	int first_day = 2; // First day of 1900 is a Monday
	for (int i = 0; i < N; ++i)
		first_day = process_year(i, first_day);

	for (int i = 0; i < 7; ++i)
		if (i < 6)
			fprintf(fout, "%d ", freq[i]);
		else 
			fprintf(fout, "%d", freq[i]);
	fprintf(fout, "\n");

	exit(0);
}
