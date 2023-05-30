#ifndef PROCESO_H
#define PROCESO_H

#include <QString>
class Proceso
{

private:
    int tiempoMaximo;
    int idProceso;
    QString operacion;
    float resultado;
    int tiempoTranscurrido;
    bool interrumpido;
    bool error;
    bool ejecutado;
    int tLlegada;
    int tFin;
    int tRet;
    int tRes;
    int tEsp;
    int tSer;
    int tBloqueado;
    int tamanio;
public:
    Proceso();
    int getIdProceso() const;
    void setIdProceso(int value);
    QString getOperacion() const;
    void setOperacion(const QString &value);
    float getResultado() const;
    void setResultado(float value);
    int getTiempoMaximo() const;
    void setTiempoMaximo(int value);
    int getTiempoTranscurrido() const;
    void setTiempoTranscurrido(int value);
    bool getInterrumpido() const;
    void setInterrumpido(bool value);
    bool getError() const;
    void setError(bool value);
    int getTLlegada() const;
    void setTLlegada(int value);
    int getTFin() const;
    void setTFin(int value);
    int getTRet() const;
    void setTRet(int value);
    int getTRes() const;
    void setTRes(int value);
    int getTEsp() const;
    void setTEsp(int value);
    int getTSer() const;
    void setTSer(int value);
    bool getEjecutado() const;
    void setEjecutado(bool value);
    int getTBloqueado() const;
    void setTBloqueado(int value);
    void aumentarTBloq();
    int getTamanio() const;
    void setTamanio(int value);
};

#endif // PROCESO_H
