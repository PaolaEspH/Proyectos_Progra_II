#ifndef LISTA_CIRCULAR_HPP
#define LISTA_CIRCULAR_HPP

#include <stdexcept>
#include "encargado.hpp"

class NodoEncargado{
    private:
        Encargado dato;
        NodoEncargado* siguiente;
    public:
        NodoEncargado(Encargado dato);
        NodoEncargado* get_siguiente() const;
        Encargado& get_dato();
        void set_siguiente(NodoEncargado* sig);
};

class ListaCircular{
    private:
        NodoEncargado* cabeza;
        NodoEncargado* cola; // cola->siguiente == cabeza
        NodoEncargado* turno; // Encargado que atenderá la siguiente solicitud
        int cantidad;
    public:
        ListaCircular();
        ~ListaCircular();
        ListaCircular(const ListaCircular& otra) = delete; // Se prohíbe la copia (evita copia superficial)
        ListaCircular& operator=(const ListaCircular& otra) = delete;
        void registrar(std::string id, std::string nombre); // logic_error si el id ya existe
        void eliminar(std::string id); // out_of_range si no existe; contemplar lista vacía, un nodo, cabeza, cola y turno
        Encargado& siguiente(); // Consultar quién atiende la siguiente solicitud; logic_error si está vacía
        std::string asignar(); // Suma una atención al del turno, avanza el turno y retorna su id; logic_error si está vacía
        void avanzar();
        bool vacia() const;
        int get_cantidad() const;
        Encargado* buscar(std::string id);

        class IteradorCircular{
            private:
                NodoEncargado* posactual;
                int restantes; // Nodos que faltan por recorrer, evita el ciclo infinito
            public:
                IteradorCircular(NodoEncargado* posicion, int restantes);
                IteradorCircular& operator++();
                bool operator!=(const IteradorCircular& otro);
                bool operator==(const IteradorCircular& otro);
                Encargado* operator->();
                Encargado& operator*();
        };

        IteradorCircular begin(); // IteradorCircular(cabeza, cantidad)
        IteradorCircular end(); // IteradorCircular(nullptr, 0)
        void mostrar(); // Encargados y cantidad de vehículos atendidos
        void mostrar_rotacion(); // Ana -> Luis -> Maria -> Ana
};

#endif
