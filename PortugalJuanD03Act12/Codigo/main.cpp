#include <iostream>
#include "contenedor.cpp"
#include "productor.cpp"
#include "consumidor.cpp"
#include "conio.h"
#include <windows.h>
#include <ctime>

using namespace std;

bool checarTecla() {
	char tecla;
	if(kbhit()) {
		tecla = getch();
		return tecla == 27;
	}
	return false;
}

bool determinarTurno() {
	int num = (rand() % 11) + 1;
	return (num < 6);
}

void imprimirDatos(Contenedor* contenedor, string consumidor, string productor) {
	cout << "Productor: " << productor << endl;
	cout << "Consumidor: " << consumidor << endl << endl;
	cout << "Contenedor: " << endl;
	contenedor->imprimir();
}


int main(int argc, char *argv[])
{
	srand(time(nullptr));
	Contenedor* contenedor = new Contenedor();
	Productor* productor = new Productor();
	Consumidor* consumidor = new Consumidor();
	int estado = 0;
	int tiempo = 0;
	contenedor->initBuffer();

	imprimirDatos(contenedor, consumidor->getEstado(), productor->getEstado());
	cout << tiempo << endl;
	Sleep(2500);
	system("cls");
	tiempo++;
	

	while (true)
	{
		switch (estado)
		{
		case 1:
			productor->setEstado(0);
			consumidor->setEstado(0);
			if(determinarTurno()) {
				if(contenedor->lleno()) {
					productor->setEstado(2);
				} else {
					productor->calcularProductos();
					estado = 2;
				}

			} else {
				if(contenedor->vacio()) {
					consumidor->setEstado(2);
				} else {
					consumidor->calcularProductos();
					estado = 3;
				}
			}
			break;
		
		case 2:
			productor->setEstado(1);
			if(!determinarTurno()) {
				consumidor->setEstado(2);
			}

			productor->producir(contenedor->getBuffer());
			if(productor->getProductos() == 0 || contenedor->lleno()) {
				estado = 1;
			}
			break;
		
		case 3:
			consumidor->setEstado(1);
			if(determinarTurno()) {
				productor->setEstado(2);
			}
			
			consumidor->consumir(contenedor->getBuffer());
			if(consumidor->getProductos() == 0 || contenedor->vacio()) {
				estado = 1;
			}
			break;
		
		default:
			consumidor->setEstado(0);
			productor->setEstado(0);
			estado = 1;
			break;
		}

		imprimirDatos(contenedor, consumidor->getEstado(), productor->getEstado());


		if(consumidor->getEstado() == "Intentando ingresar") {
			consumidor->setEstado(0);
		}
		if(productor->getEstado() == "Intentando ingresar") {
			productor->setEstado(0);
		}

		
		if(checarTecla()) {
			break;
		}
		cout << tiempo << endl;		
		Sleep(2500);
		system("cls");
		tiempo++;
	}
}