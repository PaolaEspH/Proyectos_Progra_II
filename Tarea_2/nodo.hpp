#include "vehiculo.hpp"
class Nodo{
    private:
        Vehiculo dato;
        Nodo* siguiente;
    public:
        Nodo(Vehiculo dato);
        Nodo* get_siguiente() const;
}