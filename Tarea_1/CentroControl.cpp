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
        std::cout << "No se pueden registrar mas satelites" << std::endl;
        return;
    }
    cod = verificar_codigo_satelite();
    nombre = leer_nombre("Nombre");
    if(cod.empty() || nombre.empty()){
        std::cout << "Registro incompleto, no se guardo el satelite" << std::endl;
        return;
    }
    do{
        if(std::cin.fail()){
            if(std::cin.eof()){
                std::cout << "Registro incompleto, no se guardo el satelite" << std::endl;
                return;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << "Tipo (1. Comunicacion / 2. Meteorologico): ";
    } while(!(std::cin >> tipo) || ((tipo != 1) && (tipo != 2)));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    masa = leer_double("Masa (kg)");
    altitud = leer_double("Altitud (km)");
    capacidad = leer_double("Capacidad energetica (Wh)");
    bateria = leer_double_min_max("Bateria actual (%)", 0, 100);
    potencia = leer_double("Potencia de transmision (W)");

    if(!std::cin){
        std::cout << "Registro incompleto, no se guardo el satelite" << std::endl;
        return;
    }
    if(tipo == 1){
        double ancho_banda;
        ancho_banda = leer_double("Ancho de banda (MB/s)");
        if(!std::cin){
            std::cout << "Registro incompleto, no se guardo el satelite" << std::endl;
            return;
        }

        satelites[numero_satelites()] = new Satelite(
            cod, nombre, tipo, masa, altitud,
            capacidad, bateria, potencia,
            ancho_banda
        );
    }
    else{
        double resolucion;
        double cobertura;

        resolucion = leer_double("Resolucion del sensor (m)");
        cobertura = leer_double_min_max("Cobertura (%)", 0, 100);
        if(!std::cin){
            std::cout << "Registro incompleto, no se guardo el satelite" << std::endl;
            return;
        }

        satelites[numero_satelites()] = new Satelite(
            cod, nombre, tipo, masa, altitud, capacidad, 
            bateria, potencia, resolucion, cobertura);
    }
    std::cout << "Satelite registrado correctamente" << std::endl;
}

std::string CentroControl::verificar_codigo_satelite(){
    std::string cod;
    bool repetido;
    do{
        std::cout << "Codigo: ";
        if(!(std::cin >> cod)){
            return "";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_satelites(); i++){
            if((satelites[i] != nullptr) && (cod == satelites[i]->get_codigo())){
                std::cout << "Codigo ya registrado, ingrese otro" << std::endl;
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
        std::cout << "Codigo: ";
        if(!(std::cin >> cod)){
            return "";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_orbitas(); i++){
            if((orbitas[i] != nullptr) && (cod == orbitas[i]->get_codigo())){
                std::cout << "Codigo ya registrado, ingrese otro" << std::endl;
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
        std::cout << "Codigo: ";
        if(!(std::cin >> cod)){
            return "";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        repetido = false;
        for(int i = 0; i < numero_estaciones(); i++){
            if((estaciones[i] != nullptr) && (cod == estaciones[i]->get_codigo())){
                std::cout << "Codigo ya registrado, ingrese otro" << std::endl;
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

//Lee una linea completa para aceptar nombres y ubicaciones con espacios
std::string CentroControl::leer_nombre(std::string msj){
    std::string texto;
    std::cout << msj << ": ";
    //La primera lectura se come el fin de linea que dejo pendiente el >> anterior
    while(std::getline(std::cin, texto)){
        if(!texto.empty()){
            return texto;
        }
    }
    return "";
}

std::string CentroControl::leer_codigo(std::string msj){
    std::string codigo;
    do{
        if(std::cin.fail()){
            if(std::cin.eof()){
                return "";
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout << msj << ": ";
    }while(!(std::cin >> codigo));
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return codigo;
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
        std::cout << "No hay satelites registrados" << std::endl;
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
            std::cout << "==== GESTION DE SATELITES ====" << std::endl <<
            "1. Registrar satelite" << std::endl <<
            "2. Buscar satelite" << std::endl <<
            "3. Listar satelites" << std::endl <<
            "0. Regresar al menu principal" << std::endl <<
            "Seleccione una opcion: ";
        } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 3));
        switch (opcion){
            case 1:
                registrar_satelite();
                break;
            case 2:{
                std::string codigo = leer_codigo("Ingrese el codigo del satelite");
                Satelite* satelite = buscar_satelite(codigo);
                if(satelite == nullptr){
                    std::cout << "Satelite no encontrado" << std::endl;
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
    std::cout << "Regresando al menu principal..." << std::endl;
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
            std::cout << "==== GESTION DE ORBITAS ====" << std::endl <<
            "1. Registrar orbita" << std::endl <<
            "2. Buscar orbita" << std::endl <<
            "3. Asignar satelite a orbita" << std::endl <<
            "4. Listar satelites por orbita" << std::endl <<
            "0. Regresar al menu principal" << std::endl <<
            "Seleccione una opcion: ";
        } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 4));
        switch (opcion){
            case 1:
                registrar_orbita();
                break;
            case 2:{
                std::string codigo = leer_codigo("Ingrese el codigo de la orbita");
                Orbita* orbita = buscar_orbita(codigo);
                if(orbita == nullptr){
                    std::cout << "Orbita no encontrada" << std::endl;
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
    std::cout << "Regresando al menu principal..." << std::endl;
}

void CentroControl::registrar_orbita(){
    std::string cod;
    std::string nombre;
    double altitud;
    if(numero_orbitas() >= MAX_ORBITAS){
        std::cout << "No se pueden registrar mas orbitas" << std::endl;
        return;
    }
    cod = verificar_codigo_orbita();
    nombre = leer_nombre("Nombre");
    altitud = leer_double("Altitud de referencia (km)");
    if(!std::cin || cod.empty() || nombre.empty()){
        std::cout << "Registro incompleto, no se guardo la orbita" << std::endl;
        return;
    }

    orbitas[numero_orbitas()] = new Orbita(cod, nombre, altitud);
    std::cout << "Orbita registrada correctamente" << std::endl;
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
    std::string codigo = leer_codigo("Ingrese el codigo del satelite");
    Satelite* satelite = buscar_satelite(codigo);
    if(satelite == nullptr){
        std::cout << "Satelite no encontrado" << std::endl;
        return;
    }
    std::string cod_orbita = leer_codigo("Ingrese el codigo de la orbita");
    Orbita* orbita = buscar_orbita(cod_orbita);
    if(orbita == nullptr){
        std::cout << "Orbita no encontrada" << std::endl;
        return;
    }
    //Un satélite no puede estar en dos órbitas a la vez
    if(satelite->get_orbita() != nullptr){
        std::cout << "El satelite ya esta asignado a la orbita "
                  << satelite->get_orbita()->get_codigo() << std::endl;
        return;
    }
    //Solo se marca en el satélite si la órbita logró guardar el puntero
    if(orbita->asignar_satelite(satelite)){
        satelite->set_orbita(orbita);
        std::cout << "Satelite asignado a orbita correctamente" << std::endl;
    }
}

void CentroControl::listar_satelites_por_orbita(){
    if(numero_orbitas() == 0){
        std::cout << "No hay orbitas registradas" << std::endl;
        return;
    }
    for (int i = 0; i < numero_orbitas(); i++){
        if(orbitas[i] != nullptr){
            std::cout << "Orbita: " << orbitas[i]->get_codigo() << std::endl;
            std::cout << "Satelites en la orbita:" << std::endl;
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
            "1. Registrar estacion" << std::endl <<
            "2. Buscar estacion" << std::endl <<
            "3. Crear enlace" << std::endl <<
            "4. Eliminar enlace" << std::endl <<
            "5. Mostrar satelites enlazados con una estacion" << std::endl <<
            "6. Mostrar matriz de enlaces" << std::endl <<
            "7. Enlaces activos por satelite y por estacion" << std::endl <<
            "0. Regresar al menu principal" << std::endl <<
            "Seleccione una opcion: ";
        } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 7));
        switch (opcion){
            case 1:
                registrar_estacion();
                break;
            case 2:{
                std::string codigo = leer_codigo("Ingrese el codigo de la estacion");
                EstacionTerrestre* estacion = buscar_estacion(codigo);
                if(estacion == nullptr){
                    std::cout << "Estacion no encontrada" << std::endl;
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
    std::cout << "Regresando al menu principal..." << std::endl;
}

void CentroControl::registrar_estacion(){
    std::string cod;
    std::string nombre;
    std::string ubicacion;
    if(numero_estaciones() >= MAX_ESTACIONES){
        std::cout << "No se pueden registrar mas estaciones" << std::endl;
        return;
    }
    cod = verificar_codigo_estacion();
    nombre = leer_nombre("Nombre");
    ubicacion = leer_nombre("Ubicacion");
    if(!std::cin || cod.empty() || nombre.empty() || ubicacion.empty()){
        std::cout << "Registro incompleto, no se guardo la estacion" << std::endl;
        return;
    }

    estaciones[numero_estaciones()] = new EstacionTerrestre(cod, nombre, ubicacion);
    std::cout << "Estacion registrada correctamente" << std::endl;
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
    std::string cod_satelite = leer_codigo("Ingrese el codigo del satelite");
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satelite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Ingrese el codigo de la estacion");
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estacion no encontrada" << std::endl;
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
    std::string cod_satelite = leer_codigo("Ingrese el codigo del satelite");
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satelite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Ingrese el codigo de la estacion");
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estacion no encontrada" << std::endl;
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
    std::string codigo = leer_codigo("Ingrese el codigo de la estacion");
    EstacionTerrestre* estacion = buscar_estacion(codigo);
    if(estacion == nullptr){
        std::cout << "Estacion no encontrada" << std::endl;
        return;
    }
    std::cout << "Satelites enlazados con " << estacion->get_codigo() << ":" << std::endl;
    estacion->mostrar_satelites();
}

void CentroControl::mostrar_matriz_enlaces(){
    if((numero_satelites() == 0) || (numero_estaciones() == 0)){
        std::cout << "Hacen falta satelites y estaciones registrados" << std::endl;
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
        std::cout << "No hay satelites ni estaciones registrados" << std::endl;
        return;
    }
    std::cout << "Enlaces activos por satelite:" << std::endl;
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
    std::cout << "Enlaces activos por estacion:" << std::endl;
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
        std::cout << "No se pueden registrar mas transmisiones" << std::endl;
        return;
    }
    std::cout << "--- Nueva transmision ---" << std::endl;
    std::string cod_satelite = leer_codigo("Satelite");
    if(cod_satelite.empty()){
        std::cout << "Transmision incompleta, no se guardo el envio" << std::endl;
        return;
    }
    int index_satelite = indice_satelite(cod_satelite);
    if(index_satelite == -1){
        std::cout << "Satelite no encontrado" << std::endl;
        return;
    }
    std::string cod_estacion = leer_codigo("Estacion");
    if(cod_estacion.empty()){
        std::cout << "Transmision incompleta, no se guardo el envio" << std::endl;
        return;
    }
    int index_estacion = indice_estacion(cod_estacion);
    if(index_estacion == -1){
        std::cout << "Estacion no encontrada" << std::endl;
        return;
    }
    //Sin un 1 en la matriz no se puede transmitir
    if(enlaces[index_satelite][index_estacion] == 0){
        std::cout << "No hay enlace entre el satelite " << cod_satelite
                  << " y la estacion " << cod_estacion << std::endl;
        return;
    }
    realizar_transmision(satelites[index_satelite], estaciones[index_estacion]);
}

void CentroControl::realizar_transmision(Satelite* satelite, EstacionTerrestre* estacion){
    if((satelite == nullptr) || (estacion == nullptr)){
        std::cout << "Transmision no valida" << std::endl;
        return;
    }
    if(satelite->get_estado() == "FUERA DE SERVICIO"){
        std::cout << "El satelite esta fuera de servicio, no puede transmitir" << std::endl;
        return;
    }
    double datos = leer_double("Datos a transmitir (MB)");
    if(!std::cin){
        std::cout << "Transmision incompleta, no se guardo el envio" << std::endl;
        return;
    }
    //El ancho de banda y la potencia no pueden pasar del máximo del satélite
    double ancho_banda = leer_double("Ancho de banda (MB/s)");
    if(!std::cin){
        std::cout << "Transmision incompleta, no se guardo el envio" << std::endl;
        return;
    }
    if(ancho_banda <= 0 || (satelite->get_ancho_banda() > 0 && ancho_banda > satelite->get_ancho_banda())){
        std::cout << "El ancho de banda debe ser positivo y no superar el maximo del satelite" << std::endl;
        return;
    }
    double potencia = leer_double("Potencia utilizada (W)");
    if(!std::cin){
        std::cout << "Transmision incompleta, no se guardo el envio" << std::endl;
        return;
    }
    if(potencia <= 0 || potencia > satelite->get_potencia()){
        std::cout << "La potencia debe ser positiva y no superar el maximo del satelite" << std::endl;
        return;
    }

    Transmision* transmision = new Transmision(satelite, estacion, datos, ancho_banda, potencia);
    double bateria_anterior = satelite->get_bateria();

    //Se rechaza si la energia disponible no alcanza o si dejaria la bateria bajo 0%
    if(transmision->get_energia() > satelite->energia_disponible()){
        std::cout << "Energia insuficiente: la transmision necesita "
                  << transmision->get_energia() << " Wh y el satelite tiene "
                  << satelite->energia_disponible() << " Wh" << std::endl;
        delete transmision;
        return;
    }
    if(!satelite->reducir_bateria(transmision->get_energia())){
        std::cout << "La transmision dejaria la bateria por debajo de 0%" << std::endl;
        delete transmision;
        return;
    }

    transmisiones[numero_transmisiones()] = transmision;
    std::cout << "Enlace en matriz: 1" << std::endl;
    transmision->mostrar_transmision();
    std::cout << "Bateria anterior: " << bateria_anterior << "%" << std::endl;
    std::cout << "Bateria actual: " << satelite->get_bateria() << "%" << std::endl;
    std::cout << "Estado: " << satelite->get_estado() << std::endl;
    std::cout << "Transmision registrada correctamente" << std::endl;
}

void CentroControl::telemetria(){
    if(numero_satelites() == 0){
        std::cout << "No hay satelites registrados" << std::endl;
        return;
    }
    int opcion = -1;
    while(opcion != 0){
        std::cout << "Telemetria" << std::endl;
        std::cout << "1. Registrar muestra" << std::endl;
        std::cout << "2. Mostrar historial" << std::endl;
        std::cout << "3. Mostrar estadisticas" << std::endl;
        std::cout << "0. Regresar" << std::endl;
        std::cout << "Opcion: ";
        if(!(std::cin >> opcion)){
            std::cout << "Opcion invalida" << std::endl;
            return;
        }
        if(opcion == 0){
            return;
        }
        if(opcion < 1 || opcion > 3){
            std::cout << "Opcion invalida" << std::endl;
            continue;
        }
        std::string codigo;
        std::cout << "Codigo del satelite: ";
        if(!(std::cin >> codigo)){
            return;
        }
        Satelite* satelite = buscar_satelite(codigo);
        if(satelite == nullptr){
            std::cout << "Satelite no encontrado" << std::endl;
            continue;
        }
        if(opcion == 1){
            if(satelite->get_cantidad_muestras() >= MAX_MUESTRAS){
                std::cout << "El historial esta lleno, maximo 12 muestras" << std::endl;
                continue;
            }
            double bateria_medida;
            double temperatura;
            std::cout << "Bateria medida (%): ";
            if(!(std::cin >> bateria_medida)){
                std::cout << "Dato invalido" << std::endl;
                return;
            }
            std::cout << "Temperatura (°C): ";
            if(!(std::cin >> temperatura)){
                std::cout << "Dato invalido" << std::endl;
                return;
            }
            if(satelite->registrar_muestra(bateria_medida, temperatura)){
                std::cout << "Muestra guardada" << std::endl;
                std::cout << "Muestras: " << satelite->get_cantidad_muestras() << " de 12" << std::endl;
            }
            else{
                std::cout << "La bateria debe estar entre 0 y 100" << std::endl;
            }
        }
        else if(opcion == 2){
            satelite->mostrar_historial();
        }
        else{
            satelite->mostrar_estadisticas();
        }
    }
}

void CentroControl::control_energetico(){
    if(numero_satelites() == 0){
        std::cout << "No hay satelites registrados" << std::endl;
        return;
    }
    int opcion = -1;
    while(opcion != 0){
        std::cout << "Control energetico" << std::endl;
        std::cout << "1. Consultar bateria y estado" << std::endl;
        std::cout << "2. Recarga solar" << std::endl;
        std::cout << "3. Satelites criticos y fuera de servicio" << std::endl;
        std::cout << "0. Regresar" << std::endl;
        std::cout << "Opcion: ";
        if(!(std::cin >> opcion)){
            std::cout << "Opcion invalida" << std::endl;
            return;
        }
        if(opcion == 0){
            return;
        }
        if(opcion < 1 || opcion > 3){
            std::cout << "Opcion invalida" << std::endl;
            continue;
        }
        if(opcion == 3){
            int cantidad = 0;
            for(int i = 0; i < MAX_SATELITES; i++){
                if(satelites[i] != nullptr && satelites[i]->get_bateria() < 20){
                    satelites[i]->mostrar_resumen();
                    cantidad++;
                }
            }
            if(cantidad == 0){
                std::cout << "No hay satelites criticos ni fuera de servicio" << std::endl;
            }
            continue;
        }
        std::string codigo;
        std::cout << "Codigo del satelite: ";
        if(!(std::cin >> codigo)){
            return;
        }
        Satelite* satelite = buscar_satelite(codigo);
        if(satelite == nullptr){
            std::cout << "Satelite no encontrado" << std::endl;
            continue;
        }
        if(opcion == 1){
            std::cout << "Bateria actual: " << satelite->get_bateria() << "%" << std::endl;
            std::cout << "Estado: " << satelite->get_estado() << std::endl;
            std::cout << "Energia disponible: " << satelite->energia_disponible() << " Wh" << std::endl;
        }
        else{
            double potencia_solar;
            double segundos;
            double eficiencia;
            std::cout << "Potencia solar (W): ";
            if(!(std::cin >> potencia_solar)){
                std::cout << "Dato invalido" << std::endl;
                return;
            }
            std::cout << "Tiempo de recarga (s): ";
            if(!(std::cin >> segundos)){
                std::cout << "Dato invalido" << std::endl;
                return;
            }
            std::cout << "Eficiencia (0 a 1): ";
            if(!(std::cin >> eficiencia)){
                std::cout << "Dato invalido" << std::endl;
                return;
            }
            double bateria_anterior = satelite->get_bateria();
            if(satelite->recargar_solar(potencia_solar, segundos, eficiencia)){
                std::cout << "Recarga realizada" << std::endl;
                std::cout << "Bateria anterior: " << bateria_anterior << "%" << std::endl;
                std::cout << "Bateria actual: " << satelite->get_bateria() << "%" << std::endl;
                std::cout << "Estado: " << satelite->get_estado() << std::endl;
            }
            else{
                std::cout << "Potencia y tiempo deben ser positivos, eficiencia entre 0 y 1" << std::endl;
            }
        }
    }
}

void CentroControl::reportes(){
    int opcion = -1;
    while(opcion != 0){
        std::cout << "Reportes" << std::endl;
        std::cout << "1. Cantidad de satelites por tipo" << std::endl;
        std::cout << "2. Satelites por orbita" << std::endl;
        std::cout << "3. Velocidad y periodo orbital" << std::endl;
        std::cout << "4. Promedio de bateria" << std::endl;
        std::cout << "5. Satelite con menor bateria" << std::endl;
        std::cout << "6. Datos transmitidos y energia consumida" << std::endl;
        std::cout << "7. Historial de transmisiones" << std::endl;
        std::cout << "8. Resumen de telemetria" << std::endl;
        std::cout << "9. Matriz y enlaces activos" << std::endl;
        std::cout << "0. Regresar" << std::endl;
        std::cout << "Opcion: ";
        if(!(std::cin >> opcion)){
            std::cout << "Opcion invalida" << std::endl;
            return;
        }
        if(opcion == 0){
            return;
        }
        switch(opcion){
            case 1:{
                int comunicacion = 0;
                int meteorologicos = 0;
                for(int i = 0; i < MAX_SATELITES; i++){
                    if(satelites[i] != nullptr){
                        if(satelites[i]->get_tipo() == 1){
                            comunicacion++;
                        }
                        else if(satelites[i]->get_tipo() == 2){
                            meteorologicos++;
                        }
                    }
                }
                std::cout << "Satelites registrados: " << comunicacion + meteorologicos << std::endl;
                std::cout << "Comunicacion: " << comunicacion << std::endl;
                std::cout << "Meteorologicos: " << meteorologicos << std::endl;
                break;
            }
            case 2:
                listar_satelites_por_orbita();
                break;
            case 3:{
                if(numero_satelites() == 0){
                    std::cout << "No hay satelites registrados" << std::endl;
                    break;
                }
                for(int i = 0; i < MAX_SATELITES; i++){
                    if(satelites[i] != nullptr){
                        std::cout << "Satelite: " << satelites[i]->get_codigo() << std::endl;
                        std::cout << "Velocidad: " << satelites[i]->velocidad_orbital() << " km/s" << std::endl;
                        std::cout << "Periodo: " << satelites[i]->periodo_orbital() << " s" << std::endl;
                        std::cout << "Periodo en minutos: " << satelites[i]->periodo_orbital_minutos() << " min" << std::endl;
                    }
                }
                break;
            }
            case 4:{
                double suma = 0;
                int cantidad = 0;
                for(int i = 0; i < MAX_SATELITES; i++){
                    if(satelites[i] != nullptr){
                        suma = suma + satelites[i]->get_bateria();
                        cantidad++;
                    }
                }
                if(cantidad == 0){
                    std::cout << "No hay satelites para calcular el promedio" << std::endl;
                }
                else{
                    std::cout << "Promedio de bateria de la red: " << suma / cantidad << "%" << std::endl;
                }
                break;
            }
            case 5:{
                Satelite* menor = nullptr;
                for(int i = 0; i < MAX_SATELITES; i++){
                    if(satelites[i] != nullptr){
                        if(menor == nullptr){
                            menor = satelites[i];
                        }
                        else if(satelites[i]->get_bateria() < menor->get_bateria()){
                            menor = satelites[i];
                        }
                    }
                }
                if(menor == nullptr){
                    std::cout << "No hay satelites registrados" << std::endl;
                }
                else{
                    std::cout << "Satelite con menor bateria:" << std::endl;
                    menor->mostrar_resumen();
                }
                break;
            }
            case 6:{
                double datos = 0;
                double energia = 0;
                int cantidad = 0;
                for(int i = 0; i < MAX_TRANSMISIONES; i++){
                    if(transmisiones[i] != nullptr){
                        datos = datos + transmisiones[i]->get_datos();
                        energia = energia + transmisiones[i]->get_energia();
                        cantidad++;
                    }
                }
                std::cout << "Transmisiones registradas: " << cantidad << std::endl;
                std::cout << "Datos transmitidos: " << datos << " MB" << std::endl;
                std::cout << "Energia consumida: " << energia << " Wh" << std::endl;
                break;
            }
            case 7:{
                int cantidad = 0;
                for(int i = 0; i < MAX_TRANSMISIONES; i++){
                    if(transmisiones[i] != nullptr){
                        cantidad++;
                        std::cout << "Transmision " << cantidad << std::endl;
                        transmisiones[i]->mostrar_transmision();
                    }
                }
                if(cantidad == 0){
                    std::cout << "No hay transmisiones registradas" << std::endl;
                }
                break;
            }
            case 8:{
                if(numero_satelites() == 0){
                    std::cout << "No hay satelites registrados" << std::endl;
                    break;
                }
                for(int i = 0; i < MAX_SATELITES; i++){
                    if(satelites[i] != nullptr){
                        std::cout << "Satelite: " << satelites[i]->get_codigo() << std::endl;
                        std::cout << "Muestras: " << satelites[i]->get_cantidad_muestras() << " de 12" << std::endl;
                        satelites[i]->mostrar_estadisticas();
                    }
                }
                break;
            }
            case 9:
                mostrar_matriz_enlaces();
                mostrar_enlaces_activos();
                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                break;
        }
    }
}
