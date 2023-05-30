#ifndef PROCESO_H
#define PROCESO_H


#include <QString>
class Proceso
{
public:
    Proceso();
    int tiempoMaximo;
    int idProceso;
    int lote;
    QString nombre;
    QString operacion;
    float resultado;

    int getIdProceso() const;
    void setIdProceso(int value);
    QString getNombre() const;
    void setNombre(const QString &value);
    QString getOperacion() const;
    void setOperacion(const QString &value);
    float getResultado() const;
    void setResultado(float value);
    int getLote() const;
    void setLote(int value);
    int getTiempoMaximo() const;
    void setTiempoMaximo(int value);
};

#endif // PROCESO_H
