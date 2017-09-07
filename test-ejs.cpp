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

  cout << "--------------- Chequeando que anden las funciones de ConcurrentHashMap-----------" << endl;
  ConcurrentHashMap h;
  ConcurrentHashMap h2;

  pthread_t threads[200]; int tid;
  // Creamos 200 threads, 100 insertaran valores en h y 100 en h2
  for (tid = 0; tid < 50; tid++) {
    pthread_create(&threads[tid],NULL,add,&h);
    pthread_create(&threads[50+tid],NULL,add1,&h);
    pthread_create(&threads[100+tid],NULL,add2,&h2);
    pthread_create(&threads[150+tid],NULL,add3,&h2);
  }

  for (tid = 0; tid < 200; tid++) {
    pthread_join(threads[tid],NULL);
  }
  // En h veremos que hay 50 gola's y 50 hola's y en h2  y ordenados alfabeticamente
  h.print_tabla();
  h2.print_tabla();

  cout << "gola y hola estan en h: " << h.member("gola") << ", " << h.member("hola") << endl;
  cout << "coca y lola estan en h2: " << h2.member("coca") << ", " << h2.member("lola") << endl;

  h.addAndInc("gola");
  h2.addAndInc("coca");

  cout << h.maximum(4).first << " " << h.maximum(4).second << endl;
  cout << h2.maximum(3).first << " " << h2.maximum(2).second << endl;


  cout << "--------------- Creando nueva tabla para testear count_words no concurrente-----------" << endl;

  ConcurrentHashMap h_nc = count_words("file1");
  ConcurrentHashMap h_nc2 = count_words("file2");
  h_nc.print_tabla();
  h_nc2.print_tabla();

  cout << "--------------- Creando nueva tabla para testear Count_words(list<string>)-----------" << endl;

  ConcurrentHashMap palabras;

  list<string> l;
  l.push_back("file1");
  l.push_back("file2");
  l.push_back("file3");
  l.push_back("file4");

  palabras = count_words(l);
  int i;
  for (i = 0; i < 26; i++) {
    for (auto it = palabras.tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
      auto t = it.Siguiente();
      cout << t.first << " " << t.second << endl;
    }
  }
  pair<string,unsigned int> max = palabras.maximum(26);
  cout << "<" << max.first << " , " << max.second << ">" << endl;

  cout << "-----------------Creando nueva tabla para testear Count_words(n, list<string>)-----------" << endl;

  ConcurrentHashMap words;
  list<string> l2;
  l2.push_back("file1");
  l2.push_back("file2");
  l2.push_back("file3");
  l2.push_back("file4");

  unsigned int k = 2;
  words = count_words(k,l2);
  for (i = 0; i < 26; i++) {
    for (auto it = words.tabla[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
      auto t = it.Siguiente();
      cout << t.first << " " << t.second << endl;
    }
  }

  cout << "--- Reutilizamos tabla anterior para chequear la función maximum(p_archivos, p_maximos, list_archs)-----" << endl;


  pair<string , unsigned int > m = maximum(2,2,l2);
  cout << "<" << m.first << " " << m.second << ">" << endl;

  ConcurrentHashMap h_basic = count_words(l2);
  pair<string, unsigned int > m_basic = h_basic.maximum(3);
  cout << "<" << m_basic.first << " " << m_basic.second << ">" << endl;
  
  pair<string, unsigned int > m_basic2 = maximum2(3,3,l2);
  pair<string, unsigned int > m_basic3 = maximum3(4,4,l2);

  cout << "<" << m_basic2.first << " " << m_basic2.second << ">" << endl;
  cout << "<" << m_basic3.first << " " << m_basic3.second << ">" << endl;


	return 0;
}
