// baseDeDatos.h
// Declaraciones extern para la base de datos simulada y la función de impresión
#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <string>

// CAMBIO 1: Renombramos el struct para evitar confusión.
// Este es el "molde" o "tipo" de dato.
struct PersonaData {
    int id;
    std::string nombre;
    std::string tipo;
    int prioridad;
};

const int MAX_PERSONAS = 200; // Define un tamaño máximo para tu base de datos

// CAMBIO 2: Declaramos el arreglo como 'extern'.
// Esto le dice a otros archivos que la variable PersonaDB existe en alguna parte.
extern PersonaData PersonaDB[MAX_PERSONAS];

// Declaraciones de las funciones que están en baseDeDatos.cpp
void imprimirPersonasDB();
int cargarPersonasDesdeArchivo(const char* archivo); // Cambiado a int para devolver la cantidad
void guardarPersonasEnArchivo(const char* archivo);
void cargarAccesosDesdeArchivo(const char* archivo, class AVLTree& avl, class RBTree& rb);

#endif // BASEDEDATOS_H