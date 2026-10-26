#include <iostream>
#include <string>
class Vehiculo{
    private:
        std::string placa;
        std::string propietario;
        int tipo;
        int num;
    public:
        Vehiculo(std::string placa, std::string propietario, int tipo, int num);
        int get_tipo() const;
        int get_num() const;
        std::string get_placa() const;
        std::string get_propietario() const;
    };