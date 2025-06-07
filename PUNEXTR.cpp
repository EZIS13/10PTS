
//1 clase listas encadenadas y nodo 
//2 verdad para hacer pilas y colas 
//3 usando métodos push y pop hacer el juego hanoi usando sus mismas clases
#include <iostream>
#include "LIB_H.h"

using namespace std;

//MOSTRAR LAS TORRES🖼️
void mostrar_to(Pila& torreA, Pila& torreB, Pila& torreC,int numdiscos) {
    Pila Apmo, Bpmo, Cpmo; //🗂️Pilas auxiliares para mostrar
    int aregloA[100] = {0}, aregloB[100] = {0}, aregloC[100] = {0};

    // Llenar las pilas auxiliares con los discos de cada torre
//Torre A
    int indice = numdiscos - 1;
    while (!torreA.estaVacia()){
        aregloA[indice--]= torreA.pop();
        Apmo.push(aregloA[indice + 1]); 
    }
    while (!Apmo.estaVacia())torreA.push(Apmo.pop());
//Torre B
    indice =numdiscos-1;
    while (!torreB.estaVacia()){
        aregloB[indice--]= torreB.pop();
        Bpmo.push(aregloB[indice + 1]); 
    }
    while (!Bpmo.estaVacia())torreB.push(Bpmo.pop());
//Torre C
    indice =numdiscos-1;
    while (!torreC.estaVacia()){
        aregloC[indice--]= torreC.pop();
        Cpmo.push(aregloC[indice + 1]); 
    }
    while (!Cpmo.estaVacia())torreC.push(Cpmo.pop());
    cout << "\n\n";
    cout<< "      .: Torre A :.       .: Torre B :.       .: Torre C :.\n";
//🔍VER NIVELES
    for (int nivel =0; nivel <numdiscos; nivel++){

        //TORRE A
        if(aregloA[nivel]!=0)
            cout<< "            (" << string(aregloA[nivel], '#') << ")";
        else
            cout<< "             |";
        //TORRE B
        if(aregloB[nivel]!=0)
            cout<< "            (" << string(aregloB[nivel], '#') << ")";
        else
            cout<< "             |";   
        //TORRE C
        if(aregloC[nivel]!=0)
            cout<< "            (" << string(aregloC[nivel], '#') << ")";
        else
            cout<<"             |";
            
        cout << "\n";
    }
//🔍VER BASE
    cout << "     -----------      -------------     ------------ \n";    

}
int main(){
    Pila torreA, torreB, torreC;///🏗️ Crear tres torres
    int numdiscos;
    cout<<"🎮JUEGO DE LAS TORRES DE HANOI\n";
    cout<<"Ingrese el numero de discos ";
    cin>>numdiscos;
    //🔍 Validar el número de discos
    if (numdiscos<=0){
        cout<<"numero de discos no valido, debe ser mayor a 0\n";
        return 1;
    }
    // EMPEZAR AÑADIR DISCOS A LA TORRE A
    for(int i = numdiscos; i > 0; i--) {
        torreA.push(i); // Añadir discos a la torre A
    }
    int MOVR = 0; // Contador de movimientos
    while (true){
        mostrar_to(torreA, torreB, torreC, numdiscos);
        cout<<"MOVIMIENTO N°"<<MOVR+1<<endl;
        cout<<"Ingrese la torre de origen (A, B, C): ";
        char origenChar, destinoChar;
        cin >> origenChar >> destinoChar;

        // 🔠 Convertir a mayúsculas
        origenChar = (origenChar >= 'a' && origenChar <= 'z') ? origenChar - 32 : origenChar;
        destinoChar = (destinoChar >= 'a' && destinoChar <= 'z') ? destinoChar - 32 : destinoChar;

        Pila* origen = nullptr;
        Pila* destino = nullptr;

        if (origenChar == 'A') origen = &torreA;
        else if (origenChar == 'B') origen = &torreB;
        else if (origenChar == 'C') origen = &torreC;

        if (destinoChar == 'A') destino = &torreA;
        else if (destinoChar == 'B') destino = &torreB;
        else if (destinoChar == 'C') destino = &torreC;

        if (!origen || !destino) {
            cout << "❌ Torres inválidas. Usa A, B o C.\n";
            continue;
        }

        if (origen->estaVacia()) {
            cout << "❌ Torre origen vacía.\n";
            continue;
        }

        int disco = origen->pop();
        if (!destino->estaVacia() && destino->cima() < disco) {
            origen->push(disco); // ❗ Deshacer movimiento inválido
            cout << "❌ Movimiento inválido. No se puede colocar un disco grande sobre uno pequeño.\n";
            continue;
        }

        destino->push(disco);
        MOVR++; // Incrementar el contador de movimientos
        // ✅ Verificar si ya ganaste 🎉
        Pila temp;
        int contador = 0;
        while (!torreC.estaVacia()) {
            temp.push(torreC.pop());
            contador++;
        }
        while (!temp.estaVacia()) torreC.push(temp.pop());

        if (contador == numdiscos) {
            mostrar_to(torreA, torreB, torreC, numdiscos);
            cout << "\n🎉 ¡Felicidades! Completaste el juego en " << MOVR<< " movimientos.\n";
            break;
        }
    }

    return 0;
}