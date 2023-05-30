#include <iostream>

using namespace std;

class Contenedor
{
private:
    char buffer[22];
public:
    Contenedor();
    ~Contenedor();

    bool vacio();
    bool lleno();

    void initBuffer();
    void imprimir();
    char* getBuffer();
};

Contenedor::Contenedor()
{
    initBuffer();
}

Contenedor::~Contenedor()
{
}

bool Contenedor::vacio() {
    for (int i = 0; i < 22; i++)
    {
        if(buffer[i] != '_') {
            return false;
        }   
    }
    return true;
}

bool Contenedor::lleno() {
    for (int i = 0; i < 22; i++)
    {
        if(buffer[i] != '$') {
            return false;
        }   
    }
    return true;
}

void Contenedor::initBuffer() {
    for (int i = 0; i < 22; i++)
    {
        buffer[i] = '_';   
    }
}

void Contenedor::imprimir() {
    for (int i = 0; i < 22; i++)
    {
        cout << buffer[i] << "  ";
        if(i > 8){
            cout << " ";
        }   
    }
    cout << endl;

    for (int i = 0; i < 22; i++)
    {
        cout << i + 1 << "  ";   
    }
    cout << endl;
}

char* Contenedor::getBuffer() {
    return buffer;
}



