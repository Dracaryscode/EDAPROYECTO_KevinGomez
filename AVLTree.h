#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>

struct Acceso {
    std::string id;
    std::string zona;
    int hora;
};

struct AVLNode {
    Acceso acceso;
    int altura;
    AVLNode* izq;
    AVLNode* der;

    AVLNode(const Acceso& nuevoAcceso);
};

class AVLTree {
private:
    AVLNode* raiz;

    int maximo(int a, int b);
    int obtenerAltura(AVLNode* nodo);
    int obtenerBalance(AVLNode* nodo);
    AVLNode* rotarDerecha(AVLNode* y);
    AVLNode* rotarIzquierda(AVLNode* x);
    AVLNode* insertarNodo(AVLNode* nodo, const Acceso& nuevoAcceso);
    void recorridoInorden(AVLNode* nodo, std::vector<Acceso>& accesos);
    void consultaFranjaHoraria(AVLNode* nodo, int h1, int h2, std::vector<Acceso>& resultado);
    void contarZonas(AVLNode* nodo, int* zonas, std::string* nombresZonas, int& totalZonas);

public:
    AVLTree();

    void insertar(const Acceso& nuevoAcceso);
    void mostrarInorden();
    void consultaPorFranja(int h1, int h2);
    void zonaConMasEntradas();
    std::vector<Acceso> obtenerAccesosEnOrden();
    void mostrarAccesos(const std::vector<Acceso>& accesos);
};

#endif // AVLTREE_H
