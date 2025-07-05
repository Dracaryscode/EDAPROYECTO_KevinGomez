#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

struct Acceso {
    int id;
    char zona[30];
    int hora;
};

class AVLNode {
public:
    Acceso acceso;
    int altura;
    AVLNode* izq;
    AVLNode* der;
    AVLNode(const Acceso& acc);
};

class AVLTree {
private:
    AVLNode* raiz;
    int maximo(int a, int b);
    int altura(AVLNode* nodo);
    int balance(AVLNode* nodo);
    AVLNode* rotacionDer(AVLNode* y);
    AVLNode* rotacionIzq(AVLNode* x);
    AVLNode* insertar(AVLNode* nodo, const Acceso& acc);
    void inorder(AVLNode* nodo);
    void consultaFranja(AVLNode* nodo, int h1, int h2);
    void contarZonas(AVLNode* nodo, int* zonas, char zonasNombres[][30], int& nZonas);

public:
    AVLTree();
    void insertar(const Acceso& acc);
    void mostrarInorder();
    void consultaPorFranja(int h1, int h2);
    void zonaConMasEntradas();
};

#endif // AVLTREE_H