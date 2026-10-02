#include <iostream>
#include "EstacionTerrestre.hpp"

EstacionTerrestre::EstacionTerrestre(std::string codigo, std::string nombre, std::string ubicacion, Satelite* satelites){
    this->codigo = codigo;
    this->nombre = nombre;
    this->ubicacion = ubicacion;
    this->satelites = satelites;
}

std::string EstacionTerrestre::get_codigo() const{
    return codigo;
}

std::string EstacionTerrestre::get_nombre() const{
    return nombre;
}

std::string EstacionTerrestre::get_ubicacion() const{
    return ubicacion;
}
