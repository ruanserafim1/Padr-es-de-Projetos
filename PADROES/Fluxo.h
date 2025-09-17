#pragma once
class Fluxo {
public:
    Fluxo(double vazao = 0.0, double pressao = 0.0, double volume = 0.0);
    double getVazao() const;
    void setVazao(double v);
    double getPressao() const;
    void setPressao(double p);
    double getVolumeTotal() const;
    void setVolumeTotal(double v);
    void incrementarVolume(double tempoHoras);
private:
    double vazao;
    double pressao;
    double volumeTotal;
};
