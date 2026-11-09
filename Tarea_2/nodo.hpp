#ifndef NODO_HPP
#define NODO_HPP

#include "vehiculo.hpp"

class Nodo{
    private:
        Vehiculo dato;
        Nodo* siguiente;
        Nodo* anterior;
        std::string id_encargado;
        int fila, columna;
    public:
        Nodo(Vehiculo dato);
        Nodo* get_siguiente() const;
        Nodo* get_anterior() const;
        Vehiculo& get_dato();
        void set_siguiente(Nodo* sig);
        void set_anterior(Nodo* ant);
        friend std::ostream& operator<<(std::ostream& s, const Nodo& nodo);
};

#endif