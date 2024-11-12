#include <iostream>
#include <malloc.h>

using namespace std;

struct nodo {
    int edad;
    int doc;
    nodo *izq, *der;
};

nodo *raiz = NULL, *aux, *aux2;


int posicionar() {
    if(aux->edad > aux2->edad) {  
        if(aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionar();
        } else {
            aux2->izq = aux;
        }
    } else if(aux->edad < aux2->edad) {
        if(aux2->der != NULL) {
            aux2 = aux2->der;
            posicionar();
        } else {
            aux2->der = aux;
        }
    }
    return 0;
}

int registrar() {
    int edad, doc;
    cout << "INGRESE LA EDAD DEL PACIENTE: ";
    cin >> edad;
    cout << "INGRESE EL DOCUMENTO DEL PACIENTE: ";
    cin >> doc;

    aux = (struct nodo *)malloc(sizeof(struct nodo));
    aux->edad = edad;
    aux->doc = doc;
    aux->izq = aux->der = NULL;

    if(raiz == NULL) {
        raiz = aux;
    } else {
        aux2 = raiz;
        posicionar();
    }
    cout << "PACIENTE REGISTRADO."<<endl;
    return 0;
}


int mostrar(nodo *aux3) {
    if(aux3 == NULL) return 0;
    mostrar(aux3->izq);
    cout << "EDAD: " << aux3->edad << ", DOCUMENTO: " << aux3->doc << endl;
    mostrar(aux3->der);
    return 0;
}


int buscar(nodo *aux3, int doc) {
    if(aux3 == NULL) return 0;
    if(aux3->doc == doc) {
        cout << "PACIENTE ENCONTRADO. EDAD: " << aux3->edad << endl;
        return 1;
    }
    if(buscar(aux3->izq, doc) || buscar(aux3->der, doc)) {
        return 1;
    }
    return 0;
}


int ubicar(nodo *aux3, int doc) {
    if(aux3 == NULL) return 0;
    if(aux3->doc == doc) {
        aux = aux3;
        return 1;
    }
    if(ubicar(aux3->izq, doc) || ubicar(aux3->der, doc)) {
        return 1;
    }
    return 0;
}


int ubicarPadre(nodo *padre) {
    if(padre == NULL || aux == NULL) return 0;
    if((padre->izq == aux) || (padre->der == aux)) {
        aux2 = padre;
        return 1;
    }
    if(ubicarPadre(padre->izq) || ubicarPadre(padre->der)) {
        return 1;
    }
    return 0;
}


int casoUno() {
    if(aux != raiz) ubicarPadre(raiz);
    if(aux2->izq == aux) aux2->izq = NULL;
    else if(aux2->der == aux) aux2->der = NULL;
    else raiz = NULL;
    free(aux);
    aux = NULL;
    return 0;
}

int casoDos() {
    if(aux != raiz) ubicarPadre(raiz);
    aux = (aux->izq !=NULL ) ? aux->izq : aux->der;
    if(aux2->izq == aux) aux2->izq = aux;
    else if(aux2->der == aux) aux2->der = aux;
    else raiz = aux;
    free(aux);
    aux = NULL;
    return 0;
}

int casoTres() {
    aux2 = aux;
   aux = aux->der;
    while(aux->izq != NULL) {
       aux2 = aux;
    aux = aux->izq;
    }
    aux2->edad = aux->edad;
    aux->doc = aux->doc;
    if(aux2->izq==aux) aux2->izq = aux->der;
    else aux2->der = aux->der;
    free(aux);
    aux = NULL;
    return 0;
}


int eliminarPaciente() {
    int doc;
    cout << "DIGITE EL DOCUMENTO DEL PACIENTE A ELIMINAR: ";
    cin >> doc;
    if(!ubicar(raiz, doc)) {
        cout << "PACIENTE NO ENCONTRADO" << endl;
        return 0;
    }
    if(aux->izq == NULL && aux->der == NULL) {
        casoUno();
        cout << "PACIENTE (NODO SIN HIJOS) ELIMINADO" << endl;
    }
    else if((aux->izq == NULL) || (aux->der == NULL)) {
        casoDos();
        cout << "PACIENTE (NODO CON 1 HIJO) ELIMINADO" << endl;
    }
    else {
        casoTres();
        cout << "PACIENTE (NODO CON 2 HIJOS) ELIMINADO" << endl;
    }
    return 0;
}

int main() {
    int opc = 0;
    do {
        cout << "1. REGISTRAR PACIENTE" << endl;
        cout << "2. MOSTRAR PACIENTES (MAYOR A MENOR EDAD)" << endl;
        cout << "3. BUSCAR PACIENTE POR DOCUMENTO" << endl;
        cout << "4. ELIMINAR PACIENTE POR DOCUMENTO" << endl;
        cout << "5. SALIR" << endl;
        cin >> opc;
        switch(opc) {
            case 1: 
                registrar();
                break;
            case 2: 
                cout << "LISTADO DE PACIENTES:" << endl;
                mostrar(raiz); 
                cout << endl; 
                break;
            case 3: {
                int doc;
                cout << "INGRESA EL DOCUMENTO DEL PACIENTE A BUSCAR: ";
                cin >> doc;
                if(!buscar(raiz, doc)) {
                    cout << "EL PACIENTE NO ESTA REGISTRADO" << endl;
                }
                cout << endl;
                break;
            }
            case 4: 
                eliminarPaciente();
                cout << endl;
                break;
        }
    } while(opc != 5);
    return 0;
}
