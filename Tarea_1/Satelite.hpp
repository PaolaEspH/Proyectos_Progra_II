#ifndef SATELITE_HPP
#define SATELITE_HPP
#include <string>
#include "auxiliar.hpp"

class Satelite{
    public:
        //Constructor tipo 1
        Satelite(std::string codigo, std::string nombre, 
            int tipo, double masa, double altitud, 
            double capacidad, double bateria, 
            double potencia, double ancho_banda);
        //Constructor tipo 2
        Satelite(std::string codigo, std::string nombre, 
            int tipo, double masa, double altitud, 
            double capacidad, double bateria, 
            double potencia, 
            double resolucion, double cobertura);
        std::string get_codigo() const;
        std::string get_nombre() const;
        int get_tipo() const;
        double get_masa() const;
        double get_altitud() const;
        double get_capacidad() const;
        double get_bateria() const;
        double get_potencia() const;
        double get_ancho_banda() const;
        double get_resolucion() const;
        double get_cobertura() const;
        std::string get_estado() const;
        double energia_disponible() const;
        bool reducir_bateria(double energia);
        double radio_orbital() const;
        double velocidad_orbital() const;
        double periodo_orbital() const;
        double periodo_orbital_minutos() const;
        void mostrar_resumen() const;
        void mostrar_satelite() const;
        Orbita* get_orbita() const;
        bool set_orbita(Orbita* orbita);
    private:
        std::string codigo;
        std::string nombre;
        int tipo;
        double masa;
        double altitud;
        double capacidad;
        double potencia;
        double ancho_banda;
        double resolucion;
        double cobertura;
        double historialBateria[MAX_MUESTRAS]; 
        double historialTemperatura[MAX_MUESTRAS]; 
        int cantidadMuestras;
        double bateria;
        Orbita* orbita;
    };

#endif
