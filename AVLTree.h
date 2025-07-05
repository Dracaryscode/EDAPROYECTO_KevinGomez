#ifndef AVLTREE_H
#define AVLTREE_H
#include <string> // CAMBIO: Añadir include para std::string

#include <iostream>

struct Acceso {
    int id;
    std::string zona; // CAMBIO: de char zona[30] a std::string
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
    // CAMBIO: La declaración ahora coincide con la del .cpp
    void contarZonas(AVLNode* nodo, int* zonas, std::string* zonasNombres, int& nZonas);

public:
    AVLTree();
    void insertar(const Acceso& acc);
    void mostrarInorder();
    void consultaPorFranja(int h1, int h2);
    void zonaConMasEntradas();
};

#endif // AVLTREE_H