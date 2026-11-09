#include "lista_enlazada.hpp"

ListaEnlazada::ListaEnlazada(){
    cabeza = nullptr;
    cola = nullptr;
    solicitudes = 0;
}

void ListaEnlazada::registrar(std::string placa, std::string propietario, int tipo){
    if(buscar(placa)){
        std::cout << "La placa ya se encuentra registrada" << std::endl;
        return;
    }
    Nodo* nuevo = new Nodo(Vehiculo(placa, propietario, tipo, solicitudes));
    solicitudes++;
    if(cabeza == nullptr){
        cabeza = nuevo;
        cola = nuevo;
        return;
    }
    cola->set_siguiente(nuevo);
    cola = cola->get_siguiente();
}

ListaEnlazada::IteradorEspera::IteradorEspera(Nodo* posicion){
    posactual = posicion;
}

ListaEnlazada::IteradorEspera& ListaEnlazada::IteradorEspera::operator++(){
    if(posactual != nullptr){
        posactual = posactual->get_siguiente();
    }
    return *this;
}

bool ListaEnlazada::IteradorEspera::operator!=(const IteradorEspera& otro){
    return posactual != otro.posactual;
}

bool ListaEnlazada::IteradorEspera::operator==(const IteradorEspera& otro){
    return posactual == otro.posactual;
}

Vehiculo* ListaEnlazada::IteradorEspera::operator->(){
    return &(posactual->get_dato());
}

Vehiculo& ListaEnlazada::IteradorEspera::operator*(){
    return posactual->get_dato();
}

Nodo* ListaEnlazada::IteradorEspera::get_nodo() const{
    return posactual;
}

ListaEnlazada::IteradorEspera ListaEnlazada::begin(){
    return IteradorEspera(cabeza);
}

ListaEnlazada::IteradorEspera ListaEnlazada::end(){
    return IteradorEspera(nullptr);
}

void ListaEnlazada::mostrar(){
    int i = 0;
    for(IteradorEspera it = begin(); it != end(); ++it, i++){
        std::cout << *it << "--------------------------------" << std::endl;
    }
    std::cout << "Total de solicitudes pendientes: " << i << std::endl;
}

void ListaEnlazada::consultar(std::string placa){
    Nodo* vehiculo = buscar(placa);
    if(vehiculo){
        std::cout << *vehiculo;
    }
    else{
        std::cout << "Vehículo no encontrado" << std::endl;
    }
}

Nodo* ListaEnlazada::buscar(std::string placa){
    for(IteradorEspera it = begin(); it != end(); ++it){
        if((it)->get_placa() == placa){
            return it.get_nodo();
        };
    }
    return nullptr;
}

void ListaEnlazada::cancelar(std::string placa){
    Nodo* anterior = nullptr;
    IteradorEspera b = begin();
    ++b;
    for(IteradorEspera it = begin(); it != end(); ++it, ++b){
        if(it->get_placa() == placa){
            Nodo* eliminar = it.get_nodo();
            if(anterior == nullptr){
                cabeza = cabeza->get_siguiente();
            }
            else{
                anterior->set_siguiente(b.get_nodo());
            }
            if(b == end()){
                cola = anterior;
            }
            delete eliminar;
            return;
        }
        anterior = it.get_nodo();
    }
}

int ListaEnlazada::pendientes(){
    int c = 0;
    for(IteradorEspera it = begin(); it != end(); ++it){
        c++;
    }
    return c;
}

int ListaEnlazada::cantidad(int tipo){
    int c = 0;
    for(IteradorEspera it = begin(); it != end(); ++it){
        if(it->get_tipo() == tipo){
            c++;
        };
    }
    return c;
}