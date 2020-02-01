/*
ID: janko.j1
PROG: palsquare
LANG: C
*/
#define __PROGNAME__ "palsquare"
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

int main(int argc, char **argv) {
	FILE *fin = fopen(__PROGNAME__".in", "r");
	FILE *fout = fopen(__PROGNAME__".out", "w");
	int b, d;
	fscanf(fin, "%d", &b);

#if DEBUG
	assert(is_palindrome_str("anavolimilovana", 15));
	assert(is_palindrome_str("abccba", 6));
	assert(is_palindrome_str("abbba", 5));
	assert(!is_palindrome_str("abbda", 5));
#endif

	for (int i = 1; i <= 300; ++i) {
		int n = i*i;
		if (is_palindrome(n, b)) {
			d = tobaserevstr(i, b, buf);
			process_str(buf, d);
			fprintf(fout, "%s ", buf);

			d = tobaserevstr(n, b, buf);
			process_str(buf, d);
			fprintf(fout, "%s\n", buf);
		}
	}

	exit(0);
}
