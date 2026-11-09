#include "nodo.hpp"

Nodo::Nodo(Vehiculo dato): dato(dato), siguiente(nullptr), anterior(nullptr), id_encargado(""), fila(-1), columna(-1) {}

Nodo* Nodo::get_siguiente() const{
    return siguiente;
}

Nodo* Nodo::get_anterior() const{
    return anterior;
}

Vehiculo& Nodo::get_dato(){
    return dato;
}

void Nodo::set_siguiente(Nodo* sig){
    siguiente = sig;
}

void Nodo::set_anterior(Nodo* ant){
    anterior = ant;
}

std::ostream& operator<<(std::ostream& s, const Nodo& nodo){
    s << nodo.dato;
    return s;
}