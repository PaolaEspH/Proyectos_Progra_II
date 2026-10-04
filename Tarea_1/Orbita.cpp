#include <iostream>
#include "Orbita.hpp"
#include "Satelite.hpp"

Orbita::Orbita(std::string codigo, std::string nombre, double altitud){
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

void Orbita::mostrar_satelites(){
    int i = 0;
    while(satelites_asignados[i] != nullptr){
        std::cout << "------------------------" << std::endl;
        satelites_asignados[i]->mostrar_satelite();
        i++;
    }
}

int Orbita::numero_satelites_asignados_a_orbita() const{
    int count = 0;
    while((satelites_asignados[count] != nullptr) 
            && (count < MAX_SATELITES)){
        count++;
    }
    return count;
}

void Orbita::mostrar_orbita(){
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Altitud de referencia: " << altitud << " km" << std::endl;
    std::cout << "Satélites asignados: " << numero_satelites_asignados_a_orbita() << std::endl;
}
