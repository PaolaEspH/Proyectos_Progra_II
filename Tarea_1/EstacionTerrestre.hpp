#ifndef ESTACIONTERRESTRE_HPP
#define ESTACIONTERRESTRE_HPP
#include <string>
#include "auxiliar.hpp"

class EstacionTerrestre{
    private:
        std::string codigo;
        std::string nombre;
        std::string ubicacion;
        Satelite* satelites[MAX_SATELITES];
    public:
        EstacionTerrestre(std::string codigo, std::string nombre, std::string ubicacion);
        std::string get_codigo() const;
        std::string get_nombre() const;
        std::string get_ubicacion() const;
        bool agregar_satelite(Satelite* satelite);
        bool eliminar_satelite(Satelite* satelite);
        bool tiene_satelite(Satelite* satelite) const;
        int numero_satelites_enlazados() const;
        void mostrar_satelites();
        void mostrar_estacion();
};

#endif
