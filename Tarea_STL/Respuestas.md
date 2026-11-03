# Tarea STL
Paola Espinoza Hernández, Sebastián Miranda

## Parte 1

1. 


2. **Contenedor:** Un clase que puede contener y administrar objetos de otro tipo. Existen los contenedores secuenciales (que tienen orden) y los asociativos (con llaves).
**Iterador:** Generalización de punteros, que permiten recorrer contenedores de manera uniforme. Existen los de acceso aleatorio, bidireccionales, hacia adelante y de entrada y salida.
**Algoritmo:** Los algoritmos de STL son algoritmos implementados de manera genérica, capaces de recorrer los contenedores realizados por los usuarios. Los usuraios también pueden realizar algoritmos genéricos. Se agrupan en 4 grupos: los que cambian el orden de los elementos en el contenedor, los que no, los de ordenamiento y operaciones similares, y los de operaciones numéricas.

3. 

4.

5. Incluye casi todas las librerías estándar de C y C++. No se recomienda utilizarlo porque carga librerías que no se van a utilizar, lo que puede aumentar el tiempo de compilación. Además, podría causar coalisión con los nombres reservados de las librerías.

## Parte 2
Un contenedor es un objeto que puede guardar y administrar objetos de otros tipos. Los contenedores secuenciales, como su nombre lo indica, son contenedores donde sus elementos tienen un orden lineal. Por su lado, en los contenedores asociativos, los elementos se relacionan mediante llaves, que pueden ser únicas o múltiples.





## Parte 4

### 1. ¿Qué es un iterador en la STL? ¿Qué operaciones básicas permite? ¿Cómo se compara con el de clase?

Un iterador en la STL es una abstracción y generalización de los punteros. Permite a un programa recorrer los elementos de distintas estructuras de datos (contenedores y rangos) de manera uniforme, sin necesidad de conocer los detalles internos de cómo están almacenados (seguidos o dispersos).
* **Operaciones básicas:** Las operaciones mínimas suelen ser para acceder al elemento (`*it`), avanzar (`++it`), comparar igualdad (`it == otro`) y desigualdad (`it != otro`). Sin embargo, dependiendo de su categoría (entrada, salida, forward, bidireccional o de acceso aleatorio), soportan operaciones como la desreferenciación (`*it` o `it->`), el incremento (`++it`, `it++`), el decremento (`--it`, `it--`), comparaciones de igualdad y desigualdad (`==`, `!=`), y aritmética de punteros (en iteradores de acceso aleatorio como `it + n`). 
* **Comparación con el de clase:** Si bien ambos encapsulan la posición actual dentro de una estructura de datos y sobrecargar operadores (`*`, `++`, `==`, `!=`), los iteradores de la STL se clasifican en categorías estandarizadas con diversas capacidades (input, output, forward, bidirectional y random access), de modo que cumplen varios requisitos que los de la clase no cumplen y se adaptan mejor. Además, suelen incluir tipos anidados requeridos por los *iterator traits* (como `iterator_category`, `value_type`, `difference_type`, `pointer`, `reference`), compatibilidad con adaptadores (como `std::reverse_iterator`), y soporte para versiones constantes (`const_iterator`).

### 2. ¿Qué devuelven `begin()` y `end()`? ¿Por qué `end()` apunta una posición después del último elemento?

Ambos devuelven un iterador, `begin()` devuelve un iterador que apunta al primer elemento del contenedor y `end()` devuelve un iterador que apunta a la posición inmediatamente posterior al último elemento. Esto porque facilita la lógica de los bucles (el bucle continúa mientras el iterador actual sea distinto de `end()`) y para detectar facilmente cuando un contenedor está vacío (ambos devuelven el mismo). Además, se destaca que por el estándar, aunque el `end()` apunta fuera del rango de la estructura y, por tanto, no se puede desreferenciar, es seguro comparar con este.

### 3. ¿Por qué `std::sort` funciona con `vector` pero no con `list`? ¿Qué hace `list` en su lugar?

`std::sort` requiere iteradores de acceso aleatorio (`LegacyRandomAccessIterator`) porque algoritmos eficientes como *Introsort* (la base de `std::sort`) necesitan saltar constantemente de un extremo a otro o al elemento medio en tiempo constante $O(1)$. Como `std::vector` almacena sus elementos en memoria contigua, lo permite; en cambio, un `std::list` está implementado como una lista doblemente enlazada con iteradores bidireccionales (`LegacyBidirectionalIterator`), por lo que avanzar $N$ posiciones toma tiempo lineal $O(N)$ y no se puede acceder directamente al elemento medio.
* **¿Qué hace `list` en su lugar?:** `std::list` tiene su propia función optimizada para ordenar, `list::sort()`. Esta función reorganiza los nodos internamente reasignando los punteros de los enlaces (sin mover los datos de sitio) mediante un algoritmo de ordenamiento estable adecuado para listas (como *Merge Sort*).


