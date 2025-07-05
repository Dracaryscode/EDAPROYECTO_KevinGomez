#include "RBTree.h"
#include <cstring>
#include <iostream>

using namespace std;

RBNode::RBNode(const RBAcceso& acc) {
    acceso = acc;
    color = ROJO;
    izq = der = padre = nullptr;
}

void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->der;
    x->der = y->izq;
    if (y->izq != NIL) y->izq->padre = x;
    y->padre = x->padre;
    if (x->padre == NIL) raiz = y;
    else if (x == x->padre->izq) x->padre->izq = y;
    else x->padre->der = y;
    y->izq = x;
    x->padre = y;
}

void RBTree::rightRotate(RBNode* y) {
    RBNode* x = y->izq;
    y->izq = x->der;
    if (x->der != NIL) x->der->padre = y;
    x->padre = y->padre;
    if (y->padre == NIL) raiz = x;
    else if (y == y->padre->izq) y->padre->izq = x;
    else y->padre->der = x;
    x->der = y;
    y->padre = x;
}

void RBTree::insertFixup(RBNode* z) {
    while (z->padre->color == ROJO) {
        if (z->padre == z->padre->padre->izq) {
            RBNode* y = z->padre->padre->der;
            if (y->color == ROJO) {
                z->padre->color = NEGRO;
                y->color = NEGRO;
                z->padre->padre->color = ROJO;
                z = z->padre->padre;
            } else {
                if (z == z->padre->der) {
                    z = z->padre;
                    leftRotate(z);
                }
                z->padre->color = NEGRO;
                z->padre->padre->color = ROJO;
                rightRotate(z->padre->padre);
            }
        } else {
            RBNode* y = z->padre->padre->izq;
            if (y->color == ROJO) {
                z->padre->color = NEGRO;
                y->color = NEGRO;
                z->padre->padre->color = ROJO;
                z = z->padre->padre;
            } else {
                if (z == z->padre->izq) {
                    z = z->padre;
                    rightRotate(z);
                }
                z->padre->color = NEGRO;
                z->padre->padre->color = ROJO;
                leftRotate(z->padre->padre);
            }
        }
    }
    raiz->color = NEGRO;
}

void RBTree::inorder(RBNode* nodo) {
    if (nodo == NIL) return;
    inorder(nodo->izq);
    cout << "ID: " << nodo->acceso.id << ", Zona: " << nodo->acceso.zona << ", Hora: " << nodo->acceso.hora << endl;
    inorder(nodo->der);
}

void RBTree::consultaFranja(RBNode* nodo, int h1, int h2) {
    if (nodo == NIL) return;
    if (nodo->acceso.hora >= h1 && nodo->acceso.hora <= h2)
        cout << "ID: " << nodo->acceso.id << ", Zona: " << nodo->acceso.zona << ", Hora: " << nodo->acceso.hora << endl;
    if (nodo->acceso.hora > h1)
        consultaFranja(nodo->izq, h1, h2);
    if (nodo->acceso.hora < h2)
        consultaFranja(nodo->der, h1, h2);
}

void RBTree::contarZonas(RBNode* nodo, int* zonas, std::string* zonasNombres, int& nZonas) {
    if (!nodo) return;
    int i;
    for (i = 0; i < nZonas; ++i) {
        // CAMBIO: de strcmp(zonasNombres[i], nodo->acceso.zona) == 0 a ==
        if (zonasNombres[i] == nodo->acceso.zona) {
            zonas[i]++;
            break;
        }
    }
    if (i == nZonas) {
        // CAMBIO: de strcpy a asignación directa
        zonasNombres[nZonas] = nodo->acceso.zona;
        zonas[nZonas] = 1;
        nZonas++;
    }
    contarZonas(nodo->izq, zonas, zonasNombres, nZonas);
    contarZonas(nodo->der, zonas, zonasNombres, nZonas);
}

RBTree::RBTree() {
    NIL = new RBNode({0, "", 0});
    NIL->color = NEGRO;
    NIL->izq = NIL->der = NIL->padre = NIL;
    raiz = NIL;
}

void RBTree::insertar(const RBAcceso& acc) {
    RBNode* z = new RBNode(acc);
    RBNode* y = NIL;
    RBNode* x = raiz;
    while (x != NIL) {
        y = x;
        if (z->acceso.hora < x->acceso.hora)
            x = x->izq;
        else
            x = x->der;
    }
    z->padre = y;
    if (y == NIL) raiz = z;
    else if (z->acceso.hora < y->acceso.hora) y->izq = z;
    else y->der = z;
    z->izq = z->der = NIL;
    z->color = ROJO;
    insertFixup(z);
}

void RBTree::mostrarInorder() { inorder(raiz); }

void RBTree::consultaPorFranja(int h1, int h2) { consultaFranja(raiz, h1, h2); }

void RBTree::zonaConMasEntradas() {
    int zonas[100] = {0};
    // CAMBIO: El arreglo ahora es de std::string
    std::string zonasNombres[100];
    int nZonas = 0;
    contarZonas(raiz, zonas, zonasNombres, nZonas);
    int maxIdx = 0;
    for (int i = 1; i < nZonas; ++i) {
        if (zonas[i] > zonas[maxIdx]) maxIdx = i;
    }
    if (nZonas > 0)
        cout << "Zona con más entradas: " << zonasNombres[maxIdx] << " (" << zonas[maxIdx] << ")" << endl;
    else
        cout << "No hay accesos registrados." << endl;
}