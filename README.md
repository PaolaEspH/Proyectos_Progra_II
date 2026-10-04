
Repositorio para los proyectos del curso CI0113-Programacion II de la carrera de Computación con Varios Énfasis.

# Estudiantes:

- Sebastian Miranda Ramirez C4H274
- Paola Espinoza Hernández

# Tarea 1: centro de control de satélites

Como primera tarea, el repositorio contiene un programa que permite, desde consola, registrar satélites, órbitas y estaciones terrestres, simular transmisiones y llevar el control de telemetría y energía.

## Funcionalidades

| Opción | Funciones |
| --- | --- |
| 1. Satélites | Registro de satélites de comunicación y meteorológicos, búsqueda y listado. |
| 2. Órbitas | Registro, búsqueda y asignación de satélites. |
| 3. Estaciones y enlaces | Registro y búsqueda de estaciones, creación y eliminación de enlaces, consulta de la matriz y conteo de enlaces activos. |
| 4. Telemetría | Registro de batería y temperatura, historial y estadísticas por satélite. |
| 5. Transmisiones | Registro de envíos, cálculo de duración, propagación y consumo de energía. |
| 6. Control energético | Consulta de batería y estado, recarga solar y listado de satélites críticos o fuera de servicio. |
| 7. Reportes | Resúmenes de satélites, órbitas, batería, transmisiones, telemetría y enlaces. |

## Archivos

Cada clase tiene su declaración en un `.hpp` y su implementación en un `.cpp`.

| Archivo | Contenido |
| --- | --- |
| `main_tarea1.cpp` | Menú principal. |
| `CentroControl.hpp` / `CentroControl.cpp` | Registros, búsquedas, menús, enlaces y reportes. |
| `Satelite.hpp` / `Satelite.cpp` | Datos del satélite, cálculos orbitales, telemetría y batería. |
| `Orbita.hpp` / `Orbita.cpp` | Datos de las órbitas y satélites asignados. |
| `EstacionTerrestre.hpp` / `EstacionTerrestre.cpp` | Datos de las estaciones y satélites enlazados. |
| `Transmision.hpp` / `Transmision.cpp` | Datos y cálculos de cada envío. |
| `auxiliar.hpp` | Límites de los arreglos, constantes y declaraciones adelantadas. |
| `docs/UML.pdf` | Diagrama de clases. |

## Límites y comportamiento

- Se permiten hasta 100 satélites, órbitas, estaciones y transmisiones, y 12 muestras de telemetría por satélite.
- La telemetría guarda la batería medida y la temperatura por separado de la batería que se va actualizando. Sus estadísticas usan únicamente las muestras registradas y se admiten temperaturas negativas.
- Una transmisión requiere un enlace activo y energía suficiente. Al aceptarse, descuenta batería y guarda el envío. La propagación se calcula tomando la altitud como distancia aproximada.

Los estados de batería son normal desde 50 %, precaución desde 20 % hasta menos de 50 %, crítico por encima de 0 % y por debajo de 20 %, y fuera de servicio en 0 %.

