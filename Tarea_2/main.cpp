#include "sistema.hpp"

int main(){
    std::cout << "CONFIGURACIÓN INICIAL" << std::endl;
    Sistema* sistema = nullptr;
    while(sistema == nullptr){
        int filas = Sistema::leer_entero("Ingrese cantidad de filas: ");
        int columnas = Sistema::leer_entero("Ingrese cantidad de columnas: ");
        if(std::cin.eof()){
            return 0;
        }
        try{
            sistema = new Sistema(filas, columnas);
            std::cout << "Estacionamiento creado correctamente." << std::endl;
            std::cout << "Espacios disponibles: " << filas * columnas << std::endl;
        }
        catch(const std::invalid_argument& e){
            std::cout << "Error (invalid_argument): " << e.what() << std::endl;
        }
    }
    sistema->menu();
    delete sistema;
    std::cout << "Memoria liberada. Programa finalizado." << std::endl;
    return 0;
}
