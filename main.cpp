#include <cstdlib> // Necesario para la función system() y que se reconozca las tildes
#include <cstdlib> // Necesario para la función system() y que se reconozca las tildes
#include <iostream>
#include <string>
#include <cstring>
#include <limits>

#include "HashTable.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "baseDeDatos.h" // Asegurarme de que este archivo esté correcto

// Muestra el menú principal
void mostrarMenu(bool usarAVL) {
    std::cout << "\n==== SISTEMA DE CONTROL DE ACCESOS ====" << std::endl;
    std::cout << "1. Registrar usuario (HashTable)" << std::endl;
    std::cout << "2. Buscar usuario (HashTable)" << std::endl;
    std::cout << "3. Eliminar usuario (HashTable)" << std::endl;
    std::cout << "4. Insertar persona en cola de acceso (MaxHeap)" << std::endl;
    std::cout << "5. Mostrar siguientes accesos por prioridad (MaxHeap)" << std::endl;
    std::cout << "6. Actualizar prioridad de persona (MaxHeap)" << std::endl;
    std::cout << "7. Registrar acceso (" << (usarAVL ? "AVL" : "Red-Black") << ")" << std::endl;
    std::cout << "8. Mostrar accesos en orden por hora (" << (usarAVL ? "AVL" : "Red-Black") << ")" << std::endl;
    std::cout << "9. Consultar accesos por franja horaria (" << (usarAVL ? "AVL" : "Red-Black") << ")" << std::endl;
    std::cout << "10. Mostrar zona con más entradas (" << (usarAVL ? "AVL" : "Red-Black") << ")" << std::endl;
    std::cout << "11. Cambiar estructura de árbol (AVL/Red-Black)" << std::endl;
    std::cout << "12. Cargar base de datos desde archivo" << std::endl;
    std::cout << "13. Guardar base de datos en archivo" << std::endl;
    std::cout << "14. Cargar historial de accesos" << std::endl;
    std::cout << "0. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

// Función para leer un entero de forma segura
int leerEntero(){
    int valor;
    while (!(std::cin >> valor)){
        std::cout << "Entrada inválida. Por favor, ingrese un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valor;
}

// ===================== FUNCIÓN PRINCIPAL =====================
int main() {
    system("chcp 65001");
    TablaHash tabla;
    ColaPrioridadMaxima heap;
    AVLTree arbolAVL;
    RBTree arbolRB;
    bool usarAVL = true;
    int opcion;

    std::cout << "Bienvenido. Por favor, cargue una base de datos con la opción 12." << std::endl;

    // --- CAMBIO: Solo hay UN bucle do-while ---
    do {
        mostrarMenu(usarAVL);
        opcion = leerEntero();

        if (opcion == 1) {
            int id;
            std::string nombre;
            std::cout << "DNI/código: ";
            id = leerEntero();
            std::cout << "Nombre: ";
            std::getline(std::cin, nombre);
            if (tabla.insertar(id, nombre))
                std::cout << "Usuario registrado." << std::endl;
            else
                std::cout << "Error: usuario ya existe." << std::endl;
        } else if (opcion == 2) {
            int id;
            std::string nombre;
            std::cout << "DNI/código: ";
            id = leerEntero();
            if (tabla.buscar(id, nombre))
                std::cout << "Usuario: " << nombre << std::endl;
            else
                std::cout << "No encontrado." << std::endl;
        } else if (opcion == 3) {
            int id;
            std::cout << "DNI/código: ";
            id = leerEntero();
            if (tabla.eliminar(id))
                std::cout << "Usuario eliminado." << std::endl;
            else
                std::cout << "No encontrado." << std::endl;
        } else if (opcion == 4) {
            PersonaCola p;
            std::cout << "DNI/código: ";
            p.id = leerEntero();
            std::cout << "Nombre: ";
            std::getline(std::cin, p.nombre);
            std::cout << "Prioridad (5:VIP, 4:Médico, 3:Seguridad, 2:Discapacitado, 1:General): ";
            p.prioridad = leerEntero();
            std::cout << "Tipo: ";
            std::getline(std::cin, p.tipo);
            if (heap.insertar(p))
                std::cout << "Persona añadida a la cola de acceso." << std::endl;
            else
                std::cout << "Cola llena." << std::endl;
        } else if (opcion == 5) {
            heap.mostrarSiguientes(5);
        } else if (opcion == 6) {
            int id, prio;
            std::cout << "DNI/código: ";
            id = leerEntero();
            std::cout << "Nueva prioridad: ";
            prio = leerEntero();
            if (heap.actualizarPrioridad(id, prio))
                std::cout << "Prioridad actualizada." << std::endl;
            else
                std::cout << "No encontrado." << std::endl;
        } else if (opcion == 7) {
            if (usarAVL) {
                Acceso a;
                std::cout << "DNI/código: ";
                a.id = leerEntero();
                std::cout << "Zona: ";
                std::getline(std::cin, a.zona);
                std::cout << "Hora (ej: 1430): ";
                a.hora = leerEntero();
                arbolAVL.insertar(a);
                std::cout << "Acceso registrado en AVL." << std::endl;
            } else {
                RBAcceso a;
                std::cout << "DNI/código: ";
                a.id = leerEntero();
                std::cout << "Zona: ";
                std::getline(std::cin, a.zona);
                std::cout << "Hora (ej: 1430): ";
                a.hora = leerEntero();
                arbolRB.insertar(a);
                std::cout << "Acceso registrado en Red-Black." << std::endl;
            }
        } else if (opcion == 8) {
            if (usarAVL) arbolAVL.mostrarInorder();
            else arbolRB.mostrarInorder();
        } else if (opcion == 9) {
            int h1, h2;
            std::cout << "Hora inicio: ";
            h1 = leerEntero();
            std::cout << "Hora fin: ";
            h2 = leerEntero();
            if (usarAVL) arbolAVL.consultaPorFranja(h1, h2);
            else arbolRB.consultaPorFranja(h1, h2);
        } else if (opcion == 10) {
            if (usarAVL) arbolAVL.zonaConMasEntradas();
            else arbolRB.zonaConMasEntradas();
        } else if (opcion == 11) {
            usarAVL = !usarAVL;
            std::cout << "Ahora usando " << (usarAVL ? "AVL" : "Red-Black") << " para accesos." << std::endl;
        } else if (opcion == 12) {
            char archivo[] = "personas_50k.csv";
            std::cout << "Cargando datos desde " << archivo << "..." << std::endl;

            int personasCargadas = cargarPersonasDesdeArchivo(archivo);

            if (personasCargadas > 0) {
                tabla = TablaHash(); // Reinicia la tabla hash

                // CAMBIO CLAVE: Llenamos la tabla hash con punteros
                for (int i = 0; i < baseDeDatosPersonas.size(); ++i) {
                    // Pasamos la dirección de memoria (&) de cada objeto Persona
                    tabla.insertar(&baseDeDatosPersonas[i]);
                }

                std::cout << "¡Éxito! Se cargaron " << personasCargadas << " registros y se indexaron en la tabla hash." << std::endl;

                // El MaxHeap se puede llenar después, cuando la persona "llega" al evento.
                // Por ahora lo dejamos vacío para seguir la simulación.
                heap = ColaPrioridadMaxima();

            } else {
                std::cout << "Fallo al cargar la base de datos." << std::endl;
            }
        } else if (opcion == 13) {
            std::string archivo;
            std::cout << "Nombre del archivo CSV para guardar: ";
            std::getline(std::cin, archivo);
            guardarPersonasEnArchivo(archivo.c_str());
        } else if (opcion == 14) {
            std::string archivo;
            std::cout << "Nombre del archivo de accesos: ";
            std::getline(std::cin, archivo);
            cargarAccesosDesdeArchivo(archivo.c_str(), arbolAVL, arbolRB);
        } else if (opcion == 0) {
            std::cout << "Saliendo..." << std::endl;
        } else {
            std::cout << "Opción inválida." << std::endl;
        }
    } while (opcion != 0);

    return 0;
}