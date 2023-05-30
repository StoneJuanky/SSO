#include "proceso.h"

Proceso::Proceso()
{

}

int Proceso::getTiempoMaximo() const
{
    return tiempoMaximo;
}

void Proceso::setTiempoMaximo(int value)
{
    tiempoMaximo = value;
}

int Proceso::getLote() const
{
    return lote;
}

void Proceso::setLote(int value)
{
    lote = value;
}

float Proceso::getResultado() const
{
    return resultado;
}

void Proceso::setResultado(float value)
{
    resultado = value;
}

QString Proceso::getOperacion() const
{
    return operacion;
}

void Proceso::setOperacion(const QString &value)
{
    operacion = value;
}

QString Proceso::getNombre() const
{
    return nombre;
}

void Proceso::setNombre(const QString &value)
{
    nombre = value;
}

int Proceso::getIdProceso() const
{
    return idProceso;
}

void Proceso::setIdProceso(int value)
{
    idProceso = value;
}


