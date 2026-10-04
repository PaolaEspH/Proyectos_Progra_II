#include <iostream>
#include <limits>
#include "auxiliar.hpp"
#include "Satelite.hpp"
#include "Orbita.hpp"
#include "EstacionTerrestre.hpp"
#include "Transmision.hpp"
#include "CentroControl.hpp"

int main(){
    CentroControl centro;
    int opcion;
    do{
        do{
            if(std::cin.fail()){
                if(std::cin.eof()){
                    opcion = 0;
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cout << "==== CENTRO DE CONTROL SATELITAL ====" << std::endl <<
            "1. Gestión de satélites" << std::endl <<
            "2. Gestión de órbitas" << std::endl <<
            "3. Estaciones y enlaces" << std::endl <<
            "4. Telemetría" << std::endl <<
            "5. Transmisiones" << std::endl <<
            "6. Control energético" << std::endl <<
            "7. Reportes" << std::endl <<
            "0. Salir" << std::endl <<
            "Seleccione una opción: ";
        } while(!(std::cin >> opcion) || (opcion < 0) || (opcion > 7));
        switch (opcion){
            case 1: 
                centro.gestion_satelites();
                break;
            case 2:
                centro.gestion_orbitas();
                break;
            case 3:
                centro.gestion_estaciones_y_enlaces();
                break;
            case 4:
                centro.telemetria();
                break;
            case 5:
                centro.gestion_transmisiones();
                break;
            case 6:
                centro.control_energetico();
                break;
            case 7:
                centro.reportes();
                break;
            default:
                std::cout << "Hasta pronto!" << std::endl;
        }
    }while(opcion != 0);
}
