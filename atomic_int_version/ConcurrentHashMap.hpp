#ifndef CONCURRENT_HASH_MAP_H__
#define CONCURRENT_HASH_MAP_H__


#include <atomic>
#include "ListaAtomica.hpp"
#include "pthread.h"
#include <fstream>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

//typedef pair<string,unsigned int> Elem;
struct Elem{
    Elem(){}

    Elem(const Elem& e){
    	first = e.first;
        int k = e.second;
        second.store(k);
    }
    Elem& operator =(const Elem& e)
	{
    	first = e.first;
    	int k = e.second;
    	second.store(k);
    	return *this;
	}

    string first;
    atomic_int second;
};

class ConcurrentHashMap {

private:

	/* Info que le pasamos a un thread para calcular el maximo */
	struct infoThread {
		infoThread(): siguiente(nullptr),max(nullptr),context(nullptr) {}
		atomic<int>* siguiente;
		atomic<Elem* > * max;
		ConcurrentHashMap* context;
	};

	pthread_mutex_t _locks[26];

	int hash(string s){
		return s[0] % 97;
	}

public:

	/* Lo hacemos publico por que en los test acceden */
	//Lista<pair<string,unsigned int> >* tabla[26];
	Lista<Elem >* tabla[26];


	void print_tabla();



	/***************** Constructor *****************/
	ConcurrentHashMap();
	/**********Constructor por copia *************/

	ConcurrentHashMap (const ConcurrentHashMap& other);

	/***********************************************/
	ConcurrentHashMap& operator= (const ConcurrentHashMap& other);

	/*************** Destructor ********************/
	~ConcurrentHashMap();

 /****************** addAndInc *******************/
	void addAndInc(string key);

	/****************** memeber **********************/
	bool member(string key);
	/**************************************************/


	/*************************************************/
	static void* maxThrWrapper(void * args);

	void * maxThr(void * args);
	/************************************************/

	pair<string,unsigned int> maximum(unsigned int nt);

};

ConcurrentHashMap count_words(string archivo);

void * count_words_threads(void * args);

ConcurrentHashMap count_words(list<string>archs);


struct infoFile {
	infoFile(): siguiente(nullptr), words(nullptr),context(nullptr) {}
	atomic<int>* siguiente;
	vector<string> *words;
	ConcurrentHashMap* context;
};

void * count_words_nthreads(void * args);

ConcurrentHashMap count_words(unsigned int n, list<string>archs);

struct infoFileVector {
	infoFileVector(): siguiente(nullptr), words(nullptr),hashMaps(nullptr) {}
	atomic<int>* siguiente;
	vector<string> *words;
	vector<ConcurrentHashMap>* hashMaps;
};

void * count_words_nthreads_2(void * args);

struct infoFileFind {
	infoFileFind(): row(nullptr), hashMaps(nullptr), hashMapGral(nullptr) {}
	atomic<int>* row;
	vector<ConcurrentHashMap>* hashMaps;
	ConcurrentHashMap* hashMapGral;
};

void * count_row(void * args);

pair<string, unsigned int>maximum(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);

pair<string, unsigned int>maximum2(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);

pair<string, unsigned int>maximum3(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);



#endif /* LISTA_ATOMICA_H__ */
