#ifndef SATELITE_HPP
#define SATELITE_HPP
#include <string>
#include "auxiliar.hpp"
#include "Orbita.hpp"
#include "EstacionTerrestre.hpp"
#include "Transmision.hpp"
#include "CentroControl.hpp"

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
        void mostrar_satelite();
        Orbita* get_orbita() const;
        void set_orbita(Orbita* orbita);
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
        double historialBateria[12]; 
        double historialTemperatura[12]; 
        int cantidadMuestras;
        double bateria;
        void estado_energetico();
        double radio_orbital();
        double velocidad_orbital();
        double periodo_orbital();
        Orbita* orbita;
    };

#endif
