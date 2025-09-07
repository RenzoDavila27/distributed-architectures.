#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sys/time.h>
#include <thread>

using namespace std;
vector<vector<long long int>> primos;

bool esPrimo(long long int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long long int raiz = sqrt(n);
    for (long long int i = 3; i <= raiz; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void buscarPrimos(long long int start, long long int final, int pos_vector){
    for (long long int i = start; i < final; ++i) {
        if (esPrimo(i)) {
            primos[pos_vector].push_back(i);
        }
    }
}

void calculo_con_hilos(long long int n, int thrs){
    
    vector<thread> thread_array;
    
    long long int c;
    long long int terms = n/thrs;
    long long int b = 0;

    for(int i=0;i<thrs;i++){
        
        vector<long long int> arr;

        c = terms * (i+1);
        primos.push_back(arr);

        thread_array.emplace_back(thread(buscarPrimos,b,c,i));

        b = c+1;
    }

    for(int i = 0; i < thrs; i++){

        if(thread_array[i].joinable()==true){
            thread_array[i].join();
        }

    }
}

int main() {
    long long int N;
    while (true) {
        cout << "Ingrese un valor para N (>10⁷): ";
        cin >> N;
        if (N >= 10000000) break;
    }

    int thrs;
    while (true) {
        cout << "Ingrese un numero de hilos: ";
        cin >> thrs;
        if (thrs > 0) break;
    }

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    calculo_con_hilos(N,thrs);

    vector<long long int> last_numbs;
    long int cantidad = 0;

    for (vector<long long int> vec: primos){
        cantidad += vec.size();
        if (vec == primos[primos.size()-1]){
            last_numbs = vec;
        }
    }
    cout << "Cantidad de números primos menores que " << N << ": " << cantidad << endl;
    cout << "Los 10 mayores números primos menores que " << N << ":\n";
    int size = last_numbs.size();
    int start = (size > 10) ? size-10 : 0;
    for (int i = start;i<size;i++){
        cout << last_numbs[i] << " ";
    }
    cout << endl;
    
    gettimeofday(&time2, NULL);  // fin
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
    return 0;
}