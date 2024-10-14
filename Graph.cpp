#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cmath>
#include <chrono> 
#include "Graph.h"
#include <thread>
#include <queue>


void Graph::agregarLocal(const Vertice& v){
    locales.push_back(v);
    initial_tour.push_back(v.nombre);
}
void Graph::cargar(const std::vector<Vertice>& vertices){
        for (const auto& v : vertices) {
        agregarLocal(v);
    }
    generarAristas();


}

double Graph::calcularDistancia(Vertice& origen, Vertice& destino){

    double lat1_rad = origen.latitud * M_PI / 180.0;
    double lon1_rad = origen.longitud * M_PI / 180.0;
    double lat2_rad = destino.latitud * M_PI / 180.0;
    double lon2_rad = destino.longitud* M_PI / 180.0;

    double lat = lat2_rad - lat1_rad;
    double lon = lon2_rad - lon1_rad;


    double a = std::sin(lat / 2) * std::sin(lat / 2) +
               std::cos(lat1_rad) * std::cos(lat2_rad) *
               std::sin(lon / 2) * std::sin(lon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));


    double distancia = 6371.0 * c;

    return distancia;


}

void Graph::generarAristas() {
    for (int i = 0; i<locales.size();i++) {
        std::unordered_map<std::string, float> aristas; 
        for (int j = i+1; j<locales.size();j++) {

            double distancia = calcularDistancia(locales[j],locales[i]);
            nodes[locales[i].nombre][locales[j].nombre] = distancia;
            nodes[locales[j].nombre][locales[i].nombre] = distancia;
        }

    }
}





void Graph::imprimirAdyacencia() const{
    for (const auto& pair : nodes) {
        std::cout << "Nodo: " << pair.first << " -> Adyacentes: ";

        for (const auto& vecino : pair.second) {
            std::cout<<vecino.first << " "<<vecino.second<<" km ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

    }
}




double Graph::calculate_tour_distance(const std::vector<std::string>& tour){
    double total_distance = 0;
    for (size_t i = 0; i < tour.size()-1; ++i) {
        total_distance += nodes[tour[i]][tour[i + 1]];
    }
    return total_distance;
}


std::vector<std::string> Graph::two_opt_swap(const std::vector<std::string>& tour, int i, int j) {

    std::vector<std::string> new_tour = tour;
    std::reverse(new_tour.begin() + i, new_tour.begin() + j + 1);
    return new_tour;
}




std::vector<std::string> Graph::two_opt() {

    
    std::vector<std::string> best_tour = initial_tour;
    bool improved = true;
    
    float best_distance = calculate_tour_distance(best_tour);

    while (improved) {

        improved = false;
        
        for (size_t i = 0; i < best_tour.size() - 1; ++i) {
            for (size_t j = i + 1; j < best_tour.size(); ++j) {
              
                std::vector<std::string> new_tour = two_opt_swap(best_tour, i, j);
                float new_distance = calculate_tour_distance(new_tour);

                if (new_distance < best_distance) {
                    best_tour = new_tour;
                    best_distance = new_distance;
                    improved = true;
                    break;  
                }
            }
            if (improved) {
                break;
            }
        }
    }
    

        int count = 0;
        std::cout << "Mejor tour Norte: ";
    for (const auto& node : best_tour) {
        
        if(count==locales.size()/2){
            std::cout<<std::endl;
            std::cout<<"Mejor Tour Sur: ";
        }
            std::cout << node << " ";
      
        count++;
    }
    std::cout << std::endl;
    std::cout <<"distancia total:"<<best_distance<< std::endl;


    return best_tour;
}



std::pair<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, double>> Graph::dijkstra(std::string inicio) {

    std::unordered_map<std::string, double> distancias;
    std::unordered_map<std::string, std::string> previos;

    for (const auto& local : locales) {
        distancias[local.nombre] = std::numeric_limits<double>::infinity();
        previos[local.nombre] = ""; 
    }

    std::priority_queue<std::pair<double, std::string>, std::vector<std::pair<double, std::string>>, std::greater<std::pair<double, std::string>>> pq;

    distancias[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        std::string u = pq.top().second;
        pq.pop();


        for (const auto& origen : nodes[u]) {
            for (const auto& destino : nodes[u]){
            std::string v = destino.first;
            double peso = destino.second;

            if (distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                previos[v] = u;
                pq.push({distancias[v], v});
            }
        }



            }
            

    }

    return {previos, distancias};
}

