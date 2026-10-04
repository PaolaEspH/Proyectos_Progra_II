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

//CentroControl es el responsable de liberar lo que creó con new
CentroControl::~CentroControl(){
    for(int i = 0; i < MAX_TRANSMISIONES; i++){
        delete transmisiones[i];
    }
    for(int i = 0; i < MAX_ESTACIONES; i++){
        delete estaciones[i];
    }
    for(int i = 0; i < MAX_ORBITAS; i++){
        delete orbitas[i];
    }
    for(int i = 0; i < MAX_SATELITES; i++){
        delete satelites[i];
    }
    std::cout << "Memoria liberada correctamente" << std::endl;
}

//Satélites

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

Satelite* CentroControl::buscar_satelite(std::string codigo){
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
        "0. Regresar al menú principal" << std::endl <<
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
            Satelite* satelite = buscar_satelite(codigo);
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

//Órbitas

void CentroControl::gestion_orbitas(){
    int opcion;
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "==== GESTIÓN DE ÓRBITAS ====" << std::endl <<
        "1. Registrar órbita" << std::endl <<
        "2. Buscar órbita" << std::endl <<
        "3. Asignar satélite a órbita" << std::endl <<
        "4. Listar satélites por órbita" << std::endl <<
        "0. Regresar al menú principal" << std::endl <<
        "Seleccione una opción: ";
    } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 4));
    switch (opcion){
        case 1:
            registrar_orbita();
            break;
        case 2:{
            Orbita* orbita = buscar_orbita();
            if(orbita == nullptr){
                return;
            }
            orbita->mostrar_orbita();
            break;
        }
        case 3:
            asignar_satelite_a_orbita();
            break;
        case 4:
            listar_satelites_por_orbita();
            break;
        default:
            return;
    }
}

void CentroControl::registrar_orbita(){
    std::string cod;
    std::string nombre;
    double altitud;
    if(numero_orbitas() >= MAX_ORBITAS){
        std::cout << "No se pueden registrar más órbitas" << std::endl;
        return;
    }
    cod = verificar_codigo_orbita();
    std::cout << "Nombre: ";
    std::cin >> nombre;
    altitud = leer_double("Altitud de referencia (km)");

    orbitas[numero_orbitas()] = new Orbita(cod, nombre, altitud);
    std::cout << "Órbita registrada correctamente" << std::endl;
}

Orbita* CentroControl::buscar_orbita(){
    std::string codigo;
    do{
        std::cout << "Ingrese el código de la órbita: ";
    }while(!(std::cin >> codigo));
    for(int i = 0; i < numero_orbitas(); i++){
        if(codigo == orbitas[i]->get_codigo()){
            return orbitas[i];
        }
    }
    std::cout << "Órbita no encontrada" << std::endl;
    return nullptr;
}

void CentroControl::asignar_satelite_a_orbita(){
    std::string codigo;
    do{
        std::cout << "Ingrese el código del satélite: ";
    }while(!(std::cin >> codigo));
    Satelite* satelite = buscar_satelite(codigo);
    if(satelite == nullptr){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    Orbita* orbita = buscar_orbita();
    if(orbita == nullptr){
        return;
    }
    //set_orbita avisa si ya tiene órbita; solo se agrega al arreglo si la aceptó
    if(satelite->set_orbita(orbita)){
        orbita->asignar_satelite(satelite);
        std::cout << "Satélite asignado a órbita correctamente" << std::endl;
    }
}

void CentroControl::listar_satelites_por_orbita(){
    if(numero_orbitas() == 0){
        std::cout << "No hay órbitas registradas" << std::endl;
        return;
    }
    for (int i = 0; i < numero_orbitas(); i++){
        std::cout << "Órbita: " << orbitas[i]->get_codigo() << std::endl;
        std::cout << "Satélites en la órbita:" << std::endl;
        orbitas[i]->mostrar_satelites();
    }
}

//Estaciones y enlaces

void CentroControl::gestion_estaciones_y_enlaces(){
    int opcion;
    do{
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "==== ESTACIONES Y ENLACES ====" << std::endl <<
        "1. Registrar estación" << std::endl <<
        "2. Crear enlace" << std::endl <<
        "3. Mostrar matriz de enlaces" << std::endl <<
        "0. Regresar al menú principal" << std::endl <<
        "Seleccione una opción: ";
    } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 3));
    switch (opcion){
        case 1:
            registrar_estacion();
            break;
        case 2:
            registrar_enlace();
            break;
        case 3:
            mostrar_matriz_enlaces();
            break;
        default:
            return;
    }
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

void CentroControl::registrar_estacion(){
    std::string cod;
    std::string nombre;
    double latitud;
    double longitud;
    if(numero_estaciones() >= MAX_ESTACIONES){
        std::cout << "No se pueden registrar más estaciones" << std::endl;
        return;
    }
    cod = verificar_codigo_estacion();
    std::cout << "Nombre: ";
    std::cin >> nombre;
    latitud = leer_double_min_max("Latitud (°)", -90, 90);
    longitud = leer_double_min_max("Longitud (°)", -180, 180);

    estaciones[numero_estaciones()] = new EstacionTerrestre(cod, nombre, latitud, longitud);
    std::cout << "Estación registrada correctamente" << std::endl;
}

