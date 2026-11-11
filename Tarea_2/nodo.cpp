#include "nodo.hpp"

Nodo::Nodo(Vehiculo dato): dato(dato), siguiente(nullptr) {}

Nodo* Nodo::get_siguiente() const{
    return siguiente;
}

Vehiculo& Nodo::get_dato(){
    return dato;
}

void Nodo::set_siguiente(Nodo* sig){
    siguiente = sig;
}

std::ostream& operator<<(std::ostream& s, const Nodo& nodo){
    s << nodo.dato;
    return s;
}
