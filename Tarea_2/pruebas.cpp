#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include "lista_circular.hpp"
#include "lista_enlazada.hpp"
#include "lista_doble.hpp"
#include "matriz.hpp"

using namespace std;

std::string placas_espera(ListaEnlazada& lista){
    std::string texto = "";
    for(ListaEnlazada::IteradorEspera it = lista.begin(); it != lista.end(); ++it){
        texto += (*it).get_placa() + " ";
    }
    return texto;
}

std::string placas_directo(ListaDoble& lista){
    std::string texto = "";
    for(ListaDoble::IteradorEstacionamiento it = lista.begin(); it != lista.end(); ++it){
        texto += (*it).get_placa() + " ";
    }
    return texto;
}

std::string placas_inverso(ListaDoble& lista){
    std::string texto = "";
    for(ListaDoble::IteradorEstacionamiento it = lista.rbegin(); it != lista.rend(); --it){
        texto += it->get_placa() + " ";
    }
    return texto;
}

// Caso 1: registrar una solicitud válida
void prueba_registrar_solicitud(){
    ListaEnlazada lista;
    lista.registrar("ABC123", "Carlos", 0);
    lista.registrar("MOTO45", "Daniela", 1);
    assert(placas_espera(lista) == "ABC123 MOTO45 ");
    assert(lista.pendientes() == 2);
    assert(lista.buscar("MOTO45")->get_num() == 2);
    assert(lista.cantidad(0) == 1 && lista.cantidad(1) == 1);
}

// Caso 2: cancelar la primera solicitud
void prueba_cancelar_primera(){
    ListaEnlazada lista;
    lista.registrar("A", "1", 0);
    lista.registrar("B", "2", 0);
    lista.cancelar("A");
    assert(lista.primera().get_placa() == "B");
    assert(placas_espera(lista) == "B ");
    lista.cancelar("B");
    assert(lista.pendientes() == 0);
    lista.registrar("C", "3", 1); // La cola también quedó bien actualizada
    assert(placas_espera(lista) == "C ");
}

// Caso 3: cancelar una solicitud intermedia y la última
void prueba_cancelar_intermedia(){
    ListaEnlazada lista;
    lista.registrar("A", "1", 0);
    lista.registrar("B", "2", 0);
    lista.registrar("C", "3", 0);
    lista.cancelar("B");
    assert(placas_espera(lista) == "A C ");
    lista.cancelar("C");
    lista.registrar("D", "4", 0); // Si la cola no se actualizó, D se perdería
    assert(placas_espera(lista) == "A D ");
    bool lanzo = false;
    try{ lista.cancelar("NOEXISTE"); }
    catch(const std::out_of_range&){ lanzo = true; }
    assert(lanzo && lista.pendientes() == 2);
}

// Caso 11: placa duplicada y datos inválidos
void prueba_placa_duplicada(){
    ListaEnlazada lista;
    lista.registrar("ABC123", "Carlos", 0);
    bool lanzo = false;
    try{ lista.registrar("ABC123", "Otro", 1); }
    catch(const std::logic_error&){ lanzo = true; }
    assert(lanzo && lista.pendientes() == 1);
    lanzo = false;
    try{ lista.registrar("", "Otro", 1); }
    catch(const std::invalid_argument&){ lanzo = true; }
    assert(lanzo);
    lanzo = false;
    try{ lista.registrar("XYZ", "Otro", 5); }
    catch(const std::invalid_argument&){ lanzo = true; }
    assert(lanzo && lista.pendientes() == 1);
}

// Caso 13 y 14: procesar y recorrer listas vacías
void prueba_listas_vacias(){
    ListaEnlazada espera;
    ListaDoble estacionados;
    assert(espera.begin() == espera.end() && espera.pendientes() == 0);
    assert(estacionados.begin() == estacionados.end());
    assert(estacionados.rbegin() == estacionados.rend());
    assert(estacionados.estacionados() == 0 && estacionados.cantidad(0) == 0);
    bool lanzo = false;
    try{ espera.procesar(); }
    catch(const std::underflow_error&){ lanzo = true; }
    assert(lanzo);
    lanzo = false;
    try{ espera.primera(); }
    catch(const std::underflow_error&){ lanzo = true; }
    assert(lanzo);
}

// Procesar retira en el mismo orden en que se registraron
void prueba_procesar_orden(){
    ListaEnlazada lista;
    lista.registrar("A", "1", 0);
    lista.registrar("B", "2", 1);
    assert(lista.primera().get_placa() == "A");
    lista.procesar();
    assert(lista.primera().get_placa() == "B");
    lista.procesar();
    assert(lista.pendientes() == 0);
    lista.registrar("C", "3", 0); // La cola quedó en nullptr y se puede volver a usar
    assert(placas_espera(lista) == "C ");
}

// Caso 5: recorrer la lista doble en ambos sentidos
void prueba_recorrido_doble(){
    ListaDoble lista;
    lista.registrar(Estacionado(Vehiculo("ABC123", "Carlos", 0, 1), 0, 0, "E01"));
    lista.registrar(Estacionado(Vehiculo("MOTO45", "Daniela", 1, 2), 0, 1, "E02"));
    lista.registrar(Estacionado(Vehiculo("JKL555", "Sofia", 0, 4), 1, 0, "E03"));
    assert(placas_directo(lista) == "ABC123 MOTO45 JKL555 ");
    assert(placas_inverso(lista) == "JKL555 MOTO45 ABC123 ");
    assert(lista.estacionados() == 3 && lista.cantidad(0) == 2 && lista.cantidad(1) == 1);
    Estacionado* e = lista.buscar("MOTO45");
    assert(e != nullptr && e->get_fila() == 0 && e->get_columna() == 1 && e->get_id_encargado() == "E02");
    assert(lista.buscar("NOEXISTE") == nullptr);
    bool lanzo = false;
    try{ lista.registrar(Estacionado(Vehiculo("ABC123", "Otro", 0, 9), 1, 1, "E01")); }
    catch(const std::logic_error&){ lanzo = true; }
    assert(lanzo && lista.estacionados() == 3);
}

