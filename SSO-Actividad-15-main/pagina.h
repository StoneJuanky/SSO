#ifndef PAGINA_H
#define PAGINA_H

#include <QString>

class Pagina
{
public:
    Pagina();

    int getNumPaginas() const;
    void setNumPaginas(int value);

    int getIdProceso() const;
    void setIdProceso(int value);

    QString getEstado() const;
    void setEstado(const QString &value);
    bool operator==(const Pagina &pagina) const;

private:
    int idProceso;
    int numPaginas;
    QString estado;
};

#endif // PAGINA_H
