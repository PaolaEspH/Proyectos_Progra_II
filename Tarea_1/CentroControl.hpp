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
        int enlaces[MAX_SATELITES][MAX_ESTACIONES]; //filas son satélites, columnas estaciones (1 = enlace, 0 = sin enlace)
        int numero_satelites();
        int numero_orbitas();
        int numero_estaciones();
        int numero_transmisiones();
        double leer_double(std::string msj);
        std::string verificar_codigo_satelite();
        std::string verificar_codigo_orbita();
        std::string verificar_codigo_estacion();
        double leer_double_min_max(std::string msj, double min, double max);
        std::string leer_nombre(std::string msj);
        std::string leer_codigo(std::string msj);
        void realizar_transmision(Satelite* satelite, EstacionTerrestre* estacion);
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
        void eliminar_enlace();
        void mostrar_satelites_de_estacion();
        void mostrar_enlaces_activos();
        void telemetria();
        void gestion_transmisiones();
        int indice_satelite(std::string codigo);
        int indice_estacion(std::string codigo);
        void control_energetico();
        void reportes();
        Satelite* buscar_satelite(std::string codigo);
        Orbita* buscar_orbita(std::string codigo);
        EstacionTerrestre* buscar_estacion(std::string codigo);
        void asignar_satelite_a_orbita();
        void listar_satelites_por_orbita();
        

};

#endif
