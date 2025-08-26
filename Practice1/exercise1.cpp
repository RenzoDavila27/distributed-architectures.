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

long double global_result;

// ----------------------------
// Declaración de funciones
// ----------------------------
long double logaritmo_sin_hilos(long double a);


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

void operations(long double x, long double start, long double end){

    long double result=0;

    for(long int n = start;n<end;n++){
        result += (1.0/(2.0*n+1.0))*(pow(x,2*n+1));
    }

    global_result += result;

}

void logaritmo_con_hilos(long double a, int thr){

    timeval time1, time2;
    gettimeofday(&time1, NULL);  // inicio
    vector<thread> thread_array;
    long double x = (a - 1) / (a + 1);
    long double result=0;
    

    long double c;
    long double terms = 10000000/thr;
    long double b = 0;

    for(int i=0;i<thr;i++){

        c = terms * (i+1);

        thread_array.emplace_back(thread(operations, x, b, c+1));
        
        b = c+1;
    }

    for(int i = 0; i < thr; i++){
        if(thread_array[i].joinable()==true){
            thread_array[i].join();
        }
    }
    gettimeofday(&time2, NULL);  // fin
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;

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
    cout << "Ingrese el numero de hilos: (numero par!!!)" << endl;
    cin >> thr;
    while(thr<0){
        cout << "Ingrese nuevamente el numero de hilos (numero!!!)" << endl;
        cin >> operando;
    }
    //resultado = logaritmo_sin_hilos(operando);
    logaritmo_con_hilos(operando,thr);
    //cout << "El resultado es " << setprecision(15) << resultado << endl;
    cout << "El resultado es " << setprecision(15) << 2*global_result << endl;
    double tpar = 1.0795;
    double tseq = 3.45942;
    double speedup = tseq/tpar;
}  

