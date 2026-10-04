#ifndef ORBITA_HPP
#define ORBITA_HPP
#include <string>
#include "auxiliar.hpp"

class Orbita{
    private:
        std::string codigo;
        std::string nombre;
        double altitud;
        Satelite* satelites_asignados[MAX_SATELITES];


    public:
        Orbita(std::string codigo, std::string nombre, double altitud);
        std::string get_codigo() const;
        std::string get_nombre() const;
        double get_altitud() const;
        bool asignar_satelite(Satelite* satelite);
        void mostrar_satelites();
        bool tiene_satelite(Satelite* satelite) const;
        void mostrar_orbita();
        int numero_satelites_asignados_a_orbita() const;
};

#endif
