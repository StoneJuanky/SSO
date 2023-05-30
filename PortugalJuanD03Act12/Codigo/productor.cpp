#include <iostream>
#include <ctime>

using namespace std;

class Productor
{
private:
    int productos;
    string estado;
    int i;
public:
    Productor();
    ~Productor();

    string getEstado();
    void setEstado(int estado);

    void calcularProductos();
    int getProductos();

    void producir(char buffer[22]);
    void aumentarI();
    void disminuirProductos();
};

Productor::Productor()
{
    productos = (rand() % 4) + 3;
    estado = "Dormido";
    i = 0;
}

Productor::~Productor()
{
}

string Productor::getEstado() {
    return estado;
}

void Productor::setEstado(int estado) {
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

void Productor::calcularProductos() {
    productos = (rand() % 4) + 3;
}

void Productor::disminuirProductos() {
    productos--;
}

int Productor::getProductos() {
    return productos;
}

void Productor::aumentarI() {
    if(i == 21) {
        i = 0;
    } else {
        i++;
    }
}

void Productor::producir(char buffer[22]) {
    buffer[i] = '$';
    if(productos != 0) {
        productos--;
    }
    aumentarI();
}