### 4. ¿Cómo los algoritmos de `<algorithm>` trabajan sin conocer el contenedor? ¿Por qué son el "puente"?

Los algoritmos de `<algorithm>` trabajan sin conocer el contenedor usando plantillas. Las funciones de `<algorithm>` (como `std::find`, `std::count`, `std::sort`) no reciben contenedores enteros, sino pares de iteradores que delimitan un rango (`first`, `last`). El algoritmo solo interactúa con los elementos mediante las operaciones genéricas que soportan los iteradores (`*`, `++`, etc.).

Se consideran el "puente" porque actúan como una interfaz común, puesto que permiten que un mismo algoritmo funcione igual tanto para un `std::vector`, un `std::list`, un `std::set`, un arreglo nativo de C (`int arr[]`), o incluso un flujo de entrada/salida (`std::istream_iterator`), sin importar cómo estén estructurados o guardados los datos en la memoria.

### 5. ¿Qué significa que un iterador quede invalidado? Ejemplo con `vector` vs `list`.

Un iterador queda invalidado cuando se modifica la estructura del contenedor (añadiendo, eliminando o reubicando elementos) de forma que la dirección de memoria o la posición lógica a la que apuntaba un iterador deja de ser válida o pasa a apuntar a basura u otro elemento, provocando un comportamiento indefinido si se intenta usar.
* **Ejemplo con `std::vector`:** Si se tiene un vector lleno a su capacidad y se ejecuta un `push_back()`, el vector debe reasignar memoria en un bloque más grande, copiar todos sus elementos allí y liberar el bloque viejo, por lo que todos los iteradores existentes que apuntaban al vector original quedan invalidados.
* **Ejemplo con `list`:** Como los elementos están conectados entre ellos mediante punteros, al insertar o borrar un elemento, cambian solamente los punteros de los nodos adyacentes. Así, al eliminar un nodo, el iterador queda invalidado solamente si apuntaba a ese nodo, si apuntan a otra parte de la lista, se mantienen válidos. 

### 6. ¿Qué relación tiene el *for* de rango (`for (auto x : v)`) con `begin()` y `end()`? ¿Funcionaría con nuestra clase?

* **Relación con `begin()` y `end()`:** El bucle de rango (introducido en C++11) es traducido por el compilador a un bucle tradicional utilizando los iteradores del contenedor. Para un contenedor `v`, el compilador expande el bucle de forma equivalente a:
```cpp
auto __begin = std::begin(v);
auto __end = std::end(v);
for (; __begin != __end; ++__begin) {
    auto x = *__begin;
    // cuerpo del bucle
}
```
Por tanto, funcionaría siempre y cuando se implementen en la clase las funciones `begin()` y `end()`, y estas retornen objetos que cumplan con los requisitos mínimos de un iterador (`*`, `++` y `!=`).

---

### 7. Diferencia entre `iterator`, `const_iterator` y `reverse_iterator`

* **`iterator`**: Permite leer y modificar los elementos del contenedor a través de la desreferenciación.
* *Ejemplo:*
```cpp
std::vector<int> v = {1, 2, 3};
std::vector<int>::iterator it = v.begin();
*it = 10;
std::cout << v[0];
```


* **`const_iterator`**: Es un iterador de solo lectura, permite leer los elementos pero no puede modificarlos.
* *Ejemplo:*
```cpp
std::vector<int> v = {1, 2, 3};
std::vector<int>::const_iterator cit = v.begin();
int val = *cit; // Lee el valor (val = 1).
// *cit = 20;   // Error de compilación. No se puede modificar un elemento a través de un const_iterator.
std::cout << val;
```




* **`reverse_iterator`**: Invierte la dirección del recorrido. Al incrementarlo (`++`), el iterador se mueve físicamente hacia **atrás** en el contenedor (hacia el inicio). Se obtiene típicamente mediante `rbegin()` y `rend()`.
* *Ejemplo:*
```cpp
std::vector<int> v = {1, 2, 3};
std::vector<int>::reverse_iterator rit = v.rbegin();
// *rit apunta al último elemento (3).
// Al hacer ++rit, se mueve hacia atrás, apuntando al número 2.
for (; rit != v.rend(); ++rit) {
    std::cout << *rit << " ";
}
std::cout << std::endl;
```


## Parte 5

![Captura de salida](image.png)




https://pages.di.unipi.it/corradini/Didattica/AP-24/DOCS/stl-tutorial-Weidl.pdf
