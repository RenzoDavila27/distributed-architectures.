#include <iostream>   // Librería estándar para entrada y salida
#include <vector>     // Ejemplo: estructuras de datos
#include <string>     // Manejo de cadena
#include <thread>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <thread>
#include <future>
#include <sys/time.h>

// Usar std sin tener que escribir std:: cada vez
using namespace std;

// ----------------------------
// Definición de funciones
// ----------------------------

long double logaritmo_sin_hilos(long double a) {
    
    timeval time1, time2;
    gettimeofday(&time1, NULL);  // inicio
    long double result=0;
    long double x = (a - 1) / (a + 1);

    for (int i = 0; i < 10000000; i++) {
        result += (1.0/(2.0*i+1.0))*(pow(x,2*i+1));
    }
    gettimeofday(&time2, NULL);  // fin
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
    return 2*result;
}

// ----------------------------
// Función principal
int main() {

    ios::sync_with_stdio(false); // Optimiza entrada/salida
    long double operando;
    long int thr;
    long double resultado; 

    cout << "Ingrese el operando: (1500000<)" << endl;
    cin >> operando;
    while(operando<1500000){
        cout << "Ingrese nuevamente el operando (1500000<)" << endl;
        cin >> operando;
    }
    resultado = logaritmo_sin_hilos(operando);
    cout << "El resultado es " << setprecision(15) << resultado << endl;
}  

