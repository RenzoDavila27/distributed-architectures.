#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sys/time.h>

using namespace std;

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

int main() {
    long long int N;
    while (true) {
        cout << "Ingrese un valor para N (>10⁷): ";
        cin >> N;
        if (N >= 10000000) break;
    }

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    vector<long long int> primos;
    for (long long int i = 2; i < N; ++i) {
        if (esPrimo(i)) {
            primos.push_back(i);
        }
    }
    size_t cantidad = primos.size();
    cout << "Cantidad de números primos menores que " << N << ": " << cantidad << endl;
    cout << "Los 10 mayores números primos menores que " << N << ":\n";
    for (size_t i = (cantidad >= 10 ? cantidad - 10 : 0); i < cantidad; ++i) {
        cout << primos[i] << " ";
    }
    cout << endl;
    
    gettimeofday(&time2, NULL);  // fin
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
    return 0;
}