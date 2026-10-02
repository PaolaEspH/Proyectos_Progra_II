#ifndef TAREA1_HPP
#define TAREA1_HPP
#include <string>

//Declaramos máximos como variables globales
const int MAX_SATELITES = 100;
const int MAX_ORBITAS = 100;
const int MAX_ESTACIONES = 100;
const int MAX_TRANSMISIONES = 100;

const int RT = 6371;
const int mu = 398600;
const double c = 299792.458;
const double PI = 3.14159265;


class Satelite{
    public:
        //Constructor tipo 1
        Satelite(int codigo, std::string nombre, 
            int tipo, double masa, double altitud, 
            double capacidad, double bateria, 
            double potencia, double ancho_banda);
        //Constructor tipo 2
        Satelite(int codigo, std::string nombre, 
            int tipo, double masa, double altitud, 
            double capacidad, double bateria, 
            double potencia, 
            double resolucion, double cobertura);
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
        double historialBateria[12]; 
        double historialTemperatura[12]; 
        int cantidadMuestras;
        double bateria;
        void estado_energetico(); 
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
        Satelite* satelites[MAX_SATELITES];
        Orbita* orbitas[MAX_ORBITAS];
        EstacionTerrestre* estaciones[MAX_ESTACIONES];
        Transmision* transmisiones[MAX_TRANSMISIONES];
        bool enlaces[MAX_SATELITES][MAX_ESTACIONES]; //filas son satélites, columnas estaciones
    public:
        CentroControl();
};
#endif