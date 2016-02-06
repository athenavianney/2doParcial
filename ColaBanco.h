#ifndef COLABANCO_H_INCLUDED
#define COLABANCO_H_INCLUDED

 /*
Name: Cola.cpp
Author: Athena Vianney N��ez Molina
Date: Febrero 4, 2016
Description:
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct caja{
    int valor, llegada, cajera;
    caja *siguiente;
};

class cola{
    int clientes;
    caja *principio, *finalito;
public:
    cola();
    ~cola();
    void agregar(int, int);
    void pintar();
    int sacar();
    int numClientes();
};

int main(){
    

    system("pause");
    return 0;
}

cola::cola(){
    clientes = 0;
    principio = NULL;
    finalito = NULL;
}

void cola::agregar(int llegada, int cajera){
    caja *p;
    p = (caja*)malloc(sizeof(caja));
    p->llegada = llegada;
    p->cajera = cajera;
    if(!principio){
        p->siguiente = NULL;
        principio = p;
        finalito = p;
    }else{
        p->siguiente = NULL;
        finalito->siguiente = p;
        finalito = p;
    }
    clientes++;
}

cola::~cola(){
    caja *p;
    while(principio){
        p = principio;
        principio = p->siguiente;
        free(p);
    }
    finalito = NULL;
    clientes = 0;
}

void cola::pintar(){
    caja *p;
    p = principio;
    while(p){
        cout << p-> valor << endl;
        p = p-> siguiente;
    }
}

int cola::sacar(){
    caja *p;
    int valor;
    if(!principio){
        return VACIO;
    }else{
        p = principio;
        principio = p->siguiente;
        valor = p->valor;
        free(p);
        cuantos--;
        if(cuantos==0){
            finalito = NULL;
        }
        return valor;
    }
}

int cola::cuanto(){
    return cuantos;
}

#endif // COLABANCO_H_INCLUDED
