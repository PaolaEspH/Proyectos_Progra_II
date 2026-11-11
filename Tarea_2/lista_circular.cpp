#include "lista_circular.hpp"

using namespace std;

NodoEncargado::NodoEncargado(Encargado dato) : dato(dato), siguiente(nullptr) {}

NodoEncargado* NodoEncargado::get_siguiente() const {
    return siguiente;
}

Encargado& NodoEncargado::get_dato() {
    return dato;
}

void NodoEncargado::set_siguiente(NodoEncargado* sig) {
    siguiente = sig;
}

ListaCircular::ListaCircular() : cabeza(nullptr), cola(nullptr), turno(nullptr), cantidad(0) {}

ListaCircular::~ListaCircular() {
    if (cola != nullptr) {
        cola->set_siguiente(nullptr); // se abre el círculo para borrar hasta llegar a nullptr
    }
    NodoEncargado* actual = cabeza;
    while (actual != nullptr) {
        NodoEncargado* aEliminar = actual;
        actual = actual->get_siguiente();
        delete aEliminar;
    }
}

void ListaCircular::registrar(string id, string nombre) {
    if (buscar(id) != nullptr) {
        throw logic_error("El ID del encargado ya está registrado.");
    }

    NodoEncargado* nuevo = new NodoEncargado(Encargado(id, nombre));
    if (vacia()) {
        cabeza = nuevo;
        turno = nuevo;
    } else {
        cola->set_siguiente(nuevo);
    }
    nuevo->set_siguiente(cabeza);
    cola = nuevo;
    cantidad++;
}

void ListaCircular::eliminar(string id) {
    NodoEncargado* anterior = cola;
    NodoEncargado* actual = cabeza;

    for (int i = 0; i < cantidad; i++) {
        if (actual->get_dato().get_id() == id) {
            if (cantidad == 1) {
                cabeza = nullptr;
                cola = nullptr;
                turno = nullptr;
            } else {
                NodoEncargado* siguiente = actual->get_siguiente();
                anterior->set_siguiente(siguiente);
                if (actual == cabeza) {
                    cabeza = siguiente;
                }
                if (actual == cola) {
                    cola = anterior;
                }
                if (actual == turno) {
                    turno = siguiente;
                }
            }
            delete actual;
            cantidad--;
            return;
        }
        anterior = actual;
        actual = actual->get_siguiente();
    }
    throw out_of_range("Encargado no encontrado.");
}

Encargado& ListaCircular::siguiente() {
    if (vacia()) {
        throw logic_error("No existen encargados disponibles.");
    }
    return turno->get_dato();
}

string ListaCircular::asignar() {
    Encargado& encargado = siguiente();
    string id = encargado.get_id();
    encargado.atender();
    return id;
}

void ListaCircular::avanzar() {
    if (vacia()) {
        throw logic_error("No existen encargados disponibles.");
    }
    turno = turno->get_siguiente();
}

bool ListaCircular::vacia() const {
    return cabeza == nullptr;
}

int ListaCircular::get_cantidad() const {
    return cantidad;
}
