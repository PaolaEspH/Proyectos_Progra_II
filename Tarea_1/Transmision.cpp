#include <iostream>
#include "Transmision.hpp"

Transmision::Transmision(double ancho_banda, double potencia, double duracion, double energia, double tiempo){
    this->ancho_banda = ancho_banda;
    this->potencia = potencia;
    this->duracion = duracion;
    this->energia = energia;
    this->tiempo = tiempo;
}
