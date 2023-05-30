#include <iostream>
#include <ctime>

using namespace std;

class Consumidor
{
private:
    int productos;
    string estado;
    int i;
public:
    Consumidor();
    ~Consumidor();

    string getEstado();
    void setEstado(int estado);

    void calcularProductos();
    int getProductos();

    void consumir(char buffer[22]);
    void aumentarI();
    void disminuirProductos();
};

Consumidor::Consumidor()
{
    productos = (rand() % 4) + 3;
    estado = "Dormido";
    i = 0;
}

Consumidor::~Consumidor()
{
}

string Consumidor::getEstado() {
    return estado;
}

void Consumidor::setEstado(int estado) {
    switch (estado)
    {
    case 0:
        this->estado = "Dormido";
        break;

    case 1:
        this->estado = "Trabajando";
        break;

    case 2:
        this->estado = "Intentando ingresar";
        break;
    
    default:
        this->estado = "Dormido";
        break;
    }
}

void Consumidor::calcularProductos() {
    productos = (rand() % 4) + 3;
}

int Consumidor::getProductos() {
    return productos;
}

void Consumidor::disminuirProductos() {
    productos--;
}

void Consumidor::aumentarI() {
    if(i == 21) {
        i = 0;
    } else {
        i++;
    }
}

void Consumidor::consumir(char buffer[22]) {
    buffer[i] = '_';
    if(productos != 0) {
        productos--;
    }
    aumentarI();
}
