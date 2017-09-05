#include "ConcurrentHashMap.hpp"

using namespace std;


void ConcurrentHashMap::print_tabla(){
	cout << "{";
	for (size_t i = 0; i < 26; i++) {
		auto a = tabla[i]->CrearIt();
		bool hay = false;
		for (auto it = tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			cout << " < " <<it.Siguiente().first  <<  " , "<< it.Siguiente().second <<" > " ;
		}
		if (hay) cout << "]";
	}
	cout << "}"<< endl;
}



/***************** Constructor *****************/
ConcurrentHashMap::ConcurrentHashMap(){
	/* Inizializamos la tabla y los mutex */
	for (size_t i = 0; i < 26; i++) {
		tabla[i] = new Lista<Elem>();
		pthread_mutex_init(&(_locks[i]), NULL);
	}
}

/**********Constructor por copia *************/
ConcurrentHashMap::ConcurrentHashMap (const ConcurrentHashMap& other){
	for (size_t i = 0; i < 26; i++) {
		delete tabla[i];
		tabla[i] = new Lista<Elem>();
		for (auto it = other.tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			tabla[i]->push_front(make_pair(it.Siguiente().first,it.Siguiente().second));
		}
	}
}

/***********************************************/
ConcurrentHashMap& ConcurrentHashMap::operator= (const ConcurrentHashMap& other){
	for (size_t i = 0; i < 26; i++) {
		delete tabla[i];
		tabla[i] = new Lista<Elem>();
		for (auto it = other.tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			tabla[i]->push_front(make_pair(it.Siguiente().first,it.Siguiente().second));
		}
	}
	return *this;
}


/*************** Destructor ********************/
ConcurrentHashMap::~ConcurrentHashMap(){
	for (size_t i = 0; i < 26; i++) {
		delete tabla[i];
		pthread_mutex_destroy(&_locks[i]);
	}
}
/****************** addAndInc *******************/
void ConcurrentHashMap::addAndInc(string key){
	int h = hash(key);
	/* Agregarmos la clave a la lista si no esta */
	while (!member(key)){
		pthread_mutex_lock(& _locks[h]);
		if(!member(key)) {
			tabla[h]->push_front(make_pair(key,0));
		}
		pthread_mutex_unlock(& _locks[h]);
	}
	/* Incrementamos su valor */
	for (auto it = tabla[h]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().first == key) {
			pthread_mutex_lock(& _locks[h]);
			it.Siguiente().second++;
			pthread_mutex_unlock(& _locks[h]);
			break;
		}
	}
}
/****************** memeber **********************/
bool ConcurrentHashMap::member(string key){
	for (auto it = tabla[hash(key)]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
		if (it.Siguiente().first == key) return true;
	}
	return false;
}
/**************************************************/
/*************************************************/
//static void* ConcurrentHashMap::maxThrWrapper(void * args)
void* ConcurrentHashMap::maxThrWrapper(void * args){
	infoThread * info = (infoThread *) args ;
	return info->context->maxThr(info);
}

void * ConcurrentHashMap::maxThr(void * args){
	infoThread* inf = (infoThread*) args;
	int next;
	while(next = atomic_fetch_add(inf->siguiente,1), next  < 26 ){
		/* Vamos a la proxima entrada de la tabla para recorrer. */
		for (auto it = tabla[next]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			Elem* m;
			do {
				m =  (* (inf->max)).load();
				if( m == NULL || it.Siguiente().second > m->second ){
					atomic_compare_exchange_weak(inf->max, &m , &it.Siguiente());
				 }
			} while( it.Siguiente().second > ((*inf->max).load())->second );
		}
	}
	/* Si no quedan mas entradas de la tabla para reccorer terminamos. */
	return NULL;
}

/************************************************/
pair<string,unsigned int> ConcurrentHashMap::maximum(unsigned int nt){
	atomic<int> siguiente(0);
	atomic<Elem *> maximo(nullptr);
	pthread_t threads[nt]; int tid;
	infoThread vars[nt];
	/* Pedimos los mutex de cada entrada de la tabla */
	for (size_t i = 0; i < 26; i++) pthread_mutex_lock(& _locks[i]);
	/* Inizializamos los threads */
	for (size_t tid = 0; tid < nt; tid++) {
		vars[tid].siguiente = &siguiente;
		vars[tid].max = &maximo;
		vars[tid].context = this;
		pthread_create(&threads[tid],NULL,&ConcurrentHashMap::maxThrWrapper,& (vars[tid]) );
	}
	/* Joineamos los threads */
	for (size_t tid = 0; tid < nt; tid++) pthread_join(threads[tid],NULL);
	pair<string,unsigned int> res = make_pair(maximo.load()->first,maximo.load()->second);
	/* Desbloqueamos los mutex de cada entrada de la tabla */
	for (size_t i = 0; i < 26; i++) pthread_mutex_unlock(& _locks[i]);
	return res;
}

/************* Fin class functions********************/


/*****************************************************/
ConcurrentHashMap count_words(string archivo){

	string word;
	ifstream file(archivo);
	ConcurrentHashMap h;
	if (file) {
	 while (getline(file,word)) {
		 h.addAndInc(word);
	 }
	 file.close();
 }
 return h;
}

void * count_words_threads(void * args){

	pair<string*,ConcurrentHashMap*> input = *((pair<string*,ConcurrentHashMap*> *) args);
	ConcurrentHashMap *h = input.second;
	string inputFile = *(input.first);
	ifstream file(inputFile);

	string word;
	if (file) {
		while(getline(file,word)){
			(*h).addAndInc(word);
		}
	}
	file.close();

	return NULL;
}
/********************************************************/




