#include <iostream>
#include "ConcurrentHashMap.hpp"
#include <unistd.h>
using namespace std;



void *add(void* h){

  ConcurrentHashMap* ch = (ConcurrentHashMap*) h ;
  usleep(rand() % 10000);
  ch->addAndInc("gola");
  return NULL;

}

void *add1(void* h){

  ConcurrentHashMap* ch = (ConcurrentHashMap*) h ;
  //cout << ch->member("hola2");
  usleep(rand() % 10000);
  ch->addAndInc("hola");
  return NULL;

}
void *add2(void* h){

  ConcurrentHashMap* ch = (ConcurrentHashMap*) h ;
  //cout << ch->member("hola3");
  usleep(rand() % 10000);
  ch->addAndInc("lola");
  return NULL;

}
void *add3(void* h){

  ConcurrentHashMap* ch = (ConcurrentHashMap*) h ;
  //c//out << ch->member("hola4");
  usleep(rand() % 10000);
  ch->addAndInc("coca");

  return NULL;

}




int main(void) {

  ConcurrentHashMap h;
  ConcurrentHashMap h2;

  pthread_t threads[200]; int tid;

  for (tid = 0; tid < 50; tid++) {
    pthread_create(&threads[tid],NULL,add,&h);
    pthread_create(&threads[50+tid],NULL,add1,&h);
    pthread_create(&threads[100+tid],NULL,add2,&h2);
    pthread_create(&threads[150+tid],NULL,add3,&h2);
  }






  h.print_tabla();
  h2.print_tabla();
  pair<string,unsigned int> s = h.maximum(10);
  cout << "<" << s.first << " , " << s.second << ">" << endl;
  pair<string,unsigned int> s2 = h2.maximum(10);
  cout << "<" << s2.first << " , " << s2.second << ">" << endl;

  h.print_tabla();
  h2.print_tabla();
  s = h.maximum(10);
  s2 = h.maximum(10);
  cout << "<" << s.first << " , " << s.second << ">" << endl;
  cout << "<" << s2.first << " , " << s2.second << ">" << endl;

  for (tid = 0; tid < 200; tid++) {
    pthread_join(threads[tid],NULL);
  }
  h.print_tabla();
  h2.print_tabla();
  //s = h.maximum(10);
  //cout << "<" << s.first << " , " << s.second << ">" << endl;

/*
	ConcurrentHashMap h;
	int i;

	h = count_words("corpus");
	for (i = 0; i < 26; i++) {
		for (auto it = h.tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
			cout << t.first << " " << t.second << endl;
		}
	}*/
	return 0;
}
