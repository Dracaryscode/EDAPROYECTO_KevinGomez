#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>

struct PersonaCola {
    int id;
    char nombre[50];
    int prioridad;
    char tipo[20];
};

class ColaPrioridadMaxima {
private:
    PersonaCola* arreglo;
    int capacidad;
    int cantidad;

    void subir(int indice);
    void bajar(int indice);
    int buscarIndice(int id);
    void copiarCadena(char* destino, const char* origen, int maxTam);

public:
    ColaPrioridadMaxima(int cap = 1000);
    ~ColaPrioridadMaxima();
    bool insertar(const PersonaCola& persona);
    bool extraerMax(PersonaCola& persona);
    bool actualizarPrioridad(int id, int nuevaPrioridad);
    void mostrarSiguientes(int n = 5);
    int obtenerCantidad() const;
};

#endif // MAXHEAP_H