#include <atomic>
#include <ListaAtomica.h>
#include "pthread.h"

using namespace std;

template <typename T>
class ConcurrentHashMap {

private:

	struct Elem{
		Elem(string key): _val(key),val(0) {}
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


	ConcurrentHashMap(){}

	void addAndInc(string key){

		int h = hash(key);
		/* Agregarmos la clave a la lista si no esta */
		while (!member(key)){

			pthread_mutex_lock(& _tabla[h]._lock);
			if(!member(key)) _tabla[h]._list.push_front(Elem(string,0));
			pthread_mutex_unlock(& _tabla[h]._lock);
		}

		/* Incrementamos su valor */
		Lista<Elem>::Iterador it = _tabla[h].CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente()._key == key) {
				it.Siguiente()._val++;
				break;
			}
			it.Avanzar();
		}

	}

	bool member(string key){
		Lista<Elem>::Iterador it = _tabla[hash(key)].CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente()._key == key) return true;
			it.Avanzar();
		}
		return false;
	}

	pair<string, unsigned int> maximum(unsigned int nt){

	}

}
