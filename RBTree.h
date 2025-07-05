#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>

enum Color { ROJO, NEGRO };

struct RBAcceso {
    int id;
    char zona[30];
    int hora;
};

class RBNode {
public:
    RBAcceso acceso;
    Color color;
    RBNode *izq, *der, *padre;
    RBNode(const RBAcceso& acc);
};

class RBTree {
private:
    RBNode* raiz;
    RBNode* NIL;
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void insertFixup(RBNode* z);
    void inorder(RBNode* nodo);
    void consultaFranja(RBNode* nodo, int h1, int h2);
    void contarZonas(RBNode* nodo, int* zonas, char zonasNombres[][30], int& nZonas);

public:
    RBTree();
    void insertar(const RBAcceso& acc);
    void mostrarInorder();
    void consultaPorFranja(int h1, int h2);
    void zonaConMasEntradas();
};

#endif // RBTREE_H