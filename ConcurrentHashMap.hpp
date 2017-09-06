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

typedef pair<string,unsigned int> Elem;

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
	Lista<pair<string,unsigned int> >* tabla[26];

	/***************** Constructor *****************/
	ConcurrentHashMap();
	
	/**********Constructor por copia ***************/
	ConcurrentHashMap (const ConcurrentHashMap& other);

	/***********************************************/
	ConcurrentHashMap& operator= (const ConcurrentHashMap& other);

	/*************** Destructor ********************/
	~ConcurrentHashMap();

    /****************** addAndInc ******************/
	void addAndInc(string key);

	/****************** memeber ********************/
	bool member(string key);
	

	/***********************************************/
	static void* maxThrWrapper(void * args);

	void * maxThr(void * args);
	
	/****************** maximum ********************/
	pair<string,unsigned int> maximum(unsigned int nt);

	/**************Función para imprimir hashmap ***/
	void print_tabla();
};

/******************************** versión no concurrente ***************************/
ConcurrentHashMap count_words(string archivo);

/****************************Funciones Ej 2.3 **************************************/
void * count_words_threads(void * args);

ConcurrentHashMap count_words(list<string>archs);


/********************* Estructura y funciones para Ej 2.4 ***************************/
struct infoFile {
	infoFile(): siguiente(nullptr), words(nullptr),context(nullptr) {}
	atomic<int>* siguiente;
	vector<string> *words;
	ConcurrentHashMap* context;
};

void * count_words_nthreads(void * args);

ConcurrentHashMap count_words(unsigned int n, list<string>archs);


/********************* Estructuras y funciones para Ej 2.5 ***************************/
struct infoFileVector {
	infoFileVector(): siguiente(nullptr), words(nullptr),hashMaps(nullptr) {}
	atomic<int>* siguiente;
	vector<string> *words;
	vector<ConcurrentHashMap>* hashMaps;
};
struct infoFileFind {
	infoFileFind(): row(nullptr), hashMaps(nullptr), hashMapGral(nullptr) {}
	atomic<int>* row;
	vector<ConcurrentHashMap>* hashMaps;
	ConcurrentHashMap* hashMapGral;
};
void * count_words_nthreads_2(void * args);

void * count_row(void * args);

pair<string, unsigned int>maximum(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);

/*************************************************************************************/

pair<string, unsigned int>maximum2(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);

pair<string, unsigned int>maximum3(unsigned int p_archivos,unsigned int p_maximos, list<string>archs);



#endif /* LISTA_ATOMICA_H__ */
