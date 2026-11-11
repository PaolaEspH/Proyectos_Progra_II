#ifndef NODO_DOBLE_HPP
#define NODO_DOBLE_HPP

#include "estacionado.hpp"

// Nodo de la lista doble (vehículos estacionados)
class NodoDoble{
    private:
        Estacionado dato;
        NodoDoble* siguiente;
        NodoDoble* anterior;
    public:
        NodoDoble(Estacionado dato);
        NodoDoble* get_siguiente() const;
        NodoDoble* get_anterior() const;
        Estacionado& get_dato();
        void set_siguiente(NodoDoble* sig);
        void set_anterior(NodoDoble* ant);
        friend std::ostream& operator<<(std::ostream& s, const NodoDoble& nodo);
};

#endif