/********************************************************/
ConcurrentHashMap count_words(list<string>archs){
  	ConcurrentHashMap h;

  pthread_t threads[archs.size()];
  pair<string*,ConcurrentHashMap*> vars[archs.size()];

  int tid = 0;
  // List no es accesible con [], por eso el iterador.
  for (auto it = archs.begin(); it != archs.end(); it++){
  	vars[tid].first = &(*it);
  	vars[tid].second = &h;
  	pthread_create(&threads[tid],NULL, count_words_threads, & vars[tid]); //
  	tid++;
  }


  for (tid = 0; tid < archs.size(); tid++) {
    pthread_join(threads[tid],NULL);
  }

  return h;

}

void * count_words_nthreads(void * args){

	infoFile inf = *(infoFile*) args;

	int next;
	int last = inf.words->size();

	ConcurrentHashMap *h = inf.context;

	while(next = atomic_fetch_add(inf.siguiente,1), next < last){
    	string archivo = (*inf.words)[next];
    	ifstream file(archivo);
		string word;
		if (file) {
			while(getline(file,word)){
				(*h).addAndInc(word);
			}
		}
		file.close();
	}

	return NULL;
}

ConcurrentHashMap count_words(unsigned int n, list<string>archs){

  ConcurrentHashMap h;

  pthread_t threads[n];
  int tid;
  infoFile vars[n];

  vector<string> words;
  for (auto it = archs.begin(); it != archs.end(); it++){
  	string s = *it;
  	words.push_back(s);
  }
  atomic<int> siguiente(0);


  for(tid = 0; tid < n; tid++){
  	vars[tid].siguiente = &siguiente;
  	vars[tid].words = &words;
  	vars[tid].context = &h;
  	pthread_create(&threads[tid], NULL, count_words_nthreads, & (vars[tid]));
  }

  for(tid = 0; tid < n; tid++){
  	pthread_join(threads[tid], NULL);
  }

  return h;

}
/***************************************************************************/


void * count_words_nthreads_2(void * args){

	infoFileVector inf = *(infoFileVector*) args;

	int next;
	int last = inf.words->size();

	vector<ConcurrentHashMap> *h = inf.hashMaps;

	while(next = atomic_fetch_add(inf.siguiente,1), next < last){
    	string archivo = (*inf.words)[next];
    	ifstream file(archivo);
		string word;
		if (file) {
			while(getline(file,word)){
				(*h)[next].addAndInc(word);
			}
		}
		file.close();
	}

	return NULL;
}


void * count_row(void * args){
	infoFileFind inf = *(infoFileFind*) args;

	int next;
	vector<ConcurrentHashMap> *h = inf.hashMaps;
	ConcurrentHashMap *hGral = inf.hashMapGral;

	while(next = atomic_fetch_add(inf.row, 1), next < 26){
		int i;
		for (i = 0; i < h->size(); i++){
			auto it = (*h)[i].tabla[next]->CrearIt();
			for(auto it = (*h)[i].tabla[next]->CrearIt(); it.HaySiguiente(); it.Avanzar()){
				string key = it.Siguiente().first;
				int j;
				for (j = 0; j < it.Siguiente().second; j++) (*hGral).addAndInc(key);
			}
		}
	}

	return NULL;
}


pair<string, unsigned int>maximum(unsigned int p_archivos,unsigned int p_maximos, list<string>archs){



	int n = archs.size();
	vector<ConcurrentHashMap> hashMaps(n);

	pthread_t threads[p_archivos];
	int tid;
	infoFileVector vars[p_archivos];



	vector<string> words;
	for (auto it = archs.begin(); it != archs.end(); it++){
		string s = *it;
		words.push_back(s);
	}
	atomic<int> siguiente(0);



	for(tid = 0; tid < p_archivos ; tid++){
		vars[tid].siguiente = &siguiente;
		vars[tid].words = &words;
		vars[tid].hashMaps = &hashMaps;
		pthread_create(&threads[tid], NULL, count_words_nthreads_2, & (vars[tid]));
	}

	for(tid = 0; tid < p_archivos; tid++){
		pthread_join(threads[tid], NULL);
	}

	p_maximos = (p_maximos > 26)? 26 : p_maximos;
	pthread_t threads_find[p_maximos];
	infoFileFind vars2[p_maximos];
	atomic<int> row(0);
	ConcurrentHashMap hashMapGral;

	for(tid = 0; tid < p_maximos; tid++){
		vars2[tid].row =&row;
		vars2[tid].hashMaps = &hashMaps;
		vars2[tid].hashMapGral = &hashMapGral;
		pthread_create(&threads_find[tid], NULL, count_row, & (vars2[tid]));
	}

	for(tid = 0; tid < p_maximos; tid++){
		pthread_join(threads_find[tid], NULL);
	}

	pair<string, unsigned int> max = hashMapGral.maximum(p_maximos);

	return max;

}


pair<string, unsigned int>maximum2(unsigned int p_archivos,unsigned int p_maximos, list<string>archs){
	ConcurrentHashMap h = count_words(archs);
	pair<string, unsigned int> max = h.maximum(p_maximos);
	return max;	
}


pair<string, unsigned int>maximum3(unsigned int p_archivos,unsigned int p_maximos, list<string>archs){
	ConcurrentHashMap h = count_words(p_archivos, archs);
	pair<string, unsigned int> max = h.maximum(p_maximos);
	return max;	
}


