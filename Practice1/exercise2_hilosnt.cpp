#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/time.h>

void busqueda_sin_hilos(std::string texto, std::vector<std::string> patrones){

    int contadorOcurrencias;
    int contadorPatrones = -1;
    size_t pos;
    

    for (const auto& patron : patrones) { 

        contadorPatrones++;
        contadorOcurrencias = 0;
        pos = 0;

        while ((pos = texto.find(patron, pos)) != std::string::npos) {
            contadorOcurrencias++;
            pos += patron.length();
        }
        std::cout << "El patron " << contadorPatrones << " (" << patron << ") "<< " aparece " << contadorOcurrencias << " veces." << std::endl;
    }

}

int main() {


    std::ifstream texto("texto.txt");
    std::string linea;

    timeval time1, time2;
    gettimeofday(&time1, NULL);

    
    if (!texto.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo." << std::endl;
        return 1;
    }
    
    std::getline(texto, linea);
    
    texto.close();

    std::ifstream patrones("patrones.txt");
    std::vector<std::string> patrones_extraidos;
    std::string patron;

    while (std::getline(patrones, patron)) {
        patrones_extraidos.push_back(patron);
    }
    
    patrones.close();

    busqueda_sin_hilos(linea, patrones_extraidos);

    gettimeofday(&time2, NULL);
    double tiempo = (time2.tv_sec - time1.tv_sec) + 
                    (time2.tv_usec - time1.tv_usec) / 1000000.0;
    std::cout << "Tiempo de ejecución: " << tiempo << " segundos" << std::endl;

    return 0;
    
}