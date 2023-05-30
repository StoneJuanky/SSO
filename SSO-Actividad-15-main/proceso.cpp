#include "proceso.h"

int Proceso::getTamanio() const
{
    return tamanio;
}

void Proceso::setTamanio(int value)
{
    tamanio = value;
}

Proceso::Proceso()
{
    interrumpido = false;
    error = false;
    ejecutado = false;
    tBloqueado = 0;
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

int Proceso::getTLlegada() const
{
    return tLlegada;
}

void Proceso::setTLlegada(int value)
{
    tLlegada = value;
}

int Proceso::getTFin() const
{
    return tFin;
}

void Proceso::setTFin(int value)
{
    tFin = value;
}

int Proceso::getTRet() const
{
    return tRet;
}

void Proceso::setTRet(int value)
{
    tRet = value;
}

int Proceso::getTRes() const
{
    return tRes;
}

void Proceso::setTRes(int value)
{
    tRes = value;
}

int Proceso::getTEsp() const
{
    return tEsp;
}

void Proceso::setTEsp(int value)
{
    tEsp = value;
}

int Proceso::getTSer() const
{
    return tSer;
}

void Proceso::setTSer(int value)
{
    tSer = value;
}

bool Proceso::getEjecutado() const
{
    return ejecutado;
}

void Proceso::setEjecutado(bool value)
{
    ejecutado = value;
}

int Proceso::getTBloqueado() const
{
    return tBloqueado;
}

void Proceso::setTBloqueado(int value)
{
    tBloqueado = value;
}

void Proceso::aumentarTBloq()
{
    tBloqueado+=1;
}
