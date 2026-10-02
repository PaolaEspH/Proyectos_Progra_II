#include <iostream>
#include <cmath>
#include <limits>
#include "CentroControl.hpp"

CentroControl::CentroControl(){
    for(int i = 0; i < MAX_SATELITES; i++){
        satelites[i] = nullptr;
    }
    for(int i = 0; i < MAX_ORBITAS; i++){
        orbitas[i] = nullptr;
    }
    for(int i = 0; i < MAX_ESTACIONES; i++){
        estaciones[i] = nullptr;
    }
    for(int i = 0; i < MAX_TRANSMISIONES; i++){
        transmisiones[i] = nullptr;
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        for(int j = 0; j < MAX_ESTACIONES; j++){
            enlaces[i][j] = false;
        }
    }
}

void CentroControl::registrar_satelite(){
    std::string cod;
    std::string nombre;
    int tipo;
    double masa;
    double altitud;
    double capacidad;
    double bateria;
    double potencia;
    if (numero_satelites() >= MAX_SATELITES){
        std::cout << "No se pueden registrar más satélites" << std::endl;
        return;
    }
    cod = verificar_codigo_satelite();
    std::cout << "Nombre: ";
    std::cin >> nombre;
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Tipo (1. Comunicación / 2. Meteorológico): ";
    } while(!(std::cin >> tipo) || ((tipo != 1) && (tipo != 2)));
    masa = leer_double("Masa (kg)");
    altitud = leer_double("Altitud (km)");
    capacidad = leer_double("Capacidad energética (Wh)");
    bateria = leer_double_min_max("Bateria actual (%)", 0, 100);
    potencia = leer_double("Potencia de transmision (W)");

    if(tipo == 1){
        double ancho_banda;
        ancho_banda = leer_double("Ancho de banda (MB/s)");

        satelites[numero_satelites()] = new Satelite(
            cod, nombre, tipo, masa, altitud,
            capacidad, bateria, potencia,
            ancho_banda
        );
    }
    else{
        double resolucion;
        double cobertura;

        resolucion = leer_double("Resolución del sensor (m)");
        cobertura = leer_double("Cobertura (%)");

        satelites[numero_satelites()] = new Satelite(
            cod, nombre, tipo, masa, altitud, capacidad, 
            bateria, potencia, resolucion, cobertura);
    }
    std::cout << "Satélite registrado correctamente" << std::endl;
}

std::string CentroControl::verificar_codigo_satelite(){
    std::string cod;
    bool repetido;
    do{
        std::cout << "Código: ";
        std::cin >> cod;
        repetido = false;
        for(int i = 0; i < numero_satelites(); i++){
            if(cod == satelites[i]->get_codigo()){
                std::cout << "Código ya registrado, ingrese otro" << std::endl;
                repetido = true;
                break;
            }
        }
    }while(repetido);
    return cod;
}

std::string CentroControl::verificar_codigo_orbita(){
    std::string cod;
    bool repetido;
    do{
        std::cout << "Código: ";
        std::cin >> cod;
        repetido = false;
        for(int i = 0; i < numero_orbitas(); i++){
            if(cod == orbitas[i]->get_codigo()){
                std::cout << "Código ya registrado, ingrese otro" << std::endl;
                repetido = true;
                break;
            }
        }
    }while(repetido);
    return cod;
}

std::string CentroControl::verificar_codigo_estacion(){
    std::string cod;
    bool repetido;
    do{
        std::cout << "Código: ";
        std::cin >> cod;
        repetido = false;
        for(int i = 0; i < numero_estaciones(); i++){
            if(cod == estaciones[i]->get_codigo()){
                std::cout << "Código ya registrado, ingrese otro" << std::endl;
                repetido = true;
                break;
            }
        }
    }while(repetido);
    return cod;
}

double CentroControl::leer_double(std::string msj){
    double num;
    do{
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << msj << ": ";
    }while(!(std::cin >> num) || (num <= 0));
    return num;
}

double CentroControl::leer_double_min_max(std::string msj, double min, double max){
    double num;
    do{
        std::cout << msj << ": ";
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(!(std::cin >> num) || (num < min) || (num > max));
    return num;
}

Satelite* CentroControl::get_satelite(std::string codigo){
    for(int i = 0; i < numero_satelites(); i++){
        if(codigo == satelites[i]->get_codigo()){
            return satelites[i];
        }
    }
    return nullptr;
}

void CentroControl::listar_satelites(){
    if(numero_satelites() == 0){
        std::cout << "No hay satélites registrados" << std::endl;
        return;
    }
    for(int i = 0; i < numero_satelites(); i++){
        satelites[i]->mostrar_satelite();
    }
}

int CentroControl::numero_satelites(){
    int count = 0;
    for(int i = 0; i < MAX_SATELITES; i++){
        if(satelites[i] != nullptr){
            count++;
        }
    }
    return count;
}

int CentroControl::numero_orbitas(){
    int count = 0;
    for(int i = 0; i < MAX_ORBITAS; i++){
        if(orbitas[i] != nullptr){
            count++;
        }
    }
    return count;
}

int CentroControl::numero_estaciones(){
    int count = 0;
    for(int i = 0; i < MAX_ESTACIONES; i++){
        if(estaciones[i] != nullptr){
            count++;
        }
    }
    return count;
}

int CentroControl::numero_transmisiones(){
    int count = 0;
    for(int i = 0; i < MAX_TRANSMISIONES; i++){
        if(transmisiones[i] != nullptr){
            count++;
        }
    }
    return count;
}

void CentroControl::gestion_satelites(){
    int opcion;
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "==== GESTIÓN DE SATÉLITES ====" << std::endl <<
        "1. Registrar satélite" << std::endl <<
        "2. Buscar satélite" << std::endl <<
        "3. Listar satélites" << std::endl <<
        "Seleccione una opción: ";
    } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 3));
    switch (opcion){
        case 1:
            registrar_satelite();
            break;
        case 2:{
            std::string codigo;
            do{
                std::cout << "Ingrese el código del satélite: ";
            }while(!(std::cin >> codigo));
            Satelite* satelite = get_satelite(codigo);
            if(satelite == nullptr){
                std::cout << "Satélite no encontrado" << std::endl;
                return;
            }
            satelite->mostrar_satelite();
            break;
        }
        case 3:
            listar_satelites();
            break;
        default:
            return;
    }
}

