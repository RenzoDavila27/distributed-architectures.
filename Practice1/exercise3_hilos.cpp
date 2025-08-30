#include <iostream>
#include <vector>
#include <sys/time.h>
using namespace std;

vector<vector<float>> resultado;

vector<vector<float>> crearMatriz(int n, float x) {
    vector<vector<float>> matriz(n, vector<float>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = x;
        }
    }
    return matriz;
}

void multiplicar_Matrices(vector<vector<float>> m1, vector<vector<float>> m2, int n1, int n2, int n) {

    for (int i = n1; i < n2; i++) {
        for (int j = 0; j < n; j++) {
            for (int x = 0; x < n; x++) {
                resultado[i][j] += m1[i][x] * m2[x][j];
            }
        }
    }
}

float sumatoria_elementos_matriz(vector<vector<float>> matriz, int n) {
    float sumatoria = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sumatoria += matriz[i][j];
        }
    }
    return sumatoria;
}

void imprimir_matriz(vector<vector<float>> matriz, int n) {
    cout << "|" << matriz[0][0] << "......" << matriz[0][n-1] << "|" << endl;
    cout << "|........................|" << endl;
    cout << "|" << matriz[n-1][0] << "......" << matriz[n-1][n-1] << "|" << endl;
}

int main() {
    int n;
    float x1, x2;

    cout << "Ingrese el tamaño que tendran ambas matrices (n): ";
    cin >> n;
    cout << "Ingrese el valor para llenar la matriz 1: ";
    cin >> x1;
    cout << "Ingrese el valor para llenar la matriz 2: ";
    cin >> x2;
    cout << "Ingrese el numero de hilos: ";
    cin >> thr;

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    resultado(n, vector<float>(n, 0.0f));

    vector<vector<float>> matriz1 = crearMatriz(n, x1);
    vector<vector<float>> matriz2 = crearMatriz(n, x2);

    vector<thread> thread_array;
    if (thr > n){
        thr = n;
    }
    vector <int> filasxHilo(n, 0.0f);
    int filasRestantes = n, i = 0;
    bool repartidos = false;
    while repartidos == false{
        filasxHilo[i] += 1;
        filasRestantes -= 1;
        i++;
        if (filasRestantes == 0){
            repartidos = true;
        } else if (i == n){
            i = 0;
        }
    }

    int a = 0, b;
    for(int i=0;i<thr;i++){
        b = a + filasxHilo[i];
        thread_array.emplace_back(thread(multiplicar_Matrices, matriz1, matriz2, a, b, n));
        
        a = b;
    }

    imprimir_matriz(resultado, n);

    float suma = sumatoria_elementos_matriz(resultado, n);
    cout << "La sumatoria de los elementos de la matriz resultante es: " << suma << endl;

    gettimeofday(&time2, NULL);  // fin
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;

    return 0;