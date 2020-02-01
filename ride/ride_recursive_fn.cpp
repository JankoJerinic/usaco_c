/*
ID: janko.j1
PROG: ride
LANG: C++
*/
#include <fstream>
using namespace std;

int eval(const string& s, size_t pos = 0) {
	if (pos == s.size())
		return 1;
	return ((s[pos] - 64)* eval(s, pos + 1)) % 47;
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
