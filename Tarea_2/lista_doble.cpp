#include "nodo.hpp"
class ListaDoble{
    private:
        Nodo* cabeza;
        Nodo* cola;
        int solicitudes; //Es num de solicitudes hechas en el día, no contempla canceladas ni resueltas
        int** m;
        int filas;
        int columnas;
    public:
        ListaDoble(int f, int c): filas(f), columnas(c) {
            cabeza = nullptr;
            cola = nullptr;
            solicitudes = 0;
            m = new int*[f];
            for (int i = 0; i < f; i++){
                m[i] = new int[c];
            }
        }
        ~ListaDoble(){
            for (int i = 0; i < filas; i++){
                delete[] m[i];
            }
            delete m;
        }
        void registrar(Nodo* nuevo){
            if(!espacio()){
                std::cout << "Overflow" << std::endl;
                return;
            }
            else if(!encargados()){
                //logic_error
                return;
            }
            solicitudes++;
            // actualizar atributos de nodo
            if(cabeza == nullptr){
                cabeza = nuevo;
                cola = nuevo;
                return;
            }
            nuevo->set_anterior(cola);
            cola->set_siguiente(nuevo);
            cola = cola->get_siguiente();
        }
        class IteradorEstacionamiento{
            private:
                Nodo* posactual;
            public:
                IteradorEstacionamiento(Nodo* posicion){
                    posactual = posicion;
                }
                IteradorEstacionamiento& operator++(){
                    if(posactual != nullptr){ //Deja nullptr si es nullptr
                        posactual = posactual->get_siguiente();
                    }
                    return *this;
                }
                bool operator!=(const IteradorEstacionamiento& otro){
                    return posactual != otro.posactual;
                }
                bool operator==(const IteradorEstacionamiento& otro){
                    return posactual == otro.posactual;
                }
                Vehiculo* operator->(){
                    return &(posactual->get_dato());
                }
                Vehiculo& operator*(){
                    return posactual->get_dato();
                }
                Nodo* get_nodo() const{
                    return posactual;
                }
        };
        IteradorEstacionamiento begin(){
            return IteradorEstacionamiento(cabeza);
        }
        IteradorEstacionamiento end(){
            return IteradorEstacionamiento(nullptr);
        }
        void mostrar(){
            int i = 0;
            for(IteradorEstacionamiento it = begin(); it != end(); ++it, i++){
                std::cout << *it << "--------------------------------" << std::endl;
            }
            std::cout << "Total de solicitudes pendientes: " << i << std::endl;
        }
        void consultar(std::string placa){
            Nodo* vehiculo = buscar(placa);
            if(vehiculo){
                std::cout << *vehiculo;
            }
            else{
                std::cout << "Vehículo no encontrado" << std::endl;
            }
        }
        Nodo* buscar(std::string placa){
            for(IteradorEstacionamiento it = begin(); it != end(); ++it){
                if((it)->get_placa() == placa){
                    return it.get_nodo();
                };
            }
            return nullptr;
        }
        void abandonar(std::string placa){
            for(IteradorEstacionamiento it = begin(); it != end(); ++it){
                if(it->get_placa() == placa){
                    Nodo* eliminar = it.get_nodo();
                    it.get_nodo()->get_anterior()->set_siguiente(it.get_nodo()->get_siguiente());
                    if(it.get_nodo() == cabeza){
                        cabeza = it.get_nodo()->get_siguiente();
                    }
                    if(it.get_nodo() == cola){
                        cola = it.get_nodo()->get_anterior();
                    }
                    delete eliminar;
                    return;
                }
            }
        }
        int estacionados(){
            int c = 0;
            for(IteradorEstacionamiento it = begin(); it != end(); ++it){
                c++;
            }
            return c;
        }
        int cantidad(int tipo){
            int c = 0;
            for(IteradorEstacionamiento it = begin(); it != end(); ++it){
                if(it->get_tipo() == tipo){
                    c++;
                };
            }
            return c;
        }

};