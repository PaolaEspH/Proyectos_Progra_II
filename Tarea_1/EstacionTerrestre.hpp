#ifndef ESTACIONTERRESTRE_HPP
#define ESTACIONTERRESTRE_HPP
#include <string>
#include "auxiliar.hpp"
#include "Satelite.hpp"
#include "Orbita.hpp"
#include "Transmision.hpp"
#include "CentroControl.hpp"

class EstacionTerrestre{
    private:
        std::string codigo;
        std::string nombre;
        std::string ubicacion;
        Satelite* satelites;
    public:
        EstacionTerrestre(std::string codigo, std::string nombre, std::string ubicacion, Satelite* satelites);
        std::string get_codigo() const;
        std::string get_nombre() const;
        std::string get_ubicacion() const;
};

#endif
