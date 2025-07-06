#include "HashTable.h"
#include <iostream>

int TablaHash::hash(int id) {
    int h = id % capacidad;
    if (h < 0) h += capacidad;
    return h;
}

void TablaHash::rehacerHash() {
    int capAntigua = capacidad;
    capacidad = capacidad * 2 + 1; // Un primo grande es buena idea
    EntradaHash* tablaAntigua = tabla;

    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        tabla[i].personaPtr = nullptr; // Inicializamos punteros a nulo
        tabla[i].activo = false;
    }
    cantidad = 0;

    for (int i = 0; i < capAntigua; ++i) {
        if (tablaAntigua[i].activo && tablaAntigua[i].personaPtr != nullptr) {
            // CAMBIO: Volvemos a insertar el puntero en la nueva tabla
            insertar(tablaAntigua[i].personaPtr);
        }
    }
    delete[] tablaAntigua;
}

TablaHash::TablaHash(int cap, float fc) {
    capacidad = cap;
    factorCarga = fc;
    cantidad = 0;
    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        tabla[i].personaPtr = nullptr; // Inicializar punteros a nulo
        tabla[i].activo = false;
    }
}

TablaHash::~TablaHash() {
    delete[] tabla;
}

// --- IMPLEMENTACIÓN DE LA REGLA DE TRES PARA EVITAR ERRORES DE MEMORIA ---

// Constructor de copia: Crea una copia profunda de otra TablaHash.
TablaHash::TablaHash(const TablaHash& otra) {
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    factorCarga = otra.factorCarga;
    tabla = new EntradaHash[capacidad]; // Se crea nueva memoria
    for (int i = 0; i < capacidad; ++i) {
        tabla[i] = otra.tabla[i]; // Se copia cada elemento
    }
}

// Operador de asignación: Asigna una TablaHash a otra de forma segura.
TablaHash& TablaHash::operator=(const TablaHash& otra) {
    // 1. Proteger contra la auto-asignación (ej. miTabla = miTabla;)
    if (this == &otra) {
        return *this;
    }

    // 2. Liberar la memoria que ya existía
    delete[] tabla;

    // 3. Copiar los datos y crear nueva memoria
    capacidad = otra.capacidad;
    cantidad = otra.cantidad;
    factorCarga = otra.factorCarga;
    tabla = new EntradaHash[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        tabla[i] = otra.tabla[i]; // Se copia cada elemento
    }

    // 4. Devolver el objeto actual para permitir asignaciones en cadena (a = b = c;)
    return *this;
}

// -----------------------------------------------------------------------


// CAMBIO: Acepta un puntero a Persona y lo almacena
bool TablaHash::insertar(Persona* persona) {
    if (!persona) return false; // No insertar punteros nulos

    if ((float)(cantidad + 1) / capacidad > factorCarga) rehacerHash();

    int idx = hash(persona->id);
    int inicio = idx;

    while (tabla[idx].activo) {
        if (tabla[idx].personaPtr && tabla[idx].personaPtr->id == persona->id) {
            return false; // Ya existe
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) return false; // Tabla llena
    }

    tabla[idx].personaPtr = persona; // Guardamos el puntero
    tabla[idx].activo = true;
    cantidad++;
    return true;
}

// CAMBIO: Devuelve un puntero a Persona si lo encuentra, o nullptr si no
Persona* TablaHash::buscar(int id) {
    int idx = hash(id);
    int inicio = idx;

    // El bucle debe continuar mientras haya posibilidad de encontrarlo
    // Se revisa 'activo' en lugar de 'personaPtr != nullptr' para poder pasar sobre casillas borradas.
    while (tabla[idx].activo || tabla[idx].personaPtr != nullptr) {
        if (tabla[idx].activo && tabla[idx].personaPtr && tabla[idx].personaPtr->id == id) {
            return tabla[idx].personaPtr; // Encontrado, devolvemos el puntero
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) break; // Dimos la vuelta completa
    }
    return nullptr; // No encontrado
}

bool TablaHash::eliminar(int id) {
    int idx = hash(id);
    int inicio = idx;

    // Se usa la misma lógica de búsqueda para encontrar el elemento a eliminar
    while (tabla[idx].activo || tabla[idx].personaPtr != nullptr) {
        if (tabla[idx].activo && tabla[idx].personaPtr && tabla[idx].personaPtr->id == id) {
            tabla[idx].activo = false; // Marcamos como inactivo (eliminado lógico)
            cantidad--;
            return true;
        }
        idx = (idx + 1) % capacidad;
        if (idx == inicio) break;
    }
    return false;
}

int TablaHash::obtenerCantidad() const { return cantidad; }