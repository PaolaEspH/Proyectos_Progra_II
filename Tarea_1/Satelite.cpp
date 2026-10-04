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
        for(int i = 0; i < MAX_MUESTRAS; i++){
            this->historialBateria[i] = 0;
            this->historialTemperatura[i] = 0;
        }
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
        for(int i = 0; i < MAX_MUESTRAS; i++){
            this->historialBateria[i] = 0;
            this->historialTemperatura[i] = 0;
        }
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

double Satelite::radio_orbital() const{
    return RT + altitud;
}

double Satelite::velocidad_orbital() const{
    return sqrt(MU/radio_orbital());
}

double Satelite::periodo_orbital() const{
    return (2*PI*radio_orbital())/velocidad_orbital();
}

double Satelite::periodo_orbital_minutos() const{
    return periodo_orbital()/60;
}

std::string Satelite::get_estado() const{
    if(bateria >= 50){
        return "NORMAL";
    }
    else if(bateria >= 20){
        return "PRECAUCIÓN";
    }
    else if(bateria > 0){
        return "CRÍTICO";
    }
    else{
        return "FUERA DE SERVICIO";
    }
}

//Energía que todavía tiene la batería, en Wh
double Satelite::energia_disponible() const{
    return capacidad*(bateria/100);
}

//Fórmula (g): ΔB = (E/C)*100. No deja la batería por debajo de 0%
bool Satelite::reducir_bateria(double energia){
    if(capacidad <= 0){
        return false;
    }
    double reduccion = (energia/capacidad)*100;
    if(reduccion > bateria){
        return false;
    }
    bateria = bateria - reduccion;
    return true;
}

//Listado corto: tipo, altitud, batería y estado
void Satelite::mostrar_resumen() const{
    std::cout << codigo << " | " << nombre
              << " | Tipo: " << (tipo == 1 ? "Comunicación" : "Meteorológico")
              << " | Altitud: " << altitud << " km"
              << " | Batería: " << bateria << "%"
              << " | Estado: " << get_estado() << std::endl;
}

void Satelite::mostrar_satelite() const{
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
              << periodo_orbital_minutos() << " min)" << std::endl;
    std::cout << "Estado energético: " << get_estado() << std::endl;
    if(orbita != nullptr){
        std::cout << "Órbita asignada: " << orbita->get_codigo() << std::endl;
    }
    else{
        std::cout << "Órbita asignada: ninguna" << std::endl;
    }
    std::cout << std::endl;
}

bool Satelite::set_orbita(Orbita* orbita){
    if(orbita == nullptr){
        return false;
    }
    if(this->orbita != nullptr){
        std::cout << "El satélite ya está asignado a la órbita " << this->orbita->get_codigo() << std::endl;
        return false;
    }
    this->orbita = orbita;
    return true;
}