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
	
	for (size_t i = 0; i < comet.size(); ++i)
		pcomet *= comet[i] - 64;

	for (size_t i = 0; i < group.size(); ++i)
		pgroup *= group[i] - 64;
	
	if (pcomet % 47 == pgroup % 47)
		fout << "GO\n";
	else
		fout << "STAY\n";

	return 0;
}
