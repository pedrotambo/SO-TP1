#include "ConcurrentHashMap.h"
using namespace std;


ConcurrentHashMap::ConcurrentHashMap(){

}


void ConcurrentHashMap::addAndInc(string key){

	int h = hash(key);
	/* Agregarmos la clave a la lista si no esta */
	while (!member(key)){

		pthread_mutex_lock(& _tabla[h]._lock);
		if(!member(key)) _tabla[h]._list.push_front(Elem(key));
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


bool ConcurrentHashMap::member(string key){
	Lista<Elem>::Iterador it = _tabla[hash(key)]._list.CrearIt();
	while(it.HaySiguiente()){
		if (it.Siguiente()._key == key) return true;
		it.Avanzar();
	}
	return false;
}
