#ifndef CONCURRENTHASHMAP_H__
#define CONCURRENTHASHMAP_H__


#include <atomic>
#include "ListaAtomica.hpp"
#include "pthread.h"
#include <string>

using namespace std;

class ConcurrentHashMap {

private:

	struct Elem{
		Elem(string key): _key(key),_val(0) {}
		string _key;
		std::atomic<int> _val;
	};

	struct Bucket{
		Lista<Elem> _list;
		pthread_mutex_t _lock;
	};


	Bucket _tabla[26];

	int hash(string s){
		return s[0]%26;
	}




public:


	ConcurrentHashMap();
	void addAndInc(string key);
	bool member(string key);
	//pair<string, unsigned int> maximum(unsigned int nt);

};

#endif
