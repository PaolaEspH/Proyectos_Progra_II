#ifndef TRANSMISION_HPP
#define TRANSMISION_HPP
#include <string>
#include "auxiliar.hpp"

class Transmision{
    private:
        double ancho_banda;
        double potencia;
        double duracion;
        double energia;
        double tiempo;
    public:
        Transmision(double ancho_banda, double potencia, double duracion, double energia, double tiempo);

};

#endif
