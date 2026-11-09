#include "lista_enlazada.hpp"

int main(){
    ListaEnlazada list;
    list.mostrar();
    list.registrar("23", "1", 1);
    list.registrar("26", "2", 0);
    list.registrar("78", "3", 1);
    list.mostrar();
    list.consultar("26");
    list.consultar("ZZZ999");
    list.cancelar("78");
    list.mostrar();
    list.registrar("78", "8", 0);
    list.registrar("26", "4", 0);
    list.registrar("PA56", "5", 1);
    list.cancelar("23");
    list.mostrar();
    std::cout << "Cantidad de automóviles: " << list.cantidad(0) << std::endl;
    std::cout << "Cantidad de motocicletas: " << list.cantidad(1) << std::endl;
    std::cout << "Solicitudes pendientes: " << list.pendientes() << std::endl;
}