 /*
Name: Cola.cpp
Author: Athena Vianney Núñez Molina
Date: Febrero 4, 2016
Description:
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#define VACIO 999999

using namespace std;

struct caja{
    int valor;
    caja *siguiente;
};

class cola{
    int cuantos;
    caja *principio, *finalito;
public:
    cola();
    ~cola();
    void agregar(int);
    void pintar();
    int sacar();
    int cuanto();
};

int main(){
    cola A;
    A.agregar(10);
    A.agregar(20);
    A.agregar(16);
    A.pintar();
    A.sacar();

    system("pause");
    return 0;
}

cola::cola(){
    cuantos = 0;
    principio = NULL;
    finalito = NULL;
}

void cola::agregar(int a){
    caja *p;
    p = (caja*)malloc(sizeof(caja));
    p->valor = a;
    if(!principio){
        p->siguiente = NULL;
        principio = p;
        finalito = p;
    }else{
        p->siguiente = NULL;
        finalito->siguiente = p;
        finalito = p;
    }
    cuantos++;
}

cola::~cola(){
    caja *p;
    while(principio){
        p = principio;
        principio = p->siguiente;
        free(p);
    }
    finalito = NULL;
    cuantos = 0;
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



