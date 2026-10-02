#include <iostream>
#include <cmath>
#include "tarea1.hpp"

CentroControl::CentroControl(){
}

//Todavía no sé a qué clase pertenecen, diría satélite
double radio_orbital(){
    return RT + altura;
}

double velocidad_orbital(){
    return sqrt(mu/radio_orbital());
}

double periodo_orbital(){
    return (2*PI*radio_orbital())/velocidad_orbital();
}

double tiempo_propagacion(){ //No sé qué distancia es
    return distancia/c;
}

double duracion_transmision(int datos){
    return datos/ancho_banda;
}

double energia_consumida(int datos){
    return potencia*(duracion_transmision(datos)/3600);
}

double reduccion_bateria(int datos){
    (energia_consumida(datos)/capacidad)*100
}

double recarga_solar(double eta){ //No sé qué es t
    if ((eta > 1) || (eta < 0)){
        return -1;
    }
    double resultado = potencia*(t/3600)*eta;
    if (resultado > 100){
        return 100;
    }
    return resultado;
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