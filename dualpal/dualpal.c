/*
ID: janko.j1
PROG: dualpal
LANG: C
*/
#define __PROGNAME__ "dualpal"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char buf[20];

int tobaserevstr(int n, int b, char *str) {
	int d = 0;
	while (n > 0) { str[d++] = n % b; n /= b; }
	str[d] = '\0';
	return d;
}

bool is_palindrome_str(char *str, int n) {
	int l = 0, r = n - 1;
	while (str[l] == str[r]) { l++; r--; }
	return (l >= r);
}

bool is_palindrome(int n, int b) {
	int d = tobaserevstr(n, b, buf);
	return is_palindrome_str(buf, d);
}

char getDigit(char d) {
	return d < 10 ? '0' + d : 'A' + d - 10;
}
void process_str(char *str, int n) {
	for (int i = 0; i < n; ++i) {
		str[i] = getDigit(str[i]);
	}
	for (int i = 0; i < n / 2; ++i) {
		char c = str[i]; str[i] = str[n-1-i]; str[n-1-i] = c;
	}
}

bool isdualpal(int n) {
	int np = 0;
	for (int b = 2; b <= 10 && np < 2; ++b)
		if (is_palindrome(n, b))
			++np;
	return np == 2;
}

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	int N, S;
	fscanf(fin, "%d %d", &N, &S);

	for (int n = S + 1; N > 0; ++n) {
		if (isdualpal(n)) {
			fprintf(fout, "%d\n", n);
			--N;
		}
	}

	exit(0);
}
