#include <iostream>
#include <vector>
#include <unordered_map>

struct Vertice {
    std::string nombre;  // Nombre del establecimiento
    double latitud;      // Latitud de la ubicación
    double longitud;     // Longitud de la ubicación
};

class Graph {
    
private:
    std::unordered_map<std::string, std::unordered_map<std::string, double>> nodes;
    std::vector<Vertice> locales; //locales con coordenadas en el vector
    std::vector<std::string> initial_tour ;

public:

    void agregarLocal(const Vertice& v);
    void cargar(const std::vector<Vertice>& vertices);
    double calcularDistancia(Vertice& origen, Vertice& destino);
    void generarAristas();
    void imprimirAdyacencia() const;

    double calculate_tour_distance(const std::vector<std::string>& tour);
    std::vector<std::string> two_opt_swap(const std::vector<std::string>& tour, int i, int j);
    std::vector<std::string> two_opt();
    std::pair<std::unordered_map<std::string, std::string>, std::unordered_map<std::string, double>> dijkstra(std::string inicio);

};
