#include <cstdlib> // Necesario para la función system() y que se reconozca las tildes
#include <iostream>
#include <string>
#include <cstring>
#include <limits>

#include "HashTable.h"
#include "MaxHeap.h"
#include "AVLTree.h"
#include "RBTree.h"
#include "baseDeDatos.h" // Asegúrate de que este archivo esté correcto

using namespace std;

// Muestra el menú principal
void mostrarMenu(bool usarAVL) {
    cout << "\n==== SISTEMA DE CONTROL DE ACCESOS ====" << endl;
    cout << "1. Registrar usuario (HashTable)" << endl;
    cout << "2. Buscar usuario (HashTable)" << endl;
    cout << "3. Eliminar usuario (HashTable)" << endl;
    cout << "4. Insertar persona en cola de acceso (MaxHeap)" << endl;
    cout << "5. Mostrar siguientes accesos por prioridad (MaxHeap)" << endl;
    cout << "6. Actualizar prioridad de persona (MaxHeap)" << endl;
    cout << "7. Registrar acceso (" << (usarAVL ? "AVL" : "Red-Black") << ")" << endl;
    cout << "8. Mostrar accesos en orden por hora (" << (usarAVL ? "AVL" : "Red-Black") << ")" << endl;
    cout << "9. Consultar accesos por franja horaria (" << (usarAVL ? "AVL" : "Red-Black") << ")" << endl;
    cout << "10. Mostrar zona con más entradas (" << (usarAVL ? "AVL" : "Red-Black") << ")" << endl;
    cout << "11. Cambiar estructura de árbol (AVL/Red-Black)" << endl;
    cout << "12. Cargar base de datos desde archivo" << endl;
    cout << "13. Guardar base de datos en archivo" << endl;
    cout << "14. Cargar historial de accesos" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opción: ";
}

// Función para leer un entero de forma segura
int leerEntero(){
    int valor;
    while (!(cin >> valor)){
        cout << "Entrada inválida. Por favor, ingrese un número: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    cout << "Bienvenido. Por favor, cargue una base de datos con la opción 12." << endl;

    // --- CAMBIO: Solo hay UN bucle do-while ---
    do {
        mostrarMenu(usarAVL);
        opcion = leerEntero();

        if (opcion == 1) {
            int id;
            char nombre[50];
            cout << "DNI/código: ";
            id = leerEntero();
            cout << "Nombre: ";
            cin.getline(nombre, 50);
            if (tabla.insertar(id, nombre))
                cout << "Usuario registrado." << endl;
            else
                cout << "Error: usuario ya existe." << endl;
        } else if (opcion == 2) {
            int id;
            char nombre[50];
            cout << "DNI/código: ";
            id = leerEntero();
            if (tabla.buscar(id, nombre))
                cout << "Usuario: " << nombre << endl;
            else
                cout << "No encontrado." << endl;
        } else if (opcion == 3) {
            int id;
            cout << "DNI/código: ";
            id = leerEntero();
            if (tabla.eliminar(id))
                cout << "Usuario eliminado." << endl;
            else
                cout << "No encontrado." << endl;
        } else if (opcion == 4) {
            PersonaCola p;
            cout << "DNI/código: ";
            p.id = leerEntero();
            cout << "Nombre: ";
            cin.getline(p.nombre, 50);
            cout << "Prioridad (5:VIP, 4:Médico, 3:Seguridad, 2:Discapacitado, 1:General): ";
            p.prioridad = leerEntero();
            cout << "Tipo: ";
            cin.getline(p.tipo, 20);
            if (heap.insertar(p))
                cout << "Persona añadida a la cola de acceso." << endl;
            else
                cout << "Cola llena." << endl;
        } else if (opcion == 5) {
            heap.mostrarSiguientes(5);
        } else if (opcion == 6) {
            int id, prio;
            cout << "DNI/código: ";
            id = leerEntero();
            cout << "Nueva prioridad: ";
            prio = leerEntero();
            if (heap.actualizarPrioridad(id, prio))
                cout << "Prioridad actualizada." << endl;
            else
                cout << "No encontrado." << endl;
        } else if (opcion == 7) {
            if (usarAVL) {
                Acceso a;
                cout << "DNI/código: ";
                a.id = leerEntero();
                cout << "Zona: ";
                cin.getline(a.zona, 30);
                cout << "Hora (ej: 1430): ";
                a.hora = leerEntero();
                arbolAVL.insertar(a);
                cout << "Acceso registrado en AVL." << endl;
            } else {
                RBAcceso a;
                cout << "DNI/código: ";
                a.id = leerEntero();
                cout << "Zona: ";
                cin.getline(a.zona, 30);
                cout << "Hora (ej: 1430): ";
                a.hora = leerEntero();
                arbolRB.insertar(a);
                cout << "Acceso registrado en Red-Black." << endl;
            }
        } else if (opcion == 8) {
            if (usarAVL) arbolAVL.mostrarInorder();
            else arbolRB.mostrarInorder();
        } else if (opcion == 9) {
            int h1, h2;
            cout << "Hora inicio: ";
            h1 = leerEntero();
            cout << "Hora fin: ";
            h2 = leerEntero();
            if (usarAVL) arbolAVL.consultaPorFranja(h1, h2);
            else arbolRB.consultaPorFranja(h1, h2);
        } else if (opcion == 10) {
            if (usarAVL) arbolAVL.zonaConMasEntradas();
            else arbolRB.zonaConMasEntradas();
        } else if (opcion == 11) {
            usarAVL = !usarAVL;
            cout << "Ahora usando " << (usarAVL ? "AVL" : "Red-Black") << " para accesos." << endl;
        } else if (opcion == 12) {
            char archivo[] = "personas_50k.csv";
            cout << "Cargando datos desde " << archivo << "..." << endl;

            int personasCargadas = cargarPersonasDesdeArchivo(archivo);

            if (personasCargadas > 0) {
                tabla = TablaHash();
                heap = ColaPrioridadMaxima();

                for (int i = 0; i < personasCargadas; ++i) {
                    tabla.insertar(PersonaDB[i].id, PersonaDB[i].nombre.c_str());

                    PersonaCola p;
                    p.id = PersonaDB[i].id;
                    strncpy(p.nombre, PersonaDB[i].nombre.c_str(), 49);
                    p.nombre[49] = '\0';
                    strncpy(p.tipo, PersonaDB[i].tipo.c_str(), 19);
                    p.tipo[19] = '\0';
                    p.prioridad = PersonaDB[i].prioridad;
                    heap.insertar(p);
                }
                cout << "¡Éxito! Se cargaron y procesaron " << personasCargadas << " registros." << endl;
            } else {
                cout << "Fallo al cargar la base de datos." << endl;
            }
        } else if (opcion == 13) {
            char archivo[100];
            cout << "Nombre del archivo CSV para guardar: ";
            cin.getline(archivo, 100);
            guardarPersonasEnArchivo(archivo);
        } else if (opcion == 14) {
            char archivo[100];
            cout << "Nombre del archivo de accesos: ";
            cin.getline(archivo, 100);
            cargarAccesosDesdeArchivo(archivo, arbolAVL, arbolRB);
        } else if (opcion == 0) {
            cout << "Saliendo..." << endl;
        } else {
            cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);

    return 0;
}