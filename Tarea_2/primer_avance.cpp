//Paola Espinoza Hernández, C32715
//Sebastián Miranda Ramírez, C4H274
#include <iostream>
#include <string>
class Vehiculo{
    private:
        std::string placa;
        std::string propietario;
        int tipo;
        int num;
    public:
        Vehiculo(std::string placa, std::string propietario, int tipo, int num){
            this->placa = placa;
            this->propietario = propietario;
            this->tipo = tipo;
            this->num = num;
        };
        int get_tipo() const{
            return tipo;
        };
        int get_num() const{
            return num;
        };
        std::string get_placa() const{
            return placa;
        };
        std::string get_propietario() const{
            return propietario;
        };
        std::string texto_tipo() const{
            switch(tipo){
                case 0:
                    return "Automóvil";
                case 1:
                    return "Motocicleta";
                default:
                    return "Desconocido";
            }
        }
        friend std::ostream& operator<<(std::ostream& s, const Vehiculo& v){
            s << "Placa: " << v.placa <<
            std::endl << "Propietario: " << v.propietario <<
            std::endl << "Tipo: " << v.texto_tipo() <<
            std::endl << "Número de solicitud: " << v.num << 
            std::endl;
            return s;
        }
};

class Nodo{
    private:
        Vehiculo dato;
        Nodo* siguiente;
    public:
        Nodo(Vehiculo dato): dato(dato), siguiente(nullptr){};
        Nodo* get_siguiente() const{
            return siguiente;
        };
        Vehiculo& get_dato(){
            return dato;
        }
        void set_siguiente(Nodo* sig){
            siguiente = sig;
        }
        friend std::ostream& operator<<(std::ostream& s, const Nodo& nodo){
            s << nodo.dato;
            return s;
        }
};

class ListaEnlazada{
    private:
        Nodo* cabeza;
        Nodo* cola;
        int solicitudes; //Es num de solicitudes hechas en el día, no contempla canceladas ni resueltas
    public:
        ListaEnlazada(){
            cabeza = nullptr;
            cola = nullptr;
            solicitudes = 0;
        }
        void registrar(std::string placa, std::string propietario, int tipo){
            if(buscar(placa)){
                std::cout << "La placa ya se encuentra registrada" << std::endl;
                return;
            }
            Nodo* nuevo = new Nodo(Vehiculo(placa, propietario, tipo, solicitudes));
            solicitudes++;
            if(cabeza == nullptr){
                cabeza = nuevo;
                cola = nuevo;
                return;
            }
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

int main(){
    ListaEnlazada list;
    list.mostrar();
    list.registrar("23", "1", 1);
    list.registrar("26", "2", 0);
    list.registrar("78", "3", 1);
    list.mostrar();
    list.consultar("26");
    list.consultar("ZZZ999");
    list.cancelar("78");
    list.mostrar();
    list.registrar("78", "8", 0);
    list.registrar("26", "4", 0);
    list.registrar("PA56", "5", 1);
    list.cancelar("23");
    list.mostrar();
    std::cout << "Cantidad de automóviles: " << list.cantidad(0) << std::endl;
    std::cout << "Cantidad de motocicletas: " << list.cantidad(1) << std::endl;
    std::cout << "Solicitudes pendientes: " << list.pendientes() << std::endl;
}