#include "AVLTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_ZONAS = 100;

AVLNode::AVLNode(const Acceso& nuevoAcceso)
    : acceso(nuevoAcceso), altura(1), izq(nullptr), der(nullptr) {}

AVLTree::AVLTree() : raiz(nullptr) {}

int AVLTree::obtenerAltura(AVLNode* nodo) {
    return nodo ? nodo->altura : 0;
}

int AVLTree::obtenerBalance(AVLNode* nodo) {
    return nodo ? obtenerAltura(nodo->izq) - obtenerAltura(nodo->der) : 0;
}

int AVLTree::maximo(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* AVLTree::rotarDerecha(AVLNode* y) {
    AVLNode* x = y->izq;
    AVLNode* subArbolDerecho = x->der;

    x->der = y;
    y->izq = subArbolDerecho;

    y->altura = 1 + maximo(obtenerAltura(y->izq), obtenerAltura(y->der));
    x->altura = 1 + maximo(obtenerAltura(x->izq), obtenerAltura(x->der));

    return x;
}

AVLNode* AVLTree::rotarIzquierda(AVLNode* x) {
    AVLNode* y = x->der;
    AVLNode* subArbolIzquierdo = y->izq;

    y->izq = x;
    x->der = subArbolIzquierdo;

    x->altura = 1 + maximo(obtenerAltura(x->izq), obtenerAltura(x->der));
    y->altura = 1 + maximo(obtenerAltura(y->izq), obtenerAltura(y->der));

    return y;
}

AVLNode* AVLTree::insertarNodo(AVLNode* nodoActual, const Acceso& nuevoAcceso) {
    if (!nodoActual) return new AVLNode(nuevoAcceso);

    if (nuevoAcceso.hora < nodoActual->acceso.hora)
        nodoActual->izq = insertarNodo(nodoActual->izq, nuevoAcceso);
    else
        nodoActual->der = insertarNodo(nodoActual->der, nuevoAcceso);

    nodoActual->altura = 1 + maximo(obtenerAltura(nodoActual->izq), obtenerAltura(nodoActual->der));
    int balance = obtenerBalance(nodoActual);

    // Rotaciones
    if (balance > 1 && nuevoAcceso.hora < nodoActual->izq->acceso.hora)
        return rotarDerecha(nodoActual);

    if (balance < -1 && nuevoAcceso.hora > nodoActual->der->acceso.hora)
        return rotarIzquierda(nodoActual);

    if (balance > 1 && nuevoAcceso.hora > nodoActual->izq->acceso.hora) {
        nodoActual->izq = rotarIzquierda(nodoActual->izq);
        return rotarDerecha(nodoActual);
    }

    if (balance < -1 && nuevoAcceso.hora < nodoActual->der->acceso.hora) {
        nodoActual->der = rotarDerecha(nodoActual->der);
        return rotarIzquierda(nodoActual);
    }

    return nodoActual;
}

void AVLTree::insertar(const Acceso& nuevoAcceso) {
    raiz = insertarNodo(raiz, nuevoAcceso);
}

void AVLTree::recorridoInorden(AVLNode* nodo, vector<Acceso>& accesos) {
    if (!nodo) return;
    recorridoInorden(nodo->izq, accesos);
    accesos.push_back(nodo->acceso);
    recorridoInorden(nodo->der, accesos);
}

vector<Acceso> AVLTree::obtenerAccesosEnOrden() {
    vector<Acceso> accesos;
    recorridoInorden(raiz, accesos);
    return accesos;
}

void AVLTree::mostrarAccesos(const vector<Acceso>& accesos) {
    for (const auto& acc : accesos) {
        cout << "ID: " << acc.id << ", Zona: " << acc.zona << ", Hora: " << acc.hora << endl;
    }
}

void AVLTree::mostrarInorden() {
    cout << "\n--- Accesos registrados en orden de hora ---" << endl;
    mostrarAccesos(obtenerAccesosEnOrden());
}

void AVLTree::consultaFranjaHoraria(AVLNode* nodo, int h1, int h2, vector<Acceso>& resultado) {
    if (!nodo) return;

    if (nodo->acceso.hora >= h1 && nodo->acceso.hora <= h2)
        resultado.push_back(nodo->acceso);

    if (nodo->acceso.hora > h1)
        consultaFranjaHoraria(nodo->izq, h1, h2, resultado);

    if (nodo->acceso.hora < h2)
        consultaFranjaHoraria(nodo->der, h1, h2, resultado);
}

void AVLTree::consultaPorFranja(int h1, int h2) {
    cout << "\n--- Accesos entre las " << h1 << " y las " << h2 << " ---" << endl;
    vector<Acceso> resultado;
    consultaFranjaHoraria(raiz, h1, h2, resultado);
    mostrarAccesos(resultado);
}

void AVLTree::contarZonas(AVLNode* nodo, int* zonas, string* nombresZonas, int& totalZonas) {
    if (!nodo) return;

    int i;
    for (i = 0; i < totalZonas; ++i) {
        if (nombresZonas[i] == nodo->acceso.zona) {
            zonas[i]++;
            break;
        }
    }

    if (i == totalZonas) {
        nombresZonas[totalZonas] = nodo->acceso.zona;
        zonas[totalZonas] = 1;
        totalZonas++;
    }

    contarZonas(nodo->izq, zonas, nombresZonas, totalZonas);
    contarZonas(nodo->der, zonas, nombresZonas, totalZonas);
}

void AVLTree::zonaConMasEntradas() {
    int zonas[MAX_ZONAS] = {0};
    string nombresZonas[MAX_ZONAS];
    int totalZonas = 0;

    contarZonas(raiz, zonas, nombresZonas, totalZonas);

    if (totalZonas == 0) {
        cout << "No hay accesos registrados." << endl;
        return;
    }

    int indiceMax = 0;
    for (int i = 1; i < totalZonas; ++i) {
        if (zonas[i] > zonas[indiceMax]) {
            indiceMax = i;
        }
    }

    cout << "Zona con más entradas: " << nombresZonas[indiceMax]
         << " (" << zonas[indiceMax] << ")" << endl;
}
