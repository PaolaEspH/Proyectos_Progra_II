#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <stdexcept>
#include "matriz.hpp"
#include "lista_circular.hpp"
#include "lista_doble.hpp"
#include "lista_enlazada.hpp"

class Sistema{
    private:
        Matriz matriz; // Va primero: si las dimensiones son inválidas no se construye nada más
        ListaCircular encargados;
        ListaDoble estacionamiento;
        ListaEnlazada espera;
        int recaudado;
        static const int TARIFA_AUTOMOVIL = 900;
        static const int TARIFA_MOTOCICLETA = 500;
        static void mostrar_error(const std::exception& e);
        static void mostrar_porcentaje(double porcentaje);
    public:
        Sistema(int filas, int columnas);
        Sistema(const Sistema& otro) = delete;
        Sistema& operator=(const Sistema& otro) = delete;
        static int leer_entero(std::string mensaje);
        static std::string leer_texto(std::string mensaje);

        // Operaciones (sin lectura de datos, se pueden probar directamente)
        void registrar_solicitud(std::string placa, std::string propietario, int tipo);
        void cancelar_solicitud(std::string placa);
        void procesar_solicitud();
        int registrar_salida(std::string placa, int horas);
        int calcular_monto(const Vehiculo& v, int horas) const;
        int get_recaudado() const;
        void mostrar_matriz();
        void reportes();

        // Menús
        void menu();
        void menu_solicitudes(); // Opción 1
        void menu_estacionados(); // Opción 3
        void menu_salida(); // Opción 4
        void menu_encargados(); // Opción 5
};

#endif
