#ifndef CENTROCONTROL_HPP
#define CENTROCONTROL_HPP
#include <string>
#include "auxiliar.hpp"
#include "Satelite.hpp"
#include "Orbita.hpp"
#include "EstacionTerrestre.hpp"
#include "Transmision.hpp"

class CentroControl{
    private:
        Satelite* satelites[MAX_SATELITES];
        Orbita* orbitas[MAX_ORBITAS];
        EstacionTerrestre* estaciones[MAX_ESTACIONES];
        Transmision* transmisiones[MAX_TRANSMISIONES];
        bool enlaces[MAX_SATELITES][MAX_ESTACIONES]; //filas son satélites, columnas estaciones
        int numero_satelites();
        int numero_orbitas();
        int numero_estaciones();
        int numero_transmisiones();
        double leer_double(std::string msj);
        std::string verificar_codigo_satelite();
        std::string verificar_codigo_orbita();
        std::string verificar_codigo_estacion();
        double leer_double_min_max(std::string msj, double min, double max);
        public:
        CentroControl();
        ~CentroControl();
        void gestion_satelites();
        void registrar_satelite();
        void listar_satelites();
        void gestion_orbitas();
        void registrar_orbita();
        void gestion_estaciones_y_enlaces();
        void mostrar_matriz_enlaces();
        void registrar_estacion();
        void registrar_enlace();
        void telemetria();
        void gestion_transmisiones();
        void control_energetico();
        void reportes();
        Satelite* buscar_satelite(std::string codigo);
        Orbita* buscar_orbita(std::string codigo);
        EstacionTerrestre* buscar_estacion(std::string codigo);
        void asignar_satelite_a_orbita();
        void listar_satelites_por_orbita();
        

};

#endif
