#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <string> // Necesario para std::string

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
    // buscarIndice se movió a public para poder usarse fuera si es necesario

public:
    ColaPrioridadMaxima(int cap = 50000); // Aumentar capacidad por defecto
    ~ColaPrioridadMaxima();

    // --- AÑADIMOS LA REGLA DE TRES PARA MANEJO SEGURO DE MEMORIA ---
    ColaPrioridadMaxima(const ColaPrioridadMaxima& otra); // Constructor de copia
    ColaPrioridadMaxima& operator=(const ColaPrioridadMaxima& otra); // Operador de asignación

    bool insertar(const PersonaCola& persona);
    bool extraerMax(PersonaCola& persona);
    bool actualizarPrioridad(int id, int nuevaPrioridad);
    void mostrarSiguientes(int n = 5);
    int obtenerCantidad() const;
    int buscarIndice(int id); // La hacemos pública
};

#endif // MAXHEAP_H