#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>
#include <algorithm> // find, count, sort, max_element

using namespace std;

int main() {
    // Pedir y leer lista de números
    int n;

    cout << "Cantidad de numeros: ";
    cin >> n;

    vector<int> numeros;
    set<int> numerosSet;

    cout << "Ingrese los numeros:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        numeros.push_back(x);
        numerosSet.insert(x);
    }

    // Imprimir vector con iteradores explícitos
    cout << "\nVector:\n";
    for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Vector imprime los números en el orden y tal como fueron ingresados

    // Imprimir set con iteradores explícitos
    cout << "\nSet:\n";
    for (set<int>::iterator it = numerosSet.begin(); it != numerosSet.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Set elimina repetidos y mantiene el orden de los elementos

    // Recorrer vector al revés
    cout << "\nVector al reves:\n";
    for (vector<int>::reverse_iterator it = numeros.rbegin(); it != numeros.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // Stack y Queue
    stack<int> pila;
    queue<int> cola;

    for (vector<int>::iterator it = numeros.begin();
         it != numeros.end();
         ++it) {
        pila.push(*it);
        cola.push(*it);
    }

    cout << "\nStack (orden invertido):\n";
    while (!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }
    cout << endl;

    cout << "\nQueue (mismo orden):\n";
    while (!cola.empty()) {
        cout << cola.front() << " ";
        cola.pop();
    }
    cout << endl;

    // Algoritmos

    // sort
    vector<int> copia = numeros;
    sort(copia.begin(), copia.end());

    cout << "\nVector ordenado con sort:\n";
    for (vector<int>::iterator it = copia.begin();
         it != copia.end();
         ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // max_element
    vector<int>::iterator maximo =
        max_element(numeros.begin(), numeros.end());

    cout << "\nElemento maximo: " << *maximo << endl;

    // find
    int buscado;
    cout << "\nNumero a buscar: ";
    cin >> buscado;

    vector<int>::iterator encontrado =
        find(numeros.begin(), numeros.end(), buscado);

    if (encontrado != numeros.end())
        cout << "El numero existe en el vector.\n";
    else
        cout << "El numero no existe en el vector.\n";

    // count
    cout << "Cantidad de veces que aparece "
         << buscado << ": "
         << count(numeros.begin(), numeros.end(), buscado)
         << endl;
}