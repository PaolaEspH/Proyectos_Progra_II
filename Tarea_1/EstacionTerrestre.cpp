#include <iostream>
#include "EstacionTerrestre.hpp"
#include "Satelite.hpp"

EstacionTerrestre::EstacionTerrestre(std::string codigo, std::string nombre, std::string ubicacion){
    this->codigo = codigo;
    this->nombre = nombre;
    this->ubicacion = ubicacion;
    for(int i = 0; i < MAX_SATELITES; i++){
        this->satelites[i] = nullptr;
    }
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

bool EstacionTerrestre::tiene_satelite(Satelite* satelite) const{
    if(satelite == nullptr){
        return false;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] == satelite){
            return true;
        }
    }
    return false;
}

bool EstacionTerrestre::agregar_satelite(Satelite* satelite){
    if(satelite == nullptr){
        std::cout << "Satélite no válido" << std::endl;
        return false;
    }
    if(tiene_satelite(satelite)){
        std::cout << "El satélite ya está enlazado con esta estación" << std::endl;
        return false;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] == nullptr){
            satelites[i] = satelite;
            return true;
        }
    }
    std::cout << "No se puede enlazar, la estación está llena" << std::endl;
    return false;
}

//Deja el arreglo compacto para que los recorridos no se corten en un hueco
bool EstacionTerrestre::eliminar_satelite(Satelite* satelite){
    if(satelite == nullptr){
        return false;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] == satelite){
            for(int j = i; j < MAX_SATELITES - 1; j++){
                satelites[j] = satelites[j+1];
            }
            satelites[MAX_SATELITES-1] = nullptr;
            return true;
        }
    }
    return false;
}

int EstacionTerrestre::numero_satelites_enlazados() const{
    int count = 0;
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] != nullptr){
            count++;
        }
    }
    return count;
}

void EstacionTerrestre::mostrar_satelites(){
    if(numero_satelites_enlazados() == 0){
        std::cout << "   (sin satélites enlazados)" << std::endl;
        return;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] != nullptr){
            std::cout << "   ";
            satelites[i]->mostrar_resumen();
        }
    }
}

void EstacionTerrestre::mostrar_estacion(){
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Ubicación: " << ubicacion << std::endl;
    std::cout << "Satélites enlazados: " << numero_satelites_enlazados() << std::endl;
}
