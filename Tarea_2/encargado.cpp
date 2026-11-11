#include "encargado.hpp"

using namespace std;

Encargado::Encargado(string id, string nombre)
    : id(id), nombre(nombre), atendidos(0) {}

string Encargado::get_id() const {
    return id;
}

string Encargado::get_nombre() const {
    return nombre;
}

int Encargado::get_atendidos() const {
    return atendidos;
}

void Encargado::atender() {
    atendidos++;
}

ostream& operator<<(ostream& salida, const Encargado& encargado) {
    salida << encargado.id << ' ' << encargado.nombre << ": " << encargado.atendidos;
    return salida;
}
