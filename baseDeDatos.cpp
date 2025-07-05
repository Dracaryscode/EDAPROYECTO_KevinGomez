#include "baseDeDatos.h" // Incluir el .h que ya define la estructura
#include <iostream>
#include <fstream>
#include <sstream>

// Incluimos los headers de las clases que usamos
#include "AVLTree.h"
#include "RBTree.h"

// Aquí se crea la variable global (el arreglo) que fue declarada en el .h
PersonaData PersonaDB[MAX_PERSONAS];

// La función ahora lee el CSV y devuelve cuántas personas leyó
int cargarPersonasDesdeArchivo(const char* nombreArchivo) {
    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return 0;
    }

    std::string linea;
    int contador = 0;

    // Omitir la cabecera del CSV
    if (getline(file, linea)) {
        // Cabecera leída y descartada
    }

    while (getline(file, linea) && contador < MAX_PERSONAS) {
        std::stringstream ss(linea);
        std::string campo;

        // Leer cada campo separado por comas
        getline(ss, campo, ',');
        PersonaDB[contador].id = std::stoi(campo);

        getline(ss, campo, ',');
        PersonaDB[contador].nombre = campo;

        getline(ss, campo, ',');
        PersonaDB[contador].tipo = campo;

        getline(ss, campo, ',');
        PersonaDB[contador].prioridad = std::stoi(campo);

        contador++;
    }

    file.close();
    std::cout << "Se leyeron " << contador << " registros del archivo." << std::endl;
    return contador;
}

// Implementación de las otras funciones
void guardarPersonasEnArchivo(const char* nombreArchivo) {
    // Implementa la lógica para guardar aquí si la necesitas
}

void cargarAccesosDesdeArchivo(const char* nombreArchivo, AVLTree& avl, RBTree& rb) {
    // Implementa la lógica para cargar accesos aquí si la necesitas
}

void imprimirPersonasDB() {
    // Implementa la lógica para imprimir aquí si la necesitas
}