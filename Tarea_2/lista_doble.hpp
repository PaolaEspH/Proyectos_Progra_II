#ifndef LISTA_DOBLE_HPP
#define LISTA_DOBLE_HPP

#include <stdexcept>
#include "nodo_doble.hpp"

class ListaDoble{
    private:
        NodoDoble* cabeza;
        NodoDoble* cola;
        NodoDoble* buscar_nodo(std::string placa);
    public:
        ListaDoble();
        ~ListaDoble();
        ListaDoble(const ListaDoble& otra) = delete; // Se prohíbe la copia (evita copia superficial)
        ListaDoble& operator=(const ListaDoble& otra) = delete;
        void registrar(Estacionado nuevo);

        class IteradorEstacionamiento{
            private:
                NodoDoble* posactual;
            public:
                IteradorEstacionamiento(NodoDoble* posicion);
                IteradorEstacionamiento& operator++();
                IteradorEstacionamiento& operator--();
                bool operator!=(const IteradorEstacionamiento& otro);
                bool operator==(const IteradorEstacionamiento& otro);
                Estacionado* operator->();
                Estacionado& operator*();
                NodoDoble* get_nodo() const;
        };

        IteradorEstacionamiento begin();
        IteradorEstacionamiento end();
        IteradorEstacionamiento rbegin();
        IteradorEstacionamiento rend();
        void mostrar();
        void mostrar_inverso();
        void consultar(std::string placa);
        Estacionado* buscar(std::string placa);
        void abandonar(std::string placa);
        int estacionados();
        int cantidad(int tipo);
};

#endif
