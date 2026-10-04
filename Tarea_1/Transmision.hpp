#ifndef TRANSMISION_HPP
#define TRANSMISION_HPP
#include <string>
#include "auxiliar.hpp"

class Transmision{
    private:
        Satelite* sateliteAsignado;
        EstacionTerrestre* estacionDestino;
        double datos;
        double ancho_banda;
        double potencia;
        double distancia;
        double duracion;
        double energia;
        double tiempo;
    public:
        Transmision(Satelite* sateliteAsignado, EstacionTerrestre* estacionDestino,
                    double datos, double ancho_banda, double potencia);
        Satelite* get_satelite() const;
        EstacionTerrestre* get_estacion() const;
        double get_datos() const;
        double get_ancho_banda() const;
        double get_potencia() const;
        double get_duracion() const;
        double get_energia() const;
        double get_tiempo() const;
        void mostrar_transmision();
    private:
        double duracion_transmision();
        double energia_consumida();
        double tiempo_propagacion();
};

#endif
