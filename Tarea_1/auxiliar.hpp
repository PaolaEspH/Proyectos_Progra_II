#ifndef AUXILIAR_HPP
#define AUXILIAR_HPP

// Capacidades maximas de los arreglos fijos
const int MAX_SATELITES = 100;
const int MAX_ORBITAS = 100;
const int MAX_ESTACIONES = 100;
const int MAX_TRANSMISIONES = 100;
const int MAX_MUESTRAS = 12;

// Constantes del modelo (seccion 3.5 del enunciado)
const double RT = 6371.0;          // km
const double MU = 398600.0;        // km^3/s^2
const double C_LUZ = 299792.458;   // km/s
const double PI = 3.14159265;

// Declaraciones adelantadas: evitan inclusiones circulares entre .hpp
class Satelite;
class Orbita;
class EstacionTerrestre;
class Transmision;
class CentroControl;

#endif
