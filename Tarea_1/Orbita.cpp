#include <iostream>
#include "Orbita.hpp"

Orbita::Orbita(std::string codigo){
    this->codigo = codigo;
    this->nombre = nombre;
    this->altitud = altitud;
    for(int i = 0; i < MAX_SATELITES; i++){
        this->satelites_asignados[i] = nullptr;
    }
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

void Orbita::asignar_satelite(Satelite* satelite){
    if(satelite == nullptr){
        std::cout << "Satélite no válido" << std::endl;
        return;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites_asignados[i] == nullptr){
            satelites_asignados[i] = satelite;
            return;
        }
    }
    std::cout << "No se puede asignar el satélite, la órbita está llena" << std::endl;
}

Satelite* Orbita::get_satelites_asignados() const{
    return satelites_asignados;
}

int Orbita::numero_satelites_asignados_a_orbita() const{
    int count = 0;
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites_asignados[i] != nullptr){
            count++;
        }
    }
    return count;
}