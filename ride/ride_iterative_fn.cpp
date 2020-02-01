/*
ID: janko.j1
PROG: ride
LANG: C++
*/
#include <fstream>
using namespace std;

int eval(const string& s) {
	int p = 1;
	for (size_t i = 0; i < s.size(); ++i)
		p *= s[i] - 64;
	return p % 47;
}

int main() {
	ifstream fin("ride.in");
	ofstream fout("ride.out");
	string comet, group;
	fin >> comet >> group;
	
	if (eval(comet) == eval(group))
		fout << "GO\n";
	else
		fout << "STAY\n";

	return 0;
}
