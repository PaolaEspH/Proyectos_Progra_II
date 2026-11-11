#include "estacionado.hpp"

Estacionado::Estacionado(Vehiculo vehiculo, int fila, int columna, std::string id_encargado): vehiculo(vehiculo){
    this->fila = fila;
    this->columna = columna;
    this->id_encargado = id_encargado;
}

Vehiculo& Estacionado::get_vehiculo(){
    return vehiculo;
}

std::string Estacionado::get_placa() const{
    return vehiculo.get_placa();
}

int Estacionado::get_tipo() const{
    return vehiculo.get_tipo();
}

int Estacionado::get_fila() const{
    return fila;
}

int Estacionado::get_columna() const{
    return columna;
}

std::string Estacionado::get_id_encargado() const{
    return id_encargado;
}

std::ostream& operator<<(std::ostream& s, const Estacionado& e){
    s << e.vehiculo << "Espacio: (" << e.fila + 1 << "," << e.columna + 1 << ")" <<
    std::endl << "Encargado: " << e.id_encargado <<
    std::endl;
    return s;
}
