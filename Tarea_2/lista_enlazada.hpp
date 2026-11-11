#ifndef LISTA_ENLAZADA_HPP
#define LISTA_ENLAZADA_HPP

#include <stdexcept>
#include "nodo.hpp"

class ListaEnlazada{
    private:
        Nodo* cabeza;
        Nodo* cola;
        int solicitudes; //Es num de solicitudes hechas en el día, no contempla canceladas ni resueltas
    public:
        ListaEnlazada();
        ~ListaEnlazada();
        ListaEnlazada(const ListaEnlazada& otra) = delete; // Se prohíbe la copia (evita copia superficial)
        ListaEnlazada& operator=(const ListaEnlazada& otra) = delete;
        void registrar(std::string placa, std::string propietario, int tipo);
        Vehiculo& primera();
        void procesar();

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
        Vehiculo* buscar(std::string placa);
        void cancelar(std::string placa);
        int pendientes();
        int cantidad(int tipo);
};

#endif
