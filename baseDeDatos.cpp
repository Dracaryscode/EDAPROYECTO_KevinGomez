#include "baseDeDatos.h" // Incluir el .h que ya define la estructura
#include <iostream>
#include <fstream>
#include <sstream>

// Incluimos los headers de las clases que usamos
#include "AVLTree.h"
#include "RBTree.h"


/*
// ==========================================================
// CÓDIGO ANTERIOR (COMENTADO COMO PARTE DEL PROCESO)
// ==========================================================
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
// ==========================================================
*/


// ==========================================================
// NUEVA ESTRUCTURA DEL PROYECTO (SIGUIENDO INDICACIONES)
// ==========================================================

// Definimos el vector global que contendrá todas las personas.
// Este vector fue declarado como 'extern' en baseDeDatos.h.
std::vector<Persona> baseDeDatosPersonas;

int cargarPersonasDesdeArchivo(const char* nombreArchivo) {
    std::ifstream file(nombreArchivo);
    if (!file.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return 0;
    }

    // Limpiamos la base de datos por si se carga un nuevo archivo
    baseDeDatosPersonas.clear();

    std::string linea;
    // Omitir la cabecera del CSV si la tiene
    if (file.good()) {
        getline(file, linea);
    }

    while (getline(file, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        Persona nuevaPersona;

        // Asumimos que el orden en el CSV es: id,nombre,zona,prioridad
        getline(ss, campo, ',');
        try {
            nuevaPersona.id = std::stoi(campo);
        } catch (const std::invalid_argument& ia) {
            continue; // Si el ID no es un número válido, saltamos esta línea
        }

        getline(ss, campo, ',');
        nuevaPersona.nombre = campo;

        getline(ss, campo, ',');
        nuevaPersona.zona = campo;

        getline(ss, campo, ',');
        try {
            nuevaPersona.prioridad = std::stoi(campo);
        } catch (const std::invalid_argument& ia) {
            continue; // Si la prioridad no es un número válido, saltamos esta línea
        }

        // Añadimos el objeto Persona completo al vector
        baseDeDatosPersonas.push_back(nuevaPersona);
    }

    file.close();
    std::cout << "Se leyeron y almacenaron " << baseDeDatosPersonas.size() << " registros de personas." << std::endl;
    return baseDeDatosPersonas.size();
}

// Las otras funciones se mantienen, pero podrían necesitar implementación más adelante
bool guardarPersonasEnArchivo(const char* nombreArchivo) {
    // Lógica para guardar el vector de personas en un archivo
    return true;
}

bool cargarAccesosDesdeArchivo(const char* archivo, AVLTree& arbolAVL, RBTree& arbolRB) {
    // Lógica para cargar accesos
    return true;
}