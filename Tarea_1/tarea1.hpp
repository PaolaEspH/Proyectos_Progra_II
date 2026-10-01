#ifndef TAREA1_HPP
#define TAREA1_HPP
#include <string>

class Satelite{
    public:
        Satelite(int codigo, std::string nombre, 
            int tipo, double masa, double altitud, 
            double capacidad, double potencia, 
            double ancho_banda, double resolucion, 
            double cobertura);
    private:
        int codigo;
        std::string nombre;
        int tipo;
        double masa;
        double altitud;
        double capacidad;
        double potencia;
        double ancho_banda;
        double resolucion;
        double cobertura;
    };

class Orbita{
    private:
        int codigo;
        std::string nombre;
        double altitud;
        Satelite* arr;

    public:
        Orbita(int codigo, std::string nombre, double altitud, Satelite* satelites);
};

class EstacionTerrestre{
    private:
        int codigo;
        std::string nombre;
        std::string ubicacion;
        Satelite* satelites;
    public:
        EstacionTerrestre(int codigo, std::string nombre, std::string ubicacion, Satelite* satelites);
};

class Transmision{
    private:
        double ancho_banda;
        double potencia;
        double duracion;
        double energia;
        double tiempo;
    public:
        //Falta datos transferidos porque no sé qué tipo es
        Transmision(double ancho_banda, double potencia, double duracion, double energia, double tiempo);

};

class CentroControl{
    private:
        Satelite* satelites;
        Orbita* orbitas;
        EstacionTerrestre* estaciones;
        Transmision* transmisiones;
        bool** enlaces;
    public:
        CentroControl();

};
#endif