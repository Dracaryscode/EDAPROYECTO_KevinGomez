#include "AVLTree.h"
#include <cstring> // Para strcmp, strcpy
#include <iostream>

using namespace std;

AVLNode::AVLNode(const Acceso& acc) {
    acceso = acc;
    altura = 1;
    izq = nullptr;
    der = nullptr;
}

int AVLTree::maximo(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::altura(AVLNode* nodo) {
    return nodo ? nodo->altura : 0;
}

int AVLTree::balance(AVLNode* nodo) {
    return nodo ? altura(nodo->izq) - altura(nodo->der) : 0;
}

AVLNode* AVLTree::rotacionDer(AVLNode* y) {
    AVLNode* x = y->izq;
    AVLNode* T2 = x->der;
    x->der = y;
    y->izq = T2;
    y->altura = 1 + maximo(altura(y->izq), altura(y->der));
    x->altura = 1 + maximo(altura(x->izq), altura(x->der));
    return x;
}

AVLNode* AVLTree::rotacionIzq(AVLNode* x) {
    AVLNode* y = x->der;
    AVLNode* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    x->altura = 1 + maximo(altura(x->izq), altura(x->der));
    y->altura = 1 + maximo(altura(y->izq), altura(y->der));
    return y;
}

AVLNode* AVLTree::insertar(AVLNode* nodo, const Acceso& acc) {
    if (!nodo) return new AVLNode(acc);
    if (acc.hora < nodo->acceso.hora)
        nodo->izq = insertar(nodo->izq, acc);
    else
        nodo->der = insertar(nodo->der, acc);
    nodo->altura = 1 + maximo(altura(nodo->izq), altura(nodo->der));
    int bal = balance(nodo);
    if (bal > 1 && acc.hora < nodo->izq->acceso.hora)
        return rotacionDer(nodo);
    if (bal < -1 && acc.hora > nodo->der->acceso.hora)
        return rotacionIzq(nodo);
    if (bal > 1 && acc.hora > nodo->izq->acceso.hora) {
        nodo->izq = rotacionIzq(nodo->izq);
        return rotacionDer(nodo);
    }
    if (bal < -1 && acc.hora < nodo->der->acceso.hora) {
        nodo->der = rotacionDer(nodo->der);
        return rotacionIzq(nodo);
    }
    return nodo;
}

void AVLTree::inorder(AVLNode* nodo) {
    if (!nodo) return;
    inorder(nodo->izq);
    cout << "ID: " << nodo->acceso.id << ", Zona: " << nodo->acceso.zona << ", Hora: " << nodo->acceso.hora << endl;
    inorder(nodo->der);
}

void AVLTree::consultaFranja(AVLNode* nodo, int h1, int h2) {
    if (!nodo) return;
    if (nodo->acceso.hora >= h1 && nodo->acceso.hora <= h2)
        cout << "ID: " << nodo->acceso.id << ", Zona: " << nodo->acceso.zona << ", Hora: " << nodo->acceso.hora << endl;
    if (nodo->acceso.hora > h1)
        consultaFranja(nodo->izq, h1, h2);
    if (nodo->acceso.hora < h2)
        consultaFranja(nodo->der, h1, h2);
}

void AVLTree::contarZonas(AVLNode* nodo, int* zonas, char zonasNombres[][30], int& nZonas) {
    if (!nodo) return;
    int i;
    for (i = 0; i < nZonas; ++i) {
        if (strcmp(zonasNombres[i], nodo->acceso.zona) == 0) {
            zonas[i]++;
            break;
        }
    }
    if (i == nZonas) {
        strcpy(zonasNombres[nZonas], nodo->acceso.zona);
        zonas[nZonas] = 1;
        nZonas++;
    }
    contarZonas(nodo->izq, zonas, zonasNombres, nZonas);
    contarZonas(nodo->der, zonas, zonasNombres, nZonas);
}

AVLTree::AVLTree() { raiz = nullptr; }

void AVLTree::insertar(const Acceso& acc) { raiz = insertar(raiz, acc); }

void AVLTree::mostrarInorder() {
    cout << "\n--- Accesos registrados en orden de hora ---" << endl;
    inorder(raiz);
}

void AVLTree::consultaPorFranja(int h1, int h2) {
    cout << "\n--- Accesos entre las " << h1 << " y las " << h2 << " ---" << endl;
    consultaFranja(raiz, h1, h2);
}

void AVLTree::zonaConMasEntradas() {
    int zonas[100] = {0};
    char zonasNombres[100][30];
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