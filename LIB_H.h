// Project description:librería 
///listas encadenadas 
///convertirlas a Poo
///usar herencia🧬 
///formar pilas y colas
#ifndef LIB_H
#define LIB_H
#include <iostream>

using namespace std;    
// NODO 
class Nodo {
public:
    int dato;
    Nodo* siguiente;

    Nodo(int val) : dato(val), siguiente(nullptr) {}
    virtual ~Nodo() {}
};

// ================== LISTA BASE ==================
class Lista {
protected:
    Nodo* cabeza;

public:
    Lista() : cabeza(nullptr) {}
    virtual ~Lista() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    virtual void insertar(int val) {
        Nodo* nuevo = new Nodo(val);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    }

    virtual void mostrar() const {
        Nodo* actual = cabeza;
        while (actual) {
            std::cout << actual->dato << " -> ";
            actual = actual->siguiente;
        }
        std::cout << "NULL" << std::endl;
    }

    virtual bool buscar(int val) const {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->dato == val) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    bool estaVacia() const {
        return cabeza == nullptr;
    }
};

// ================== PILA (STACK) ==================
class Pila : public Lista {
public:
    Pila() : Lista() {}
    ~Pila() {}

    void push(int val) {
        insertar(val); // Inserta al inicio
    }

    int pop() {
        if (estaVacia()) {
            std::cerr << "Pila vacía" << std::endl;
            return -1;
        }
        Nodo* temp = cabeza;
        int valor = cabeza->dato;
        cabeza = cabeza->siguiente;
        delete temp;
        return valor;
    }

    int cima() const {
        if (estaVacia()) {
            std::cerr << "Pila vacía" << std::endl;
            return -1;
        }
        return cabeza->dato;
    }
};

// ================== COLA (QUEUE) ==================
class Cola : public Lista {
private:
    Nodo* cola; // apuntador al final

public:
    Cola() : Lista(), cola(nullptr) {}

    ~Cola() {}

    void enqueue(int val) {
        Nodo* nuevo = new Nodo(val);
        if (estaVacia()) {
            cabeza = cola = nuevo;
        } else {
            cola->siguiente = nuevo;
            cola = nuevo;
        }
    }

    int dequeue() {
        if (estaVacia()) {
            std::cerr << "Cola vacía" << std::endl;
            return -1;
        }
        Nodo* temp = cabeza;
        int valor = cabeza->dato;
        cabeza = cabeza->siguiente;
        if (cabeza == nullptr) {
            cola = nullptr;
        }
        delete temp;
        return valor;
    }

    int frente() const {
        if (estaVacia()) {
            std::cerr << "Cola vacía" << std::endl;
            return -1;
        }
        return cabeza->dato;
    }
};


#endif // LIB_H

