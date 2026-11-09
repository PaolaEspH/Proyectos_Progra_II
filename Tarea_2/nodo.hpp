#ifndef NODO_HPP
#define NODO_HPP

#include "vehiculo.hpp"

class Nodo{
    private:
        Vehiculo dato;
        Nodo* siguiente;
    public:
        Nodo(Vehiculo dato);
        Nodo* get_siguiente() const;
        Vehiculo& get_dato();
        void set_siguiente(Nodo* sig);
        friend std::ostream& operator<<(std::ostream& s, const Nodo& nodo);
};

#endif