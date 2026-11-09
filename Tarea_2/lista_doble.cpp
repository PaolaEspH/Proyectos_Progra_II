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
        void registrar(Nodo& nuevo){
            if(!espacio()){
                std::cout << "Overflow" << std::endl;
                return;
            }
            else if(!encargados()){
                //logic_error
                return;
            }
            solicitudes++;
            if(cabeza == nullptr){
                cabeza = nuevo;
                cola = nuevo;
                return;
            }
            nuevo->set_anterior(cola);
            cola->set_siguiente(nuevo);
            cola = cola->get_siguiente();
        }
        class IteradorEspera{
            private:
                Nodo* posactual;
            public:
                IteradorEspera(Nodo* posicion){
                    posactual = posicion;
                }
                IteradorEspera& operator++(){
                    if(posactual != nullptr){ //Deja nullptr si es nullptr
                        posactual = posactual->get_siguiente();
                    }
                    return *this;
                }
                bool operator!=(const IteradorEspera& otro){
                    return posactual != otro.posactual;
                }
                bool operator==(const IteradorEspera& otro){
                    return posactual == otro.posactual;
                }
                //Decidimos modificar el operador para que * devuelva nodo en vez de vehículo, pero también devolvemos vehículo mediante ->.
                //Le pregunté al profe y dijo que estaba bien hacerlo así
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
        IteradorEspera begin(){
            return IteradorEspera(cabeza);
        }
        IteradorEspera end(){
            return IteradorEspera(nullptr);
        }
        void mostrar(){
            int i = 0;
            for(IteradorEspera it = begin(); it != end(); ++it, i++){
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
            for(IteradorEspera it = begin(); it != end(); ++it){
                if((it)->get_placa() == placa){
                    return it.get_nodo();
                };
            }
            return nullptr;
        }
        void cancelar(std::string placa){
            Nodo* anterior = nullptr;
            IteradorEspera b = begin();
            ++b;
            for(IteradorEspera it = begin(); it != end(); ++it, ++b){
                if(it->get_placa() == placa){
                    Nodo* eliminar = it.get_nodo();
                    if(anterior == nullptr){
                        cabeza = cabeza->get_siguiente();
                    }
                    else{
                        anterior->set_siguiente(b.get_nodo());
                    }
                    if(b == end()){
                        cola = anterior;
                    }
                    delete eliminar;
                    return;
                }
                anterior = it.get_nodo();
            }
        }
        int pendientes(){
            int c = 0;
            for(IteradorEspera it = begin(); it != end(); ++it){
                c++;
            }
            return c;
        }
        int cantidad(int tipo){
            int c = 0;
            for(IteradorEspera it = begin(); it != end(); ++it){
                if(it->get_tipo() == tipo){
                    c++;
                };
            }
            return c;
        }

};