// Caso 4: eliminar de la lista doble al inicio, en medio y al final
void prueba_eliminar_doble(){
    ListaDoble lista;
    lista.registrar(Estacionado(Vehiculo("A", "1", 0, 1), 0, 0, "E01"));
    lista.registrar(Estacionado(Vehiculo("B", "2", 0, 2), 0, 1, "E01"));
    lista.registrar(Estacionado(Vehiculo("C", "3", 0, 3), 0, 2, "E01"));
    lista.registrar(Estacionado(Vehiculo("D", "4", 0, 4), 0, 3, "E01"));
    lista.abandonar("B"); // medio
    assert(placas_directo(lista) == "A C D " && placas_inverso(lista) == "D C A ");
    lista.abandonar("A"); // inicio
    assert(placas_directo(lista) == "C D " && placas_inverso(lista) == "D C ");
    lista.abandonar("D"); // final
    assert(placas_directo(lista) == "C " && placas_inverso(lista) == "C ");
    lista.abandonar("C"); // único
    assert(lista.begin() == lista.end() && lista.rbegin() == lista.rend());
    bool lanzo = false;
    try{ lista.abandonar("NOEXISTE"); }
    catch(const std::out_of_range&){ lanzo = true; }
    assert(lanzo);
}

// Matriz: dimensiones inválidas y posiciones fuera de rango
void prueba_matriz_validaciones(){
    bool lanzo = false;
    try{ Matriz m(0, 3); }
    catch(const std::invalid_argument&){ lanzo = true; }
    assert(lanzo);
    lanzo = false;
    try{ Matriz m(2, -1); }
    catch(const std::invalid_argument&){ lanzo = true; }
    assert(lanzo);
    Matriz m(2, 3);
    assert(m.total() == 6 && m.libres() == 6 && m.ocupados() == 0 && m.porcentaje() == 0);
    lanzo = false;
    try{ m.ocupar(2, 0); }
    catch(const std::out_of_range&){ lanzo = true; }
    assert(lanzo);
    lanzo = false;
    try{ m.get_estado(0, -1); }
    catch(const std::out_of_range&){ lanzo = true; }
    assert(lanzo);
    lanzo = false;
    try{ m.liberar(0, 0); } // Liberar un espacio que ya está libre
    catch(const std::logic_error&){ lanzo = true; }
    assert(lanzo);
}

// Caso 8 y 9: llenar la matriz, 100 % y overflow; liberar reutiliza el primer espacio
void prueba_matriz_llena(){
    Matriz m(2, 2);
    int f, c;
    for(int i = 0; i < 4; i++){
        m.buscar_espacio(f, c);
        assert(f == i / 2 && c == i % 2); // Recorre filas de izquierda a derecha
        m.ocupar(f, c);
    }
    assert(m.porcentaje() == 100 && m.libres() == 0 && !m.hay_espacio());
    bool lanzo = false;
    try{ m.buscar_espacio(f, c); }
    catch(const std::overflow_error&){ lanzo = true; }
    assert(lanzo);
    m.liberar(0, 0);
    assert(m.get_estado(0, 0) == 0 && m.porcentaje() == 75);
    m.buscar_espacio(f, c);
    assert(f == 0 && c == 0);
}

bool prueba_rotacion_encargados() {
    ListaCircular lista;
    lista.registrar("E01", "Ana");
    lista.registrar("E02", "Luis");
    lista.registrar("E03", "Maria");

    Encargado& ana = lista.siguiente();
    lista.asignar();
    lista.asignar();
    lista.asignar();
    string id = lista.asignar();
    if (id != "E01" || ana.get_atendidos() != 2 || lista.siguiente().get_id() != "E02") {
        cout << "Falló la prueba de rotación de encargados." << endl;
        return false;
    }
    return true;
}

bool prueba_eliminar_encargados() {
    ListaCircular lista;
    lista.registrar("E01", "Ana");
    lista.registrar("E02", "Luis");
    lista.registrar("E03", "Maria");

    lista.avanzar();
    lista.eliminar("E02");
    if (lista.siguiente().get_id() != "E03" || lista.get_cantidad() != 2) {
        cout << "Falló la prueba al eliminar al encargado en turno." << endl;
        return false;
    }

    lista.avanzar();
    if (lista.siguiente().get_id() != "E01") {
        cout << "Falló la rotación después de eliminar al encargado." << endl;
        return false;
    }
    return true;
}

int main(){
    prueba_registrar_solicitud();
    prueba_cancelar_primera();
    prueba_cancelar_intermedia();
    prueba_placa_duplicada();
    prueba_listas_vacias();
    prueba_procesar_orden();
    prueba_recorrido_doble();
    prueba_eliminar_doble();
    prueba_matriz_validaciones();
    prueba_matriz_llena();
    if (!prueba_rotacion_encargados()) {
        return 1;
    }
    if (!prueba_eliminar_encargados()) {
        return 1;
    }
    cout << "Las 12 pruebas pasaron correctamente." << endl;
    return 0;
}
