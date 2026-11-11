#include "sistema.hpp"

Sistema::Sistema(int filas, int columnas): matriz(filas, columnas), recaudado(0) {}

int Sistema::leer_entero(std::string mensaje){
    int valor;
    std::cout << mensaje;
    while(!(std::cin >> valor)){
        if(std::cin.eof()){ // Si se cierra la entrada se toma como salir
            return 0;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Debe ingresar un número entero: ";
    }
    return valor;
}

std::string Sistema::leer_texto(std::string mensaje){
    std::string texto;
    std::cout << mensaje;
    std::cin >> std::ws; // Descarta el salto de línea que deja cin >>
    std::getline(std::cin, texto);
    return texto;
}

void Sistema::mostrar_error(const std::exception& e){
    std::string tipo = "error";
    if(dynamic_cast<const std::invalid_argument*>(&e)){
        tipo = "invalid_argument";
    }
    else if(dynamic_cast<const std::out_of_range*>(&e)){
        tipo = "out_of_range";
    }
    else if(dynamic_cast<const std::overflow_error*>(&e)){
        tipo = "overflow_error";
    }
    else if(dynamic_cast<const std::underflow_error*>(&e)){
        tipo = "underflow_error";
    }
    else if(dynamic_cast<const std::logic_error*>(&e)){
        tipo = "logic_error";
    }
    std::cout << "Error (" << tipo << "): " << e.what() << std::endl;
}

void Sistema::mostrar_porcentaje(double porcentaje){
    std::ios::fmtflags formato = std::cout.flags();
    std::streamsize precision = std::cout.precision();
    std::cout << "Porcentaje de ocupación: " << std::fixed << std::setprecision(2) << porcentaje << "%" << std::endl;
    std::cout.flags(formato);
    std::cout.precision(precision);
}

// No se permiten placas repetidas entre la espera y los estacionados
void Sistema::registrar_solicitud(std::string placa, std::string propietario, int tipo){
    if(estacionamiento.buscar(placa) != nullptr){
        throw std::logic_error("La placa ya está registrada.");
    }
    espera.registrar(placa, propietario, tipo);
    std::cout << "Solicitud " << espera.buscar(placa)->get_num() << " registrada correctamente." << std::endl;
}

void Sistema::cancelar_solicitud(std::string placa){
    Vehiculo* solicitud = espera.buscar(placa);
    if(solicitud == nullptr){
        throw std::out_of_range("Solicitud no encontrada.");
    }
    int num = solicitud->get_num();
    espera.cancelar(placa);
    std::cout << "Solicitud " << num << " cancelada correctamente." << std::endl;
    std::cout << "Pendientes: " << espera.pendientes() << std::endl;
}

// Se valida todo antes de modificar: si algo falla, la solicitud sigue en espera y nada cambia
void Sistema::procesar_solicitud(){
    Vehiculo& solicitud = espera.primera(); // underflow_error si no hay solicitudes
    int f, c;
    matriz.buscar_espacio(f, c); // overflow_error si no hay espacios
    if(encargados.vacia()){
        throw std::logic_error("No existen encargados disponibles.");
    }
    Encargado& encargado = encargados.siguiente();
    estacionamiento.registrar(Estacionado(solicitud, f, c, encargado.get_id())); // logic_error si la placa ya está
    matriz.ocupar(f, c);
    std::cout << "Solicitud: " << solicitud.get_num() << " - " << solicitud.get_placa() << std::endl;
    std::cout << "Espacio asignado: Fila " << f + 1 << ", Columna " << c + 1 << std::endl;
    std::cout << "Encargado: " << encargado.get_nombre() << std::endl;
    encargados.asignar(); // Suma la atención y avanza el turno
    espera.procesar(); // Se retira de la espera al final (solicitud deja de ser válida aquí)
    std::cout << "Ingreso registrado correctamente." << std::endl;
    std::cout << "Siguiente encargado: " << encargados.siguiente().get_nombre() << std::endl;
}

int Sistema::calcular_monto(const Vehiculo& v, int horas) const{
    if(horas <= 0){
        throw std::invalid_argument("Las horas deben ser positivas.");
    }
    if(v.get_tipo() == 0){
        return horas * TARIFA_AUTOMOVIL;
    }
    return horas * TARIFA_MOTOCICLETA;
}

int Sistema::registrar_salida(std::string placa, int horas){
    Estacionado* vehiculo = estacionamiento.buscar(placa);
    if(vehiculo == nullptr){
        throw std::out_of_range("Vehículo no encontrado.");
    }
    int monto = calcular_monto(vehiculo->get_vehiculo(), horas); // invalid_argument si horas <= 0
    int f = vehiculo->get_fila();
    int c = vehiculo->get_columna();
    matriz.liberar(f, c);
    estacionamiento.abandonar(placa);
    recaudado += monto;
    std::cout << "COMPROBANTE DE SALIDA" << std::endl;
    std::cout << "Placa: " << placa << std::endl;
    std::cout << "Horas de permanencia: " << horas << std::endl;
    std::cout << "Tarifa por hora: " << monto / horas << " colones" << std::endl;
    std::cout << "Monto a pagar: " << monto << " colones" << std::endl;
    std::cout << "Espacio (" << f + 1 << "," << c + 1 << ") liberado." << std::endl;
    std::cout << "Vehículo retirado del registro." << std::endl;
    return monto;
}

int Sistema::get_recaudado() const{
    return recaudado;
}

void Sistema::mostrar_matriz(){
    std::cout << "ESTADO DEL ESTACIONAMIENTO" << std::endl;
    matriz.mostrar();
}

void Sistema::reportes(){
    std::cout << "REPORTE GENERAL" << std::endl;
    std::cout << "Solicitudes pendientes: " << espera.pendientes() << std::endl;
    std::cout << "Vehículos estacionados: " << estacionamiento.estacionados() << std::endl;
    std::cout << "Automóviles estacionados: " << estacionamiento.cantidad(0) << std::endl;
    std::cout << "Motocicletas estacionadas: " << estacionamiento.cantidad(1) << std::endl;
    std::cout << "Espacios ocupados: " << matriz.ocupados() << std::endl;
    std::cout << "Espacios libres: " << matriz.libres() << std::endl;
    mostrar_porcentaje(matriz.porcentaje());
    std::cout << "Total recaudado: " << recaudado << " colones" << std::endl;
    std::cout << std::endl << "VEHÍCULOS ATENDIDOS POR ENCARGADO" << std::endl;
    encargados.mostrar();
}

void Sistema::menu(){
    int opcion = -1;
    while(opcion != 0){
        std::cout << std::endl << "=========================================" << std::endl;
        std::cout << " SISTEMA DE ESTACIONAMIENTO" << std::endl;
        std::cout << "=========================================" << std::endl;
        std::cout << "1. Gestionar solicitudes de ingreso" << std::endl;
        std::cout << "2. Procesar siguiente solicitud" << std::endl;
        std::cout << "3. Consultar vehículos estacionados" << std::endl;
        std::cout << "4. Registrar salida de vehículo" << std::endl;
        std::cout << "5. Gestionar encargados" << std::endl;
        std::cout << "6. Mostrar matriz del estacionamiento" << std::endl;
        std::cout << "7. Generar reportes" << std::endl;
        std::cout << "0. Salir" << std::endl;
        opcion = leer_entero("Seleccione una opción: ");
        try{
            switch(opcion){
                case 1:
                    menu_solicitudes();
                    break;
                case 2:
                    procesar_solicitud();
                    break;
                case 3:
                    menu_estacionados();
                    break;
                case 4:
                    menu_salida();
                    break;
                case 5:
                    menu_encargados();
                    break;
                case 6:
                    mostrar_matriz();
                    break;
                case 7:
                    reportes();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Opción inválida." << std::endl;
            }
        }
        catch(const std::exception& e){
            mostrar_error(e);
        }
    }
}

void Sistema::menu_solicitudes(){
    int opcion = -1;
    while(opcion != 0){
        std::cout << std::endl << "GESTIÓN DE SOLICITUDES" << std::endl;
        std::cout << "1. Registrar solicitud" << std::endl;
        std::cout << "2. Mostrar solicitudes pendientes" << std::endl;
        std::cout << "3. Consultar solicitud por placa" << std::endl;
        std::cout << "4. Cancelar solicitud" << std::endl;
        std::cout << "5. Cantidad de solicitudes pendientes" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leer_entero("Seleccione una opción: ");
        try{
            switch(opcion){
                case 1:{
                    std::string placa = leer_texto("Placa: ");
                    if(espera.buscar(placa) != nullptr || estacionamiento.buscar(placa) != nullptr){
                        throw std::logic_error("La placa ya está registrada."); // Se valida antes de pedir lo demás
                    }
                    std::string propietario = leer_texto("Propietario: ");
                    int tipo = leer_entero("Tipo (0 = Automóvil, 1 = Motocicleta): ");
                    registrar_solicitud(placa, propietario, tipo);
                    break;
                }
                case 2:
                    espera.mostrar();
                    break;
                case 3:
                    espera.consultar(leer_texto("Placa: "));
                    break;
                case 4:
                    cancelar_solicitud(leer_texto("Placa: "));
                    break;
                case 5:
                    std::cout << "Solicitudes pendientes: " << espera.pendientes() << std::endl;
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Opción inválida." << std::endl;
            }
        }
        catch(const std::exception& e){
            mostrar_error(e);
        }
    }
}

void Sistema::menu_estacionados(){
    int opcion = -1;
    while(opcion != 0){
        std::cout << std::endl << "VEHÍCULOS ESTACIONADOS" << std::endl;
        std::cout << "1. Recorrer en orden directo" << std::endl;
        std::cout << "2. Recorrer en orden inverso" << std::endl;
        std::cout << "3. Buscar vehículo por placa" << std::endl;
        std::cout << "4. Total de vehículos estacionados" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leer_entero("Seleccione una opción: ");
        try{
            switch(opcion){
                case 1:
                    estacionamiento.mostrar();
                    break;
                case 2:
                    estacionamiento.mostrar_inverso();
                    break;
                case 3:
                    estacionamiento.consultar(leer_texto("Placa: "));
                    break;
                case 4:
                    std::cout << "Vehículos estacionados: " << estacionamiento.estacionados() << std::endl;
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Opción inválida." << std::endl;
            }
        }
        catch(const std::exception& e){
            mostrar_error(e);
        }
    }
}

void Sistema::menu_salida(){
    std::string placa = leer_texto("Placa: ");
    Estacionado* vehiculo = estacionamiento.buscar(placa);
    if(vehiculo == nullptr){
        throw std::out_of_range("Vehículo no encontrado.");
    }
    std::cout << "Propietario: " << vehiculo->get_vehiculo().get_propietario() << std::endl;
    std::cout << "Tipo: " << vehiculo->get_vehiculo().texto_tipo() << std::endl;
    int horas = leer_entero("Horas de permanencia: ");
    registrar_salida(placa, horas);
}

void Sistema::menu_encargados(){
    int opcion = -1;
    while(opcion != 0){
        std::cout << std::endl << "GESTIÓN DE ENCARGADOS" << std::endl;
        std::cout << "1. Registrar encargado" << std::endl;
        std::cout << "2. Eliminar encargado" << std::endl;
        std::cout << "3. Consultar siguiente encargado" << std::endl;
        std::cout << "4. Avanzar turno" << std::endl;
        std::cout << "5. Mostrar encargados" << std::endl;
        std::cout << "6. Mostrar orden de rotación" << std::endl;
        std::cout << "0. Volver" << std::endl;
        opcion = leer_entero("Seleccione una opción: ");
        try{
            switch(opcion){
                case 1:{
                    std::string id = leer_texto("ID: ");
                    std::string nombre = leer_texto("Nombre: ");
                    encargados.registrar(id, nombre);
                    std::cout << "Encargados registrados: " << encargados.get_cantidad() << std::endl;
                    break;
                }
                case 2:{
                    std::string id = leer_texto("ID: ");
                    Encargado* encargado = encargados.buscar(id);
                    if(encargado == nullptr){
                        throw std::out_of_range("Encargado no encontrado.");
                    }
                    std::string nombre = encargado->get_nombre(); // Se guarda antes de que el nodo se elimine
                    encargados.eliminar(id);
                    std::cout << "Encargado " << nombre << " eliminado." << std::endl;
                    break;
                }
                case 3:
                    std::cout << "Próximo encargado: " << encargados.siguiente().get_nombre() << std::endl;
                    break;
                case 4:
                    encargados.avanzar();
                    std::cout << "Próximo encargado: " << encargados.siguiente().get_nombre() << std::endl;
                    break;
                case 5:
                    encargados.mostrar();
                    break;
                case 6:
                    encargados.mostrar_rotacion();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "Opción inválida." << std::endl;
            }
        }
        catch(const std::exception& e){
            mostrar_error(e);
        }
    }
}
