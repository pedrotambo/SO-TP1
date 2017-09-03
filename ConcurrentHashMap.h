#ifndef CONCURRENT_HASH_MAP_H__
#define CONCURRENT_HASH_MAP_H__


#include <atomic>
#include "ListaAtomica.hpp"
#include "pthread.h"

using namespace std;


class ConcurrentHashMap {

private:

	struct Elem{
		Elem(string key){
			_key = string(key);
			std::atomic<int> _val(0);
		}
		string _key;
		std::atomic<int> _val;
	};

	struct Bucket{
		Lista<Elem * > _list;
		pthread_mutex_t _lock;
	};


	Bucket _tabla[26];

	int hash(string s){
		return s[0]%26;
	}




public:


	ConcurrentHashMap(){}

	void addAndInc(string key){

		int h = hash(key);
		/* Agregarmos la clave a la lista si no esta */
		while (!member(key)){

			pthread_mutex_lock(& _tabla[h]._lock);
			if(!member(key)) {
				//Elem* e = new Elem(key);
				_tabla[h]._list.push_front(Elem(key));
			}
			pthread_mutex_unlock(& _tabla[h]._lock);
		}

		/* Incrementamos su valor */
		Lista<Elem>::Iterador it = _tabla[h]._list.CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente()._key == key) {
				it.Siguiente()._val++;
				break;
			}
			it.Avanzar();
		}

	}

	bool member(string key){
		Lista<Elem>::Iterador it = _tabla[hash(key)]._list.CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente()._key == key) return true;
			it.Avanzar();
		}
		return false;
	}

	pair<string, unsigned int> maximum(unsigned int nt){

	}

};

#endif /* LISTA_ATOMICA_H__ */
