#include <iostream>
#include "Graph.h"
#include <chrono>
#include <algorithm>


#include <vector>
#include <stack>
#include <unordered_map>
#include <string>




int main() {
  
    Graph graph;
    
    graph.cargar({
    {"D1 Laureles", 6.23457, -75.58132},
    {"D1 Centro", 6.24611, -75.56889},
    {"D1 Castilla", 6.28512, -75.55987},
    {"D1 Robledo", 6.29876, -75.58743},
    {"D1 Buenos Aires", 6.24032, -75.57561},
    {"D1 Manrique", 6.27394, -75.55203},
    {"D1 Aranjuez", 6.25817, -75.56128},
    {"D1 Floresta", 6.23019, -75.57845},
    {"D1 Estadio", 6.24931, -75.57014},
    {"D1 Belén", 6.26708, -75.56435},
    {"D1 Envigado", 6.17123, -75.58291},
    {"D1 Poblado", 6.20528, -75.56719},
    {"D1 Guayabal", 6.21854, -75.59320},
    {"D1 Itagüí", 6.16256, -75.60183},
    {"D1 Sabaneta", 6.14589, -75.61027}});
   
    graph.imprimirAdyacencia();
    

    std::cout << "\nRecorrido 2-opt: "<<std::endl;       
    auto inicio = std::chrono::high_resolution_clock::now();
    graph.two_opt();
    auto fin = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
    std::cout << "Tiempo de 2-opt: " << duracion.count() << " segundos" << std::endl;

    std::pair<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, double>> resultado = graph.dijkstra("D1 Itagüí");
    std::unordered_map<std::string, std::string> previos = resultado.first;
    std::unordered_map<std::string, double> distancias = resultado.second;
    std::cout<<std::endl;

    for(auto&  elemento1 :previos){
        std::cout<<elemento1.first<<" "<<elemento1.second<<std::endl;
    
    }

    return 0;
}

