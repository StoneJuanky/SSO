#ifndef PROCESO_H
#define PROCESO_H

#include <QString>
class Proceso
{

private:
    int tiempoMaximo;
    int idProceso;
    int lote;
    QString operacion;
    float resultado;
    int tiempoTranscurrido;
    bool interrumpido;
    bool error;
public:
    Proceso();
    int getIdProceso() const;
    void setIdProceso(int value);
    QString getOperacion() const;
    void setOperacion(const QString &value);
    float getResultado() const;
    void setResultado(float value);
    int getLote() const;
    void setLote(int value);
    int getTiempoMaximo() const;
    void setTiempoMaximo(int value);
    int getTiempoTranscurrido() const;
    void setTiempoTranscurrido(int value);
    bool getInterrumpido() const;
    void setInterrumpido(bool value);
    bool getError() const;
    void setError(bool value);
};

#endif // PROCESO_H

