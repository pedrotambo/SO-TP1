#include "ConcurrentHashMap.hpp"
#include <chrono>

#define now std::chrono::high_resolution_clock::now

using namespace std;

int main(int argc, char** argv){

    if (argc < 3){
        cout << endl << "Error en los parametros de entrada. Los parametros correctos son:" << endl;
        cout << endl << "./interza <función> <parámetros>" << endl;
        cout << "Funciones a utilizar:" << endl;
        cout << "count_words_nc -> Verisón no concurrente, toma un archivo." << endl;
        cout << "count_words_c -> Versión concurrente: un thread por archivo." << endl;
        cout << "count_words_ct -> Versión concurrente: no pueden haber threads sin trabajar." << endl;
        cout << "maximum -> Versión concurrente." << endl;
        cout << "maximum_cw_c -> Versión concurrente con count_words_c." << endl;
        cout << "maximum_cw_ct -> Versión concurrente con count_words_ct." << endl;
        cout << endl << "Los parámetro serán los de la función elegida." << endl;
        return -1;
    }



    //inicializo las variables para medir el tiempo
    chrono::high_resolution_clock::time_point t1;
    chrono::high_resolution_clock::time_point t2;
    chrono::duration<double> time_span;

    string funcion = argv[1];
    
    if(funcion == "count_words_nc"){

        string arch = argv[2];
        t1 = now();
        count_words(arch);
        t2 = now();

    } else if(funcion == "count_words_c"){

        list<string> archs;
        for (int i = 2; i < argc; ++i){
            archs.push_back(argv[i]);
        }
        t1 = now();
        count_words(archs);
        t2 = now();

    } else if(funcion == "count_words_ct"){

        int n = atoi(argv[2]);
        list<string> archs;
        for (int i = 3; i < argc; ++i){
            archs.push_back(argv[i]);
        }
        t1 = now();
        count_words(n, archs);
        t2 = now();

    } else if(funcion == "maximum"){
        int p_archivos = atoi(argv[2]);
        int p_maximos = atoi(argv[3]);
        list<string> archs;
        for (int i = 4; i < argc; ++i){
            archs.push_back(argv[i]);
        }
        t1 = now();
        maximum(p_archivos, p_maximos, archs);
        t2 = now();

    } else if(funcion == "maximum_cw_c"){

        int p_archivos = atoi(argv[2]);
        int p_maximos = atoi(argv[3]);
        list<string> archs;
        for (int i = 4; i < argc; ++i){
            archs.push_back(argv[i]);
        }
        t1 = now();
        maximum2(p_archivos, p_maximos, archs);
        t2 = now();

    } else if(funcion == "maximum_cw_ct"){

        int p_archivos = atoi(argv[2]);
        int p_maximos = atoi(argv[3]);
        list<string> archs;
        for (int i = 4; i < argc; ++i){
            archs.push_back(argv[i]);
        }
        t1 = now();
        maximum3(p_archivos, p_maximos, archs);
        t2 = now();

    }


    time_span = std::chrono::duration_cast<std::chrono::duration<double> >(t2-t1);
            
    cout << time_span.count() << endl;

    return 0;
}