void CentroControl::mostrar_matriz_enlaces(){
    std::cout << "Matriz de enlaces:" << std::endl;
    std::cout << "Satélites/Estaciones" << std::endl;
    std::cout << "      ";
    // Mostrar estaciones en la primera fila
    for(int i = 0; i < numero_estaciones(); i++){
        std::cout << estaciones[i]->get_codigo() << " ";
    }
    std::cout << std::endl;
    for(int i = 0; i < numero_satelites(); i++){
        // Mostrar satélite en la primera columna
        std::cout << satelites[i]->get_codigo() << " ";
        for(int j = 0; j < numero_estaciones(); j++){
            std::cout << enlaces[i][j] << "      ";
        }
        std::cout << std::endl;
    }
}

EstacionTerrestre* CentroControl::buscar_estacion(std::string codigo){
    for(int i = 0; i < numero_estaciones(); i++){
        if(codigo == estaciones[i]->get_codigo()){
            return estaciones[i];
        }
    }
    return nullptr;
}

void CentroControl::registrar_enlace(){
    std::string cod_satelite;
    std::string cod_estacion;
    do{
        std::cout << "Ingrese el código del satélite: ";
    }while(!(std::cin >> cod_satelite));
    Satelite* satelite = buscar_satelite(cod_satelite);
    if(satelite == nullptr){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    do{
        std::cout << "Ingrese el código de la estación: ";
    }while(!(std::cin >> cod_estacion));
    EstacionTerrestre* estacion = buscar_estacion(cod_estacion);
    if(estacion == nullptr){
        std::cout << "Estación no encontrada" << std::endl;
        return;
    }
    // Buscar índices del satélite y la estación
    int index_satelite = -1;
    int index_estacion = -1;
    for(int i = 0; i < numero_satelites(); i++){
        if(satelites[i] == satelite){
            index_satelite = i;
            break;
        }
    }
    for(int j = 0; j < numero_estaciones(); j++){
        if(estaciones[j] == estacion){
            index_estacion = j;
            break;
        }
    }
    if(index_satelite != -1 && index_estacion != -1){
        enlaces[index_satelite][index_estacion] = true;
        std::cout << "Enlace registrado correctamente" << std::endl;
    }
}

void CentroControl::gestion_transmisiones(){
    std::string cod_satelite = verificar_codigo_satelite();
    std::string cod_estacion = verificar_codigo_estacion();
    // Buscar índices del satélite y la estación
    int index_satelite = indice_satelite(cod_satelite);
    int index_estacion = indice_estacion(cod_estacion);
    if(enlaces[index_satelite][index_estacion]){
        realizar_transmision(satelites[index_satelite], estaciones[index_estacion]);
    } else {
        std::cout << "No hay enlace entre el satélite " << cod_satelite
                  << " y la estación " << cod_estacion << std::endl;
    }
}

void CentroControl::realizar_transmision(Satelite* satelite, EstacionTerrestre* estacion){
    if(numero_transmisiones() >= MAX_TRANSMISIONES){
        std::cout << "No se pueden registrar más transmisiones" << std::endl;
        return;
    }
    double datos = leer_double("Datos a transmitir (MB)");
    double ancho_banda = leer_double("Ancho de banda (MB/s)");
    double potencia = leer_double("Potencia utilizada (W)");
    double duracion = leer_double("Duración (s)");
    std::cout << "Enlace de la matriz: ACTIVO" << std::endl;
    if(satelite->get_bateria() < reduccion_bateria(datos, ancho_banda, duracion)){
        std::cout << "Batería insuficiente para la transmisión" << std::endl;
        return;
    }
    std::cout << "Energía consumida: " << satelite->energia_consumida() << " Wh" << std::endl;
    std::cout << "Batería anterior: " << satelite->get_bateria() << " %" << std::endl;
    satelite->actualizar_bateria(datos, ancho_banda, duracion);
    std::cout << "Batería actual: " << satelite->get_bateria() << " %" << std::endl;
    std::cout << "Estado:" << satelite->estado() << std::endl;
    transmisiones[numero_transmisiones()] = new Transmision(ancho_banda, potencia, duracion, satelite->energia_consumida(), duracion);
    std::cout << "Transmisión registrada correctamente" << std::endl;
}

int CentroControl::indice_satelite(std::string codigo){
    for(int i = 0; i < numero_satelites(); i++){
        if(satelites[i]->get_codigo() == codigo){
            return i;
        }
    }
    return -1;
}

int CentroControl::indice_estacion(std::string codigo){
    for(int i = 0; i < numero_estaciones(); i++){
        if(estaciones[i]->get_codigo() == codigo){
            return i;
        }
    }
    return -1;
}