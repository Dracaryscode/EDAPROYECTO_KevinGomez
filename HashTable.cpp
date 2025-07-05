#include "HashTable.h"
#include <iostream>

using namespace std;

int TablaHash::hash(int id) {
    int h = id % capacidad;
    if (h < 0) h += capacidad;
    return h;
}

void TablaHash::rehacerHash() {
    int capAntigua = capacidad;
    capacidad = capacidad * 2 + 1;
    EntradaHash* tablaAntigua = tabla;
    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) tabla[i].activo = false;
    cantidad = 0;
    for (int i = 0; i < capAntigua; ++i) {
        if (tablaAntigua[i].activo) {
            insertar(tablaAntigua[i].id, tablaAntigua[i].nombre);
        }
    }
    delete[] tablaAntigua;
}

void TablaHash::copiarCadena(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0' && i < 49) {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

TablaHash::TablaHash(int cap, float fc) {
    capacidad = cap;
    factorCarga = fc;
    cantidad = 0;
    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) tabla[i].activo = false;
}

TablaHash::~TablaHash() {
    delete[] tabla;
}

bool TablaHash::insertar(int id, const char* nombre) {
    if ((float)(cantidad + 1) / capacidad > factorCarga) rehacerHash();
    int idx = hash(id);
    int inicio = idx;
    while (tabla[idx].activo) {
        if (tabla[idx].id == id) return false; // Ya existe
        idx = (idx + 1) % capacidad;
        if (idx == inicio) return false; // Tabla llena
    }
    tabla[idx].id = id;
    copiarCadena(tabla[idx].nombre, nombre);
    tabla[idx].activo = true;
    cantidad++;
    return true;
}

bool TablaHash::buscar(int id, char* nombreOut) {
    int idx = hash(id);
    int inicio = idx;
    while (tabla[idx].activo) {
        if (tabla[idx].id == id) {
            copiarCadena(nombreOut, tabla[idx].nombre);
            return true;
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) break;
    }
    return false;
}

bool TablaHash::eliminar(int id) {
    int idx = hash(id);
    int inicio = idx;
    while (tabla[idx].activo) {
        if (tabla[idx].id == id) {
            tabla[idx].activo = false;
            cantidad--;
            return true;
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) break;
    }
    return false;
}

int TablaHash::obtenerCantidad() const { return cantidad; }