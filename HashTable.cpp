#include "HashTable.h"
#include <iostream>

// La función hash no cambia

void TablaHash::rehacerHash() {
    int capAntigua = capacidad;
    capacidad = capacidad * 2 + 1;
    EntradaHash* tablaAntigua = tabla;
    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) tabla[i].activo = false;
    cantidad = 0;
    for (int i = 0; i < capAntigua; ++i) {
        if (tablaAntigua[i].activo) {
            // CAMBIO: Ahora se inserta directamente el std::string
            insertar(tablaAntigua[i].id, tablaAntigua[i].nombre);
        }
    }
    delete[] tablaAntigua;
}

// CAMBIO: Se elimina la función copiarCadena

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

// CAMBIO: El parámetro es const std::string& y se usa asignación directa
bool TablaHash::insertar(int id, const std::string& nombre) {
    if ((float)(cantidad + 1) / capacidad > factorCarga) rehacerHash();
    int idx = hash(id);
    int inicio = idx;
    while (tabla[idx].activo) {
        if (tabla[idx].id == id) return false; // Ya existe
        idx = (idx + 1) % capacidad;
        if (idx == inicio) return false; // Tabla llena
    }
    tabla[idx].id = id;
    tabla[idx].nombre = nombre; // CAMBIO: Asignación directa
    tabla[idx].activo = true;
    cantidad++;
    return true;
}

// CAMBIO: El parámetro de salida es std::string&
bool TablaHash::buscar(int id, std::string& nombreOut) {
    int idx = hash(id);
    int inicio = idx;
    while (tabla[idx].activo) {
        if (tabla[idx].id == id) {
            nombreOut = tabla[idx].nombre; // CAMBIO: Asignación directa
            return true;
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) break;
    }
    return false;
}

// La función eliminar no cambia
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