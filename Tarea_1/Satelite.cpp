#include <iostream>
#include <cmath>
#include "Satelite.hpp"
#include "Orbita.hpp"

Satelite::Satelite(std::string codigo, std::string nombre, 
    int tipo, double masa, double altitud, 
    double capacidad, double bateria, 
    double potencia, double ancho_banda){
        this->codigo = codigo;
        this->nombre = nombre;
        this->tipo = tipo;
        this->masa = masa;
        this->altitud = altitud;
        this->capacidad = capacidad;
        this->bateria = bateria;
        this->potencia = potencia;
        this->ancho_banda = ancho_banda;
        this->resolucion = 0;
        this->cobertura = 0;
        this->cantidadMuestras = 0;
        this->orbita = nullptr;
}

Satelite::Satelite(std::string codigo, std::string nombre, 
    int tipo, double masa, double altitud, 
    double capacidad, double bateria, 
    double potencia, 
    double resolucion, double cobertura){
        this->codigo = codigo;
        this->nombre = nombre;
        this->tipo = tipo;
        this->masa = masa;
        this->altitud = altitud;
        this->capacidad = capacidad;
        this->bateria = bateria;
        this->potencia = potencia;
        this->ancho_banda = 0;
        this->resolucion = resolucion;
        this->cobertura = cobertura;
        this->cantidadMuestras = 0;
        this->orbita = nullptr;
}

std::string Satelite::get_codigo() const{
    return codigo;
}

std::string Satelite::get_nombre() const{
    return nombre;
}

int Satelite::get_tipo() const{
    return tipo;
}

double Satelite::get_masa() const{
    return masa;
}

double Satelite::get_altitud() const{
    return altitud;
}

double Satelite::get_capacidad() const{
    return capacidad;
}

double Satelite::get_bateria() const{
    return bateria;
}

double Satelite::get_potencia() const{
    return potencia;
}

double Satelite::get_ancho_banda() const{
    return ancho_banda;
}

double Satelite::get_resolucion() const{
    return resolucion;
}

double Satelite::get_cobertura() const{
    return cobertura;
}

Orbita* Satelite::get_orbita() const{
    return orbita;
}

double Satelite::radio_orbital(){
    return RT + altitud;
}

double Satelite::velocidad_orbital(){
    return sqrt(MU/radio_orbital());
}

double Satelite::periodo_orbital(){
    return (2*PI*radio_orbital())/velocidad_orbital();
}

void Satelite::estado_energetico(){
    if(bateria >= 50){
        std::cout << "NORMAL" << std::endl;
    }
    else if(bateria >= 20){
        std::cout << "PRECAUCION" << std::endl;
    }
    else if(bateria > 0){
        std::cout << "CRÍTICO" << std::endl;
    }
    else{
        std::cout << "FUERA DE SERVICIO" << std::endl;
    }
}

void Satelite::mostrar_satelite(){
    std::cout << "Código: " << codigo << std::endl;
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Tipo: " << (tipo == 1 ? "Comunicación" : "Meteorológico") << std::endl;
    std::cout << "Masa: " << masa << " kg" << std::endl;
    std::cout << "Altitud: " << altitud << " km" << std::endl;
    std::cout << "Capacidad energética: " << capacidad << " Wh" << std::endl;
    std::cout << "Batería actual: " << bateria << "%" << std::endl;
    std::cout << "Potencia de transmisión: " << potencia << " W" << std::endl;
    if(tipo == 1){
        std::cout << "Ancho de banda: " << ancho_banda << " MB/s" << std::endl;
    }
    else{
        std::cout << "Resolución del sensor: " << resolucion << " m" << std::endl;
        std::cout << "Cobertura: " << cobertura << "%" << std::endl;
    }
    std::cout << "Velocidad orbital: " << velocidad_orbital() << " km/s" << std::endl;
    std::cout << "Periodo orbital: " << periodo_orbital() << " s ("
              << periodo_orbital()/60 << " min)" << std::endl;
    std::cout << "Estado energético: ";
    estado_energetico();
    std::cout << std::endl;
}

bool Satelite::set_orbita(Orbita* orbita){
    if(this->orbita != nullptr){
        std::cout << "El satélite ya está asignado a la órbita " << this->orbita->get_codigo() << std::endl;
        return false;
    }
    this->orbita = orbita;
    return true;
}