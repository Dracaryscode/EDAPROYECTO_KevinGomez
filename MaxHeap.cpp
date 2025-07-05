#include "MaxHeap.h"
#include <iostream>

using namespace std;

void ColaPrioridadMaxima::subir(int indice) {
    while (indice > 0) {
        int padre = (indice - 1) / 2;
        if (arreglo[indice].prioridad > arreglo[padre].prioridad) {
            PersonaCola temp = arreglo[indice];
            arreglo[indice] = arreglo[padre];
            arreglo[padre] = temp;
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
            PersonaCola temp = arreglo[indice];
            arreglo[indice] = arreglo[mayor];
            arreglo[mayor] = temp;
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

// CAMBIO: Se elimina la función copiarCadena

ColaPrioridadMaxima::ColaPrioridadMaxima(int cap) {
    capacidad = cap;
    cantidad = 0;
    arreglo = new PersonaCola[capacidad];
}

ColaPrioridadMaxima::~ColaPrioridadMaxima() {
    delete[] arreglo;
}

bool ColaPrioridadMaxima::insertar(const PersonaCola& persona) {
    if (cantidad == capacidad) return false;
    // CAMBIO: Asignación directa de std::string
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
    cout << "\n--- Siguientes personas en la cola (mayor prioridad primero) ---" << endl;

    // Creación de una copia temporal para no modificar el heap original
    ColaPrioridadMaxima copia = *this;

    int mostrar = (n < copia.cantidad) ? n : copia.cantidad;
    if (mostrar == 0) {
        cout << "No hay personas en la cola." << endl;
        return;
    }

    for (int i = 0; i < mostrar; ++i) {
        PersonaCola p;
        copia.extraerMax(p); // Extraemos el máximo de la copia
        cout << i + 1 << ". " << p.nombre << " (" << p.tipo << ", Prioridad: " << p.prioridad << ")" << endl;
    }
}

int ColaPrioridadMaxima::obtenerCantidad() const { return cantidad; }