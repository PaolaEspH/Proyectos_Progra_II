#include <iostream>
#include "Orbita.hpp"

Orbita::Orbita(std::string codigo, std::string nombre, double altitud, Satelite* satelites){
    this->codigo = codigo;
    this->nombre = nombre;
    this->altitud = altitud;
    this->arr = satelites;
}

std::string Orbita::get_codigo() const{
    return codigo;
}

std::string Orbita::get_nombre() const{
    return nombre;
}

double Orbita::get_altitud() const{
    return altitud;
}
