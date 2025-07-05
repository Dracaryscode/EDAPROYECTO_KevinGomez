#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string> // CAMBIO: Añadir include para std::string

struct EntradaHash {
    int id;
    std::string nombre; // CAMBIO: de char nombre[50] a std::string
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
    // CAMBIO: ya no se necesita copiarCadena

public:
    TablaHash(int cap = 1009, float fc = 0.7f);
    ~TablaHash();
    // CAMBIO: El parámetro ahora es const std::string&
    bool insertar(int id, const std::string& nombre);
    // CAMBIO: El parámetro de salida ahora es std::string&
    bool buscar(int id, std::string& nombreOut);
    bool eliminar(int id);
    int obtenerCantidad() const;
};

#endif // HASHTABLE_H