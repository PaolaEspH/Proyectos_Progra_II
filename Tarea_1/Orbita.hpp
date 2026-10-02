#ifndef ORBITA_HPP
#define ORBITA_HPP
#include <string>
#include "auxiliar.hpp"
#include "Satelite.hpp"
#include "EstacionTerrestre.hpp"
#include "Transmision.hpp"
#include "CentroControl.hpp"

class Orbita{
    private:
        std::string codigo;
        std::string nombre;
        double altitud;
        Satelite* arr;

    public:
        Orbita(std::string codigo, std::string nombre, double altitud, Satelite* satelites);
        std::string get_codigo() const;
        std::string get_nombre() const;
        double get_altitud() const;
};

#endif
