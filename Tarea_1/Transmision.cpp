#include <iostream>
#include "Transmision.hpp"
#include "Satelite.hpp"
#include "EstacionTerrestre.hpp"

Transmision::Transmision(Satelite* sateliteAsignado, EstacionTerrestre* estacionDestino,
                         double datos, double ancho_banda, double potencia){
    this->sateliteAsignado = sateliteAsignado;
    this->estacionDestino = estacionDestino;
    this->datos = datos;
    this->ancho_banda = ancho_banda;
    this->potencia = potencia;
    //Distancia aproximada satélite-estación: la altitud del satélite
    if(sateliteAsignado != nullptr){
        this->distancia = sateliteAsignado->get_altitud();
    }
    else{
        this->distancia = 0;
    }
    this->duracion = duracion_transmision();
    this->energia = energia_consumida();
    this->tiempo = tiempo_propagacion();
}

//Fórmula (e): t_tx = D / B
double Transmision::duracion_transmision(){
    if(ancho_banda <= 0){
        return 0;
    }
    return datos/ancho_banda;
}

//Fórmula (f): E = P * (t_tx / 3600)
double Transmision::energia_consumida(){
    return potencia*(duracion/3600);
}

//Fórmula (d): t_p = d / c
double Transmision::tiempo_propagacion(){
    return distancia/C_LUZ;
}

Satelite* Transmision::get_satelite() const{
    return sateliteAsignado;
}

EstacionTerrestre* Transmision::get_estacion() const{
    return estacionDestino;
}

double Transmision::get_datos() const{
    return datos;
}

double Transmision::get_ancho_banda() const{
    return ancho_banda;
}

double Transmision::get_potencia() const{
    return potencia;
}

double Transmision::get_duracion() const{
    return duracion;
}

double Transmision::get_energia() const{
    return energia;
}

double Transmision::get_tiempo() const{
    return tiempo;
}

void Transmision::mostrar_transmision(){
    if((sateliteAsignado == nullptr) || (estacionDestino == nullptr)){
        std::cout << "Transmision incompleta" << std::endl;
        return;
    }
    std::cout << "Satelite: " << sateliteAsignado->get_codigo()
              << " -> Estacion: " << estacionDestino->get_codigo() << std::endl;
    std::cout << "Datos transmitidos: " << datos << " MB" << std::endl;
    std::cout << "Ancho de banda: " << ancho_banda << " MB/s" << std::endl;
    std::cout << "Potencia utilizada: " << potencia << " W" << std::endl;
    std::cout << "Duracion: " << duracion << " s" << std::endl;
    std::cout << "Tiempo de propagacion: " << tiempo << " s" << std::endl;
    std::cout << "Energia consumida: " << energia << " Wh" << std::endl;
}
