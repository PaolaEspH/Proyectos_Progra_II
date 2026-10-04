#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
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
            enlaces[i][j] = 0;
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
    nombre = leer_nombre("Nombre");
    do{
        if(std::cin.fail()){
            if(std::cin.eof()){
                return;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Tipo (1. Comunicación / 2. Meteorológico): ";
    } while(!(std::cin >> tipo) || ((tipo != 1) && (tipo != 2)));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    masa = leer_double("Masa (kg)");
    altitud = leer_double("Altitud (km)");
    capacidad = leer_double("Capacidad energética (Wh)");
    bateria = leer_double_min_max("Bateria actual (%)", 0, 100);
    potencia = leer_double("Potencia de transmision (W)");

    if(std::cin.eof()){
        std::cout << "Registro incompleto, no se guardó el satélite" << std::endl;
        return;
    }
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
        cobertura = leer_double_min_max("Cobertura (%)", 0, 100);

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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_satelites(); i++){
            if((satelites[i] != nullptr) && (cod == satelites[i]->get_codigo())){
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_orbitas(); i++){
            if((orbitas[i] != nullptr) && (cod == orbitas[i]->get_codigo())){
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_estaciones(); i++){
            if((estaciones[i] != nullptr) && (cod == estaciones[i]->get_codigo())){
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
            if(std::cin.eof()){
                return 0;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << msj << ": ";
    }while(!(std::cin >> num) || (num <= 0));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}

double CentroControl::leer_double_min_max(std::string msj, double min, double max){
    double num;
    do{
        std::cout << msj << ": ";
        if (std::cin.fail()){
            if(std::cin.eof()){
                return min;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(!(std::cin >> num) || (num < min) || (num > max));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return num;
}

Satelite* CentroControl::buscar_satelite(std::string codigo){
    for(int i = 0; i < numero_satelites(); i++){
        if((satelites[i] != nullptr) && (codigo == satelites[i]->get_codigo())){
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
        if(satelites[i] != nullptr){
            satelites[i]->mostrar_resumen();
        }
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
        do{
            if(std::cin.fail()){
                if(std::cin.eof()){
                    return;
                }
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
                std::string codigo = leer_codigo("Ingrese el código del satélite");
                Satelite* satelite = buscar_satelite(codigo);
                if(satelite == nullptr){
                    std::cout << "Satélite no encontrado" << std::endl;
                    break;
                }
                satelite->mostrar_satelite();
                break;
            }
            case 3:
                listar_satelites();
                break;
            default:
                break;
        }
    }while(opcion != 0);
    std::cout << "Regresando al menú principal..." << std::endl;
}

//Órbitas

void CentroControl::gestion_orbitas(){
    int opcion;
    do{
        do{
            if(std::cin.fail()){
                if(std::cin.eof()){
                    return;
                }
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
                std::string codigo = leer_codigo("Ingrese el código de la órbita");
                Orbita* orbita = buscar_orbita(codigo);
                if(orbita == nullptr){
                    std::cout << "Órbita no encontrada" << std::endl;
                    break;
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
                break;
        }
    }while(opcion != 0);
    std::cout << "Regresando al menú principal..." << std::endl;
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
    nombre = leer_nombre("Nombre");
    altitud = leer_double("Altitud de referencia (km)");

    orbitas[numero_orbitas()] = new Orbita(cod, nombre, altitud);
    std::cout << "Órbita registrada correctamente" << std::endl;
}

Orbita* CentroControl::buscar_orbita(std::string codigo){
    for(int i = 0; i < numero_orbitas(); i++){
        if((orbitas[i] != nullptr) && (codigo == orbitas[i]->get_codigo())){
            return orbitas[i];
        }
    }
    return nullptr;
}

void CentroControl::asignar_satelite_a_orbita(){
    std::string codigo = leer_codigo("Ingrese el código del satélite");
    Satelite* satelite = buscar_satelite(codigo);
    if(satelite == nullptr){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    std::string cod_orbita = leer_codigo("Ingrese el código de la órbita");
    Orbita* orbita = buscar_orbita(cod_orbita);
    if(orbita == nullptr){
        std::cout << "Órbita no encontrada" << std::endl;
        return;
    }
    //Un satélite no puede estar en dos órbitas a la vez
    if(satelite->get_orbita() != nullptr){
        std::cout << "El satélite ya está asignado a la órbita "
                  << satelite->get_orbita()->get_codigo() << std::endl;
        return;
    }
    //Solo se marca en el satélite si la órbita logró guardar el puntero
    if(orbita->asignar_satelite(satelite)){
        satelite->set_orbita(orbita);
        std::cout << "Satélite asignado a órbita correctamente" << std::endl;
    }
}

void CentroControl::listar_satelites_por_orbita(){
    if(numero_orbitas() == 0){
        std::cout << "No hay órbitas registradas" << std::endl;
        return;
    }
    for (int i = 0; i < numero_orbitas(); i++){
        if(orbitas[i] != nullptr){
            std::cout << "Órbita: " << orbitas[i]->get_codigo() << std::endl;
            std::cout << "Satélites en la órbita:" << std::endl;
            orbitas[i]->mostrar_satelites();
        }
    }
}

//Estaciones y enlaces

void CentroControl::gestion_estaciones_y_enlaces(){
    int opcion;
    do{
        do{
            if(std::cin.fail()){
                if(std::cin.eof()){
                    return;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "==== ESTACIONES Y ENLACES ====" << std::endl <<
            "1. Registrar estación" << std::endl <<
            "2. Buscar estación" << std::endl <<
            "3. Crear enlace" << std::endl <<
            "4. Eliminar enlace" << std::endl <<
            "5. Mostrar satélites enlazados con una estación" << std::endl <<
            "6. Mostrar matriz de enlaces" << std::endl <<
            "7. Enlaces activos por satélite y por estación" << std::endl <<
            "0. Regresar al menú principal" << std::endl <<
            "Seleccione una opción: ";
        } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 7));
        switch (opcion){
            case 1:
                registrar_estacion();
                break;
            case 2:{
                std::string codigo = leer_codigo("Ingrese el código de la estación");
                EstacionTerrestre* estacion = buscar_estacion(codigo);
                if(estacion == nullptr){
                    std::cout << "Estación no encontrada" << std::endl;
                    break;
                }
                estacion->mostrar_estacion();
                break;
            }
            case 3:
                registrar_enlace();
                break;
            case 4:
                eliminar_enlace();
                break;
            case 5:
                mostrar_satelites_de_estacion();
                break;
            case 6:
                mostrar_matriz_enlaces();
                break;
            case 7:
                mostrar_enlaces_activos();
                break;
            default:
                break;
        }
    }while(opcion != 0);
    std::cout << "Regresando al menú principal..." << std::endl;
}

void CentroControl::registrar_estacion(){
    std::string cod;
    std::string nombre;
    std::string ubicacion;
    if(numero_estaciones() >= MAX_ESTACIONES){
        std::cout << "No se pueden registrar más estaciones" << std::endl;
        return;
    }
    cod = verificar_codigo_estacion();
    nombre = leer_nombre("Nombre");
    ubicacion = leer_nombre("Ubicación");

    estaciones[numero_estaciones()] = new EstacionTerrestre(cod, nombre, ubicacion);
    std::cout << "Estación registrada correctamente" << std::endl;
}

EstacionTerrestre* CentroControl::buscar_estacion(std::string codigo){
    for(int i = 0; i < numero_estaciones(); i++){
        if((estaciones[i] != nullptr) && (codigo == estaciones[i]->get_codigo())){
            return estaciones[i];
        }
    }
    return nullptr;
}

int CentroControl::indice_satelite(std::string codigo){
    for(int i = 0; i < numero_satelites(); i++){
        if((satelites[i] != nullptr) && (satelites[i]->get_codigo() == codigo)){
            return i;
        }
    }
    return -1;
}

int CentroControl::indice_estacion(std::string codigo){
    for(int i = 0; i < numero_estaciones(); i++){
        if((estaciones[i] != nullptr) && (estaciones[i]->get_codigo() == codigo)){
            return i;
        }
    }
    return -1;
}

void CentroControl::registrar_enlace(){
    std::string cod_satelite = leer_codigo("Ingrese el código del satélite");
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Ingrese el código de la estación");
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estación no encontrada" << std::endl;
        return;
    }
    if(enlaces[index_satelite][index_estacion] == 1){
        std::cout << "El enlace ya existe" << std::endl;
        return;
    }
    //La estación guarda el puntero y la matriz guarda el 1
    if(estaciones[index_estacion]->agregar_satelite(satelites[index_satelite])){
        enlaces[index_satelite][index_estacion] = 1;
        std::cout << "Enlace activado. Matriz actualizada" << std::endl;
    }
}

void CentroControl::eliminar_enlace(){
    std::string cod_satelite = leer_codigo("Ingrese el código del satélite");
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Ingrese el código de la estación");
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estación no encontrada" << std::endl;
        return;
    }
    if(enlaces[index_satelite][index_estacion] == 0){
        std::cout << "No existe ese enlace" << std::endl;
        return;
    }
    if(!estaciones[index_estacion]->eliminar_satelite(satelites[index_satelite])){
        std::cout << "No se pudo eliminar el enlace" << std::endl;
        return;
    }
    enlaces[index_satelite][index_estacion] = 0;
    std::cout << "Enlace eliminado. Matriz actualizada" << std::endl;
}

void CentroControl::mostrar_satelites_de_estacion(){
    std::string codigo = leer_codigo("Ingrese el código de la estación");
    EstacionTerrestre* estacion = buscar_estacion(codigo);
    if(estacion == nullptr){
        std::cout << "Estación no encontrada" << std::endl;
        return;
    }
    std::cout << "Satélites enlazados con " << estacion->get_codigo() << ":" << std::endl;
    estacion->mostrar_satelites();
}

void CentroControl::mostrar_matriz_enlaces(){
    if((numero_satelites() == 0) || (numero_estaciones() == 0)){
        std::cout << "Hacen falta satélites y estaciones registrados" << std::endl;
        return;
    }
    std::cout << "MATRIZ DE ENLACES" << std::endl;
    //Ancho de la primera columna segun el código de satélite más largo
    int ancho = 8;
    for(int i = 0; i < numero_satelites(); i++){
        if(satelites[i] != nullptr){
            int largo = satelites[i]->get_codigo().length();
            if(largo + 2 > ancho){
                ancho = largo + 2;
            }
        }
    }
    //Encabezado con los códigos de las estaciones
    std::cout << std::left << std::setw(ancho) << " ";
    for(int j = 0; j < numero_estaciones(); j++){
        if(estaciones[j] != nullptr){
            std::cout << std::setw(estaciones[j]->get_codigo().length() + 2)
                      << estaciones[j]->get_codigo();
        }
    }
    std::cout << std::endl;
    for(int i = 0; i < numero_satelites(); i++){
        if(satelites[i] == nullptr){
            continue;
        }
        std::cout << std::setw(ancho) << satelites[i]->get_codigo();
        for(int j = 0; j < numero_estaciones(); j++){
            if(estaciones[j] != nullptr){
                std::cout << std::setw(estaciones[j]->get_codigo().length() + 2)
                          << enlaces[i][j];
            }
        }
        std::cout << std::endl;
    }
}

void CentroControl::mostrar_enlaces_activos(){
    if((numero_satelites() == 0) || (numero_estaciones() == 0)){
        std::cout << "No hay satélites ni estaciones registrados" << std::endl;
        return;
    }
    std::cout << "Enlaces activos por satélite:" << std::endl;
    for(int i = 0; i < numero_satelites(); i++){
        if(satelites[i] == nullptr){
            continue;
        }
        int total = 0;
        for(int j = 0; j < numero_estaciones(); j++){
            total = total + enlaces[i][j];
        }
        std::cout << "   " << satelites[i]->get_codigo() << ": " << total << std::endl;
    }
    std::cout << "Enlaces activos por estación:" << std::endl;
    for(int j = 0; j < numero_estaciones(); j++){
        if(estaciones[j] == nullptr){
            continue;
        }
        int total = 0;
        for(int i = 0; i < numero_satelites(); i++){
            total = total + enlaces[i][j];
        }
        std::cout << "   " << estaciones[j]->get_codigo() << ": " << total << std::endl;
    }
}

//Transmisiones

void CentroControl::gestion_transmisiones(){
    if(numero_transmisiones() >= MAX_TRANSMISIONES){
        std::cout << "No se pueden registrar más transmisiones" << std::endl;
        return;
    }
    std::cout << "--- Nueva transmisión ---" << std::endl;
    std::string cod_satelite = leer_codigo("Satélite");
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satélite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Estación");
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estación no encontrada" << std::endl;
        return;
    }
    //Sin un 1 en la matriz no se puede transmitir
    if(enlaces[index_satelite][index_estacion] == 0){
        std::cout << "No hay enlace entre el satélite " << cod_satelite
                  << " y la estación " << cod_estacion << std::endl;
        return;
    }
    realizar_transmision(satelites[index_satelite], estaciones[index_estacion]);
}

void CentroControl::realizar_transmision(Satelite* satelite, EstacionTerrestre* estacion){
    if((satelite == nullptr) || (estacion == nullptr)){
        std::cout << "Transmisión no válida" << std::endl;
        return;
    }
    if(satelite->get_estado() == "FUERA DE SERVICIO"){
        std::cout << "El satélite está fuera de servicio, no puede transmitir" << std::endl;
        return;
    }
    double datos = leer_double("Datos a transmitir (MB)");
    //El ancho de banda y la potencia no pueden pasar del máximo del satélite
    double ancho_banda;
    if(satelite->get_ancho_banda() > 0){
        ancho_banda = leer_double_min_max("Ancho de banda (MB/s)", 0.01, satelite->get_ancho_banda());
    }
    else{
        ancho_banda = leer_double("Ancho de banda (MB/s)");
    }
    double potencia = leer_double_min_max("Potencia utilizada (W)", 0.01, satelite->get_potencia());

    Transmision* transmision = new Transmision(satelite, estacion, datos, ancho_banda, potencia);
    double bateria_anterior = satelite->get_bateria();

    //Se rechaza si la energia disponible no alcanza o si dejaria la bateria bajo 0%
    if(transmision->get_energia() > satelite->energia_disponible()){
        std::cout << "Energía insuficiente: la transmisión necesita "
                  << transmision->get_energia() << " Wh y el satélite tiene "
                  << satelite->energia_disponible() << " Wh" << std::endl;
        delete transmision;
        return;
    }
    if(!satelite->reducir_bateria(transmision->get_energia())){
        std::cout << "La transmisión dejaría la batería por debajo de 0%" << std::endl;
        delete transmision;
        return;
    }

    transmisiones[numero_transmisiones()] = transmision;
    std::cout << "Enlace en matriz: 1" << std::endl;
    transmision->mostrar_transmision();
    std::cout << "Batería anterior: " << bateria_anterior << "%" << std::endl;
    std::cout << "Batería actual: " << satelite->get_bateria() << "%" << std::endl;
    std::cout << "Estado: " << satelite->get_estado() << std::endl;
    std::cout << "Transmisión registrada correctamente" << std::endl;
}

}

