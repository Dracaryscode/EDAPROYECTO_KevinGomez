#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>

struct EntradaHash {
    int id;
    char nombre[50];
    bool activo;
};

class TablaHash {
private:
    EntradaHash* tabla;
    int capacidad;
    int cantidad;
    float factorCarga;

    int hash(int id);
    void rehacerHash();
    void copiarCadena(char* destino, const char* origen);

public:
    TablaHash(int cap = 1009, float fc = 0.7f);
    ~TablaHash();
    bool insertar(int id, const char* nombre);
    bool buscar(int id, char* nombreOut);
    bool eliminar(int id);
    int obtenerCantidad() const;
};

#endif // HASHTABLE_H