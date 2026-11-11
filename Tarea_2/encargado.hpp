#ifndef ENCARGADO_HPP
#define ENCARGADO_HPP

#include <iostream>
#include <string>

class Encargado{
    private:
        std::string id;
        std::string nombre;
        int atendidos;
    public:
        Encargado(std::string id, std::string nombre);
        std::string get_id() const;
        std::string get_nombre() const;
        int get_atendidos() const;
        void atender(); // Suma un vehículo atendido
        friend std::ostream& operator<<(std::ostream& s, const Encargado& e);
};

#endif
