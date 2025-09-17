#pragma once
#include "Fluxo.h"
#include "Medicao.h"

class Hidrometro {
public:
    Hidrometro();
    void medir();
    void setVazaoEntrada(double vazao);
    void atualizarVolume(double tempoHoras);
    double getVolumeTotal() const;
    double getConsumo() const;
    void setLeituraAnterior(double leitura);
    const Medicao& getMedicao() const;
private:
    Fluxo entrada;
    Fluxo saida;
    Medicao medicao;
    double leituraAnterior;
};
