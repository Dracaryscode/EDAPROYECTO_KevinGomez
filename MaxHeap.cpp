#include "MaxHeap.h"
#include <iostream>
#include <utility> // Necesario para std::swap

void ColaPrioridadMaxima::subir(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (arreglo[indice].prioridad > arreglo[padre].prioridad) {
            // std::swap es más eficiente y seguro que usar una variable temporal
            std::swap(arreglo[indice], arreglo[padre]);
            indice = padre;
        } else {
            break;
        }
    }
}

void ColaPrioridadMaxima::bajar(int indice) {
    int izq, der, mayor;
    while (true) {
        izq = 2 * indice + 1;
        der = 2 * indice + 2;
        mayor = indice;
        if (izq < cantidad && arreglo[izq].prioridad > arreglo[mayor].prioridad)
            mayor = izq;
        if (der < cantidad && arreglo[der].prioridad > arreglo[mayor].prioridad)
            mayor = der;
        if (mayor != indice) {
            std::swap(arreglo[indice], arreglo[mayor]);
            indice = mayor;
        } else {
            break;
        }
    }
}

int ColaPrioridadMaxima::buscarIndice(int id) {
    for (int i = 0; i < cantidad; ++i) {
        if (arreglo[i].id == id) return i;
    }
    return -1;
}

ColaPrioridadMaxima::ColaPrioridadMaxima(int cap) {
    capacidad = cap;
    cantidad = 0;
    arreglo = new PersonaCola[capacidad];
}

ColaPrioridadMaxima::~ColaPrioridadMaxima() {
    delete[] arreglo;
}

// --- IMPLEMENTACIÓN DE LA REGLA DE TRES PARA MANEJO SEGURO DE MEMORIA ---

// Constructor de copia
ColaPrioridadMaxima::ColaPrioridadMaxima(const ColaPrioridadMaxima& otra) {
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    arreglo = new PersonaCola[capacidad]; // Creamos nueva memoria
    for (int i = 0; i < cantidad; ++i) {
        arreglo[i] = otra.arreglo[i]; // Copiamos cada elemento
    }
}

// Operador de asignación
ColaPrioridadMaxima& ColaPrioridadMaxima::operator=(const ColaPrioridadMaxima& otra) {
    if (this == &otra) { // Protección contra auto-asignación
        return *this;
    }

    delete[] arreglo; // Liberamos la memoria vieja

    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    arreglo = new PersonaCola[capacidad]; // Creamos nueva memoria
    for (int i = 0; i < cantidad; ++i) {
        arreglo[i] = otra.arreglo[i]; // Copiamos cada elemento
    }
    return *this;
}

// -----------------------------------------------------------------------


bool ColaPrioridadMaxima::insertar(const PersonaCola& persona) {
    if (cantidad == capacidad) return false;
    // La asignación directa funciona gracias a std::string
    arreglo[cantidad] = persona;
    cantidad++;
    subir(cantidad - 1);
    return true;
}


bool ColaPrioridadMaxima::extraerMax(PersonaCola& persona) {
    if (cantidad == 0) return false;
    persona = arreglo[0];
    arreglo[0] = arreglo[cantidad - 1];
    cantidad--;
    bajar(0);
    return true;
}

bool ColaPrioridadMaxima::actualizarPrioridad(int id, int nuevaPrioridad) {
    int indice = buscarIndice(id);
    if (indice == -1) return false;
    int anterior = arreglo[indice].prioridad;
    arreglo[indice].prioridad = nuevaPrioridad;
    if (nuevaPrioridad > anterior)
        subir(indice);
    else
        bajar(indice);
    return true;
}

void ColaPrioridadMaxima::mostrarSiguientes(int n) {
    std::cout << "\n--- Siguientes personas en la cola (mayor prioridad primero) ---" << std::endl;

    // Creación de una copia temporal para no modificar el heap original
    ColaPrioridadMaxima copia = *this;

    int mostrar = (n < copia.cantidad) ? n : copia.cantidad;
    if (mostrar == 0) {
        std::cout << "No hay personas en la cola." << std::endl;
        return;
    }

    for (int i = 0; i < mostrar; ++i) {
        PersonaCola p;
        copia.extraerMax(p); // Extraemos el máximo de la copia
        std::cout << i + 1 << ". " << p.nombre << " (" << p.tipo << ", Prioridad: " << p.prioridad << ")" << std::endl;
    }
}

int ColaPrioridadMaxima::obtenerCantidad() const { return cantidad; }