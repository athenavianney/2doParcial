 /*
Name: Pila.cpp
Author: Athena Vianney Núñez Molina
Date: Febrero 4, 2016.
Description:
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#define VACIO 99999

using namespace std;

struct caja{
    int valor;
    caja *siguiente;
};

class pila{
    caja *principio;
    int cuantos;
public:
    pila();
    ~pila();
    void agregar(int);
    void pintar();
    int sacar();
};

int main(){
    pila A;
    A.agregar(10);
    A.agregar(20);
    A.agregar(16);
    A.pintar();
    A.sacar();

    system("pause");
    return 0;
}

pila::pila(){
    principio = NULL;
    cuantos = 0;
}

void pila::agregar(int a){
    caja *p;
    p = (caja*)malloc(sizeof(caja));
    p->valor = a;
    if(!principio){
        p->siguiente = NULL;
        principio = p;
    }else{
        p->siguiente = principio;
        principio = p;
    }
    cuantos++;
}

void pila::pintar(){
    caja *p;
    p = principio;
    while(p){
        cout << p-> valor << endl;
        p = p-> siguiente;
    }
}

pila::~pila(){
    caja *p;
    while(principio){
        p = principio;
        principio = p->siguiente;
        free(p);
    }
    cuantos = 0;
}

int pila::sacar(){
    caja* p;
    int valor;
    if(!principio){
        return VACIO;
    }else{
        p = principio;
        principio = p->siguiente;
        valor = p->valor;
        free(p);
        cuantos--;
        return valor;
    }
}
