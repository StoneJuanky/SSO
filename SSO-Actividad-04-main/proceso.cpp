#include "proceso.h"



Proceso::Proceso()
{
    interrumpido = false;
    error = false;
}

bool Proceso::getError() const
{
    return error;
}

void Proceso::setError(bool value)
{
    error = value;
}

bool Proceso::getInterrumpido() const
{
    return interrumpido;
}

void Proceso::setInterrumpido(bool value)
{
    interrumpido = value;
}

int Proceso::getTiempoTranscurrido() const
{
    return tiempoTranscurrido;
}

void Proceso::setTiempoTranscurrido(int value)
{
    tiempoTranscurrido = value;
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

int Proceso::getIdProceso() const
{
    return idProceso;
}

void Proceso::setIdProceso(int value)
{
    idProceso = value;
}

