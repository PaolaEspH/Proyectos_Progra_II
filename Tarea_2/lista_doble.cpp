#include "lista_doble.hpp"

ListaDoble::ListaDoble(){
    cabeza = nullptr;
    cola = nullptr;
}

ListaDoble::~ListaDoble(){
    NodoDoble* actual = cabeza;
    while(actual != nullptr){
        NodoDoble* sig = actual->get_siguiente();
        delete actual;
        actual = sig;
    }
}

void ListaDoble::registrar(Estacionado nuevo){
    if(buscar(nuevo.get_placa()) != nullptr){
        throw std::logic_error("La placa ya está registrada.");
    }
    NodoDoble* nodo = new NodoDoble(nuevo);
    nodo->set_anterior(cola);
    if(cabeza == nullptr){
        cabeza = nodo;
    }
    else{
        cola->set_siguiente(nodo);
    }
    cola = nodo;
}

ListaDoble::IteradorEstacionamiento::IteradorEstacionamiento(NodoDoble* posicion){
    posactual = posicion;
}

ListaDoble::IteradorEstacionamiento& ListaDoble::IteradorEstacionamiento::operator++(){
    if(posactual != nullptr){ //Deja nullptr si es nullptr
        posactual = posactual->get_siguiente();
    }
    return *this;
}

ListaDoble::IteradorEstacionamiento& ListaDoble::IteradorEstacionamiento::operator--(){
    if(posactual != nullptr){
        posactual = posactual->get_anterior();
    }
    return *this;
}

bool ListaDoble::IteradorEstacionamiento::operator!=(const IteradorEstacionamiento& otro){
    return posactual != otro.posactual;
}

bool ListaDoble::IteradorEstacionamiento::operator==(const IteradorEstacionamiento& otro){
    return posactual == otro.posactual;
}

Estacionado* ListaDoble::IteradorEstacionamiento::operator->(){
    return &(posactual->get_dato());
}

Estacionado& ListaDoble::IteradorEstacionamiento::operator*(){
    return posactual->get_dato();
}

NodoDoble* ListaDoble::IteradorEstacionamiento::get_nodo() const{
    return posactual;
}

ListaDoble::IteradorEstacionamiento ListaDoble::begin(){
    return IteradorEstacionamiento(cabeza);
}

ListaDoble::IteradorEstacionamiento ListaDoble::end(){
    return IteradorEstacionamiento(nullptr);
}

// Recorrido inverso: empieza en la cola y termina al pasar antes de la cabeza
ListaDoble::IteradorEstacionamiento ListaDoble::rbegin(){
    return IteradorEstacionamiento(cola);
}

ListaDoble::IteradorEstacionamiento ListaDoble::rend(){
    return IteradorEstacionamiento(nullptr);
}

void ListaDoble::mostrar(){
    int i = 0;
    for(IteradorEstacionamiento it = begin(); it != end(); ++it, i++){
        std::cout << *it << "--------------------------------" << std::endl;
    }
    std::cout << "Total de vehículos estacionados: " << i << std::endl;
}

void ListaDoble::mostrar_inverso(){
    int i = 0;
    for(IteradorEstacionamiento it = rbegin(); it != rend(); --it, i++){
        std::cout << *it << "--------------------------------" << std::endl;
    }
    std::cout << "Total de vehículos estacionados: " << i << std::endl;
}

void ListaDoble::consultar(std::string placa){
    Estacionado* vehiculo = buscar(placa);
    if(vehiculo == nullptr){
        throw std::out_of_range("Vehículo no encontrado.");
    }
    std::cout << *vehiculo;
}

NodoDoble* ListaDoble::buscar_nodo(std::string placa){
    for(IteradorEstacionamiento it = begin(); it != end(); ++it){
        if(it->get_placa() == placa){
            return it.get_nodo();
        }
    }
    return nullptr;
}

Estacionado* ListaDoble::buscar(std::string placa){
    NodoDoble* nodo = buscar_nodo(placa);
    if(nodo == nullptr){
        return nullptr;
    }
    return &(nodo->get_dato());
}

void ListaDoble::abandonar(std::string placa){
    NodoDoble* eliminar = buscar_nodo(placa);
    if(eliminar == nullptr){
        throw std::out_of_range("Vehículo no encontrado.");
    }
    NodoDoble* ant = eliminar->get_anterior();
    NodoDoble* sig = eliminar->get_siguiente();
    if(ant == nullptr){ // Era la cabeza
        cabeza = sig;
    }
    else{
        ant->set_siguiente(sig);
    }
    if(sig == nullptr){ // Era la cola
        cola = ant;
    }
    else{
        sig->set_anterior(ant);
    }
    delete eliminar;
}

int ListaDoble::estacionados(){
    int c = 0;
    for(IteradorEstacionamiento it = begin(); it != end(); ++it){
        c++;
    }
    return c;
}

int ListaDoble::cantidad(int tipo){
    int c = 0;
    for(IteradorEstacionamiento it = begin(); it != end(); ++it){
        if(it->get_tipo() == tipo){
            c++;
        }
    }
    return c;
}
