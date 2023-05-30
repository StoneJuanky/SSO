#include "pagina.h"

Pagina::Pagina()
{
}

int Pagina::getNumPaginas() const
{
    return numPaginas;
}

void Pagina::setNumPaginas(int value)
{
    numPaginas = value;
}

int Pagina::getIdProceso() const
{
    return idProceso;
}

void Pagina::setIdProceso(int value)
{
    idProceso = value;
}

QString Pagina::getEstado() const
{
    return estado;
}

void Pagina::setEstado(const QString &value)
{
    estado = value;
}

bool Pagina::operator==(const Pagina &pagina) const
{
    return idProceso == pagina.idProceso;
}
