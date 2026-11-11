#include "nodo_doble.hpp"

NodoDoble::NodoDoble(Estacionado dato): dato(dato), siguiente(nullptr), anterior(nullptr) {}

NodoDoble* NodoDoble::get_siguiente() const{
    return siguiente;
}

NodoDoble* NodoDoble::get_anterior() const{
    return anterior;
}

Estacionado& NodoDoble::get_dato(){
    return dato;
}

void NodoDoble::set_siguiente(NodoDoble* sig){
    siguiente = sig;
}

void NodoDoble::set_anterior(NodoDoble* ant){
    anterior = ant;
}

std::ostream& operator<<(std::ostream& s, const NodoDoble& nodo){
    s << nodo.dato;
    return s;
}
