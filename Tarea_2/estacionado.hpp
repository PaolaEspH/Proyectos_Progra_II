#ifndef ESTACIONADO_HPP
#define ESTACIONADO_HPP

#include "vehiculo.hpp"

// Vehículo que ya ingresó: guarda la solicitud original, su espacio y el encargado que lo autorizó
class Estacionado{
    private:
        Vehiculo vehiculo;
        int fila, columna; // Desde 0, se muestran desde 1
        std::string id_encargado;
    public:
        Estacionado(Vehiculo vehiculo, int fila, int columna, std::string id_encargado);
        Vehiculo& get_vehiculo();
        std::string get_placa() const;
        int get_tipo() const;
        int get_fila() const;
        int get_columna() const;
        std::string get_id_encargado() const;
        friend std::ostream& operator<<(std::ostream& s, const Estacionado& e);
};

#endif
