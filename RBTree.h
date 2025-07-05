#ifndef RBTREE_H
#define RBTREE_H

#include <string> // CAMBIO: Añadir include para std::string


enum Color { ROJO, NEGRO };

struct RBAcceso {
    int id;
    std::string zona; // CAMBIO: de char zona[30] a std::string
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
    // CAMBIO: La declaración ahora coincide con la del .cpp
    void contarZonas(RBNode* nodo, int* zonas, std::string* zonasNombres, int& nZonas);

public:
    RBTree();
    void insertar(const RBAcceso& acc);
    void mostrarInorder();
    void consultaPorFranja(int h1, int h2);
    void zonaConMasEntradas();
};

#endif // RBTREE_H