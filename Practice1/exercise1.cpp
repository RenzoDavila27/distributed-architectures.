#include <iostream>   // Librería estándar para entrada y salida
#include <vector>     // Ejemplo: estructuras de datos
#include <string>     // Manejo de cadena
#include <thread>
#include <fstream>
#include <math.h>
#include <iomanip>

// Usar std sin tener que escribir std:: cada vez
using namespace std;

// ----------------------------
// Declaración de funciones
// ----------------------------
long double logaritmo_sin_hilos(long double a);

// ----------------------------
// Función principal
int main() {

    ios::sync_with_stdio(false); // Optimiza entrada/salida
    long double operando;
    int num_hilos;
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

// ----------------------------
// Definición de funciones
// ----------------------------

long double logaritmo_sin_hilos(long double a) {

    long double resultado=0;
    long double x = (a - 1) / (a + 1);

    for (int i = 0; i < 10000000; i++) {
        resultado += (1.0/(2.0*i+1.0))*(pow(x,2*i+1));
    }

    return 2*resultado;
}

