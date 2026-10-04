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

bool Orbita::asignar_satelite(Satelite* satelite){
    if(satelite == nullptr){
        std::cout << "Satélite no válido" << std::endl;
        return false;
    }
    if(tiene_satelite(satelite)){
        std::cout << "El satélite ya pertenece a esta órbita" << std::endl;
        return false;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites_asignados[i] == nullptr){
            satelites_asignados[i] = satelite;
            return true;
        }
    }
    std::cout << "No se puede asignar el satélite, la órbita está llena" << std::endl;
    return false;
}

void Orbita::mostrar_satelites(){
    if(numero_satelites_asignados_a_orbita() == 0){
        std::cout << "   (sin satélites asignados)" << std::endl;
        return;
    }
    int i = 0;
    while((i < MAX_SATELITES) && (satelites_asignados[i] != nullptr)){
        std::cout << "------------------------" << std::endl;
        satelites_asignados[i]->mostrar_satelite();
        i++;
    }
}

int Orbita::numero_satelites_asignados_a_orbita() const{
    int count = 0;
    while((count < MAX_SATELITES)
            && (satelites_asignados[count] != nullptr)){
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

bool Orbita::tiene_satelite(Satelite* satelite) const{
    if(satelite == nullptr){
        return false;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites_asignados[i] == satelite){
            return true;
        }
    }
    return false;
}
