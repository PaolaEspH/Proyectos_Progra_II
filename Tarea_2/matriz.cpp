#include "matriz.hpp"

Matriz::Matriz(int f, int c){
    if(f <= 0 || c <= 0){
        throw std::invalid_argument("Las dimensiones del estacionamiento deben ser positivas.");
    }
    filas = f;
    columnas = c;
    m = new int*[filas];
    for(int i = 0; i < filas; i++){
        m[i] = new int[columnas];
    }
    inicializar();
}

Matriz::~Matriz(){
    for(int i = 0; i < filas; i++){
        delete[] m[i];
    }
    delete[] m;
}

void Matriz::inicializar(){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            m[i][j] = 0;
        }
    }
}

void Matriz::validar_posicion(int f, int c) const{
    if(f < 0 || f >= filas || c < 0 || c >= columnas){
        throw std::out_of_range("La posición no existe en el estacionamiento.");
    }
}

int Matriz::get_filas() const{
    return filas;
}

int Matriz::get_columnas() const{
    return columnas;
}

int Matriz::get_estado(int f, int c) const{
    validar_posicion(f, c);
    return m[f][c];
}

bool Matriz::hay_espacio() const{
    return libres() > 0;
}

// Primer espacio libre recorriendo filas de izquierda a derecha (posiciones desde 0)
void Matriz::buscar_espacio(int& f, int& c) const{
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            if(m[i][j] == 0){
                f = i;
                c = j;
                return;
            }
        }
    }
    throw std::overflow_error("No hay espacios disponibles.");
}

void Matriz::ocupar(int f, int c){
    validar_posicion(f, c);
    if(m[f][c] == 1){
        throw std::logic_error("El espacio ya está ocupado.");
    }
    m[f][c] = 1;
}

void Matriz::liberar(int f, int c){
    validar_posicion(f, c);
    if(m[f][c] == 0){
        throw std::logic_error("El espacio ya está libre.");
    }
    m[f][c] = 0;
}

void Matriz::mostrar() const{
    std::cout << "    ";
    for(int j = 0; j < columnas; j++){
        std::cout << std::setw(4) << ("C" + std::to_string(j + 1));
    }
    std::cout << std::endl;
    for(int i = 0; i < filas; i++){
        std::cout << std::setw(4) << std::left << ("F" + std::to_string(i + 1)) << std::right;
        for(int j = 0; j < columnas; j++){
            std::cout << std::setw(4) << (m[i][j] == 1 ? "O" : "L");
        }
        std::cout << std::endl;
    }
    std::cout << "O = Ocupado | L = Libre" << std::endl;
    std::cout << "Espacios ocupados: " << ocupados() << std::endl;
    std::cout << "Espacios libres: " << libres() << std::endl;
    std::ios::fmtflags formato = std::cout.flags(); // Se guarda el formato para no afectar otras impresiones
    std::streamsize precision = std::cout.precision();
    std::cout << "Porcentaje de ocupación: " << std::fixed << std::setprecision(2) << porcentaje() << "%" << std::endl;
    std::cout.flags(formato);
    std::cout.precision(precision);
}

int Matriz::total() const{
    return filas * columnas;
}

int Matriz::ocupados() const{
    int c = 0;
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            c += m[i][j];
        }
    }
    return c;
}

int Matriz::libres() const{
    return total() - ocupados();
}

double Matriz::porcentaje() const{
    return (double)ocupados() / total() * 100;
}
