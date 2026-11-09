#ifndef LISTA_ENLAZADA_HPP
#define LISTA_ENLAZADA_HPP

#include "nodo.hpp"

class ListaEnlazada{
    private:
        Nodo* cabeza;
        Nodo* cola;
        int solicitudes;
    public:
        ListaEnlazada();
        void registrar(std::string placa, std::string propietario, int tipo);

        class IteradorEspera{
            private:
                Nodo* posactual;
            public:
                IteradorEspera(Nodo* posicion);
                IteradorEspera& operator++();
                bool operator!=(const IteradorEspera& otro);
                bool operator==(const IteradorEspera& otro);
                Vehiculo* operator->();
                Vehiculo& operator*();
                Nodo* get_nodo() const;
        };

        IteradorEspera begin();
        IteradorEspera end();
        void mostrar();
        void consultar(std::string placa);
        Nodo* buscar(std::string placa);
        void cancelar(std::string placa);
        int pendientes();
        int cantidad(int tipo);
};

#endif