#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

class Matriz{
    private:
        int** m; // 0: libre, 1: ocupado
        int filas;
        int columnas;
        void validar_posicion(int f, int c) const;
    public:
        Matriz(int f, int c);
        ~Matriz();
        Matriz(const Matriz& otra) = delete; // Se prohíbe la copia (evita copia superficial)
        Matriz& operator=(const Matriz& otra) = delete;
        void inicializar();
        int get_filas() const;
        int get_columnas() const;
        int get_estado(int f, int c) const;
        bool hay_espacio() const;
        void buscar_espacio(int& f, int& c) const;
        void ocupar(int f, int c);
        void liberar(int f, int c);
        void mostrar() const;
        int total() const;
        int ocupados() const;
        int libres() const;
        double porcentaje() const;
};

#endif
