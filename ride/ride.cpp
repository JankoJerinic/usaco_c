/*
ID: janko.j1
PROG: ride
LANG: C++
*/
#include <fstream>
using namespace std;

int main() {
	ifstream fin("ride.in");
	ofstream fout("ride.out");
	string comet, group;
	fin >> comet >> group;
	int pcomet = 1, pgroup = 1;
	/*for (char c: comet) {
		pcomet *= (int)(1 + c - 'A');
	}
	for (char c: group) {
		pgroup *= (int)(1 + c - 'A');
	}*/
	
	if (pcomet % 47 == pgroup % 47)
		fout << "GO\n";
	else
		fout << "STAY\n";
	return 0;
}
