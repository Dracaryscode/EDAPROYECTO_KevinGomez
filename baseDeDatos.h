// baseDeDatos.h
// Declaraciones extern para la base de datos simulada y la función de impresión
#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <string>
#include <vector> // CAMBIO: Incluimos vector para un almacenamiento dinámico
/*
// ==========================================================
// CÓDIGO ANTERIOR (COMENTADO COMO PARTE DEL PROCESO)
// ==========================================================
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

// Declaraciones de las funciones que estaban en baseDeDatos.cpp
void imprimirPersonasDB();
int cargarPersonasDesdeArchivo(const char* archivo); // Cambiado a int para devolver la cantidad
void guardarPersonasEnArchivo(const char* archivo);
void cargarAccesosDesdeArchivo(const char* archivo, class AVLTree& avl, class RBTree& rb);
// ==========================================================
*/

// ==========================================================
// NUEVA ESTRUCTURA DEL PROYECTO (SIGUIENDO INDICACIONES)
// ==========================================================

// La clase Persona será el objeto central de nuestra base de datos
class Persona {
public:
    int id; // DNI
    std::string nombre; // Nombres y Apellidos
    std::string zona;
    int prioridad;
};

// Esta será nuestra base de datos principal en memoria, usando un vector
// que es más flexible que un arreglo de tamaño fijo.
extern std::vector<Persona> baseDeDatosPersonas;


// --- Declaraciones de funciones ---
class AVLTree;
class RBTree;

int cargarPersonasDesdeArchivo(const char* nombreArchivo);
bool guardarPersonasEnArchivo(const char* nombreArchivo);
bool cargarAccesosDesdeArchivo(const char* archivo, AVLTree& arbolAVL, RBTree& arbolRB);



#endif // BASEDEDATOS_H