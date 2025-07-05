#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <string> // CAMBIO: Añadir include para std::string

struct PersonaCola {
    int id;
    std::string nombre; // CAMBIO: de char nombre[50] a std::string
    int prioridad;
    std::string tipo;   // CAMBIO: de char tipo[20] a std::string
};

class ColaPrioridadMaxima {
private:
    PersonaCola* arreglo;
    int capacidad;
    int cantidad;

    void subir(int indice);
    void bajar(int indice);
    int buscarIndice(int id);
    // CAMBIO: ya no se necesita copiarCadena

public:
    ColaPrioridadMaxima(int cap = 50000); // CAMBIO: Aumentar capacidad por defecto
    ~ColaPrioridadMaxima();
    bool insertar(const PersonaCola& persona);
    bool extraerMax(PersonaCola& persona);
    bool actualizarPrioridad(int id, int nuevaPrioridad);
    void mostrarSiguientes(int n = 5);
    int obtenerCantidad() const;
};

#endif // MAXHEAP_H