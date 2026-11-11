#include "lista_enlazada.hpp"

ListaEnlazada::ListaEnlazada(){
    cabeza = nullptr;
    cola = nullptr;
    solicitudes = 0;
}

ListaEnlazada::~ListaEnlazada(){
    Nodo* actual = cabeza;
    while(actual != nullptr){
        Nodo* sig = actual->get_siguiente();
        delete actual;
        actual = sig;
    }
}

void ListaEnlazada::registrar(std::string placa, std::string propietario, int tipo){
    if(placa.empty() || propietario.empty()){
        throw std::invalid_argument("La placa y el propietario no pueden estar vacíos.");
    }
    if(tipo != 0 && tipo != 1){
        throw std::invalid_argument("El tipo de vehículo no es válido.");
    }
    if(buscar(placa)){
        throw std::logic_error("La placa ya está registrada.");
    }
    solicitudes++; // La primera solicitud es la 1
    Nodo* nuevo = new Nodo(Vehiculo(placa, propietario, tipo, solicitudes));
    if(cabeza == nullptr){
        cabeza = nuevo;
        cola = nuevo;
        return;
    }
    cola->set_siguiente(nuevo);
    cola = cola->get_siguiente();
}

// Consulta la primera solicitud sin retirarla
Vehiculo& ListaEnlazada::primera(){
    if(cabeza == nullptr){
        throw std::underflow_error("No hay solicitudes pendientes.");
    }
    return cabeza->get_dato();
}

// Retira la primera solicitud (el Sistema la llama solo cuando el ingreso ya se completó)
void ListaEnlazada::procesar(){
    if(cabeza == nullptr){
        throw std::underflow_error("No hay solicitudes pendientes.");
    }
    Nodo* eliminar = cabeza;
    cabeza = cabeza->get_siguiente();
    if(cabeza == nullptr){
        cola = nullptr;
    }
    delete eliminar;
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
    if(begin() == end()){
        std::cout << "No existen solicitudes pendientes." << std::endl;
        return;
    }
    int i = 0;
    for(IteradorEspera it = begin(); it != end(); ++it, i++){
        std::cout << *it << "--------------------------------" << std::endl;
    }
    std::cout << "Total de solicitudes pendientes: " << i << std::endl;
}

void ListaEnlazada::consultar(std::string placa){
    Vehiculo* vehiculo = buscar(placa);
    if(vehiculo == nullptr){
        throw std::out_of_range("Solicitud no encontrada.");
    }
    std::cout << *vehiculo;
}

Vehiculo* ListaEnlazada::buscar(std::string placa){
    for(IteradorEspera it = begin(); it != end(); ++it){
        if(it->get_placa() == placa){
            return &(*it);
        }
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
    throw std::out_of_range("Solicitud no encontrada.");
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
        }
    }
    return c;
}
