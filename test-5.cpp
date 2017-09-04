#include <iostream>
#include <cstdlib>
#include "ConcurrentHashMap.hpp"
#include <list>

using namespace std;

int main(int argc, char **argv) {


	pair<string, unsigned int> p;
	list<string> l = { "corpus", "corpus-1", "corpus-2", "corpus-3", "corpus-4" };

	if (argc != 3) {
		cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
		return 1;
	}
	p = maximum(atoi(argv[1]), atoi(argv[2]), l);
	cout << p.first << " " << p.second << endl;



  l = { "corpus", "corpus", "corpus-2", "corpus-3", "corpus-4" };

	if (argc != 3) {
		cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
		return 1;
	}



	p = maximum(atoi(argv[1]), atoi(argv[2]), l);
	cout << p.first << " " << p.second << endl;

	l = { "corpus", "corpus", "corpus", "corpus-3", "corpus-4" };

	if (argc != 3) {
		cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
		return 1;
	}



	p = maximum(atoi(argv[1]), atoi(argv[2]), l);
	cout << p.first << " " << p.second << endl;






	return 0;
}
