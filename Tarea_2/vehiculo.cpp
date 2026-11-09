#include "vehiculo.hpp"

Vehiculo::Vehiculo(std::string placa, std::string propietario, int tipo, int num){
    this->placa = placa;
    this->propietario = propietario;
    this->tipo = tipo;
    this->num = num;
}

int Vehiculo::get_tipo() const{
    return tipo;
}

int Vehiculo::get_num() const{
    return num;
}

std::string Vehiculo::get_placa() const{
    return placa;
}

std::string Vehiculo::get_propietario() const{
    return propietario;
}

std::string Vehiculo::texto_tipo() const{
    switch(tipo){
        case 0:
            return "Automóvil";
        case 1:
            return "Motocicleta";
        default:
            return "Desconocido";
    }
}

std::ostream& operator<<(std::ostream& s, const Vehiculo& v){
    s << "Placa: " << v.placa <<
    std::endl << "Propietario: " << v.propietario <<
    std::endl << "Tipo: " << v.texto_tipo() <<
    std::endl << "Número de solicitud: " << v.num << 
    std::endl;
    return s;
}