#include "Fluxo.h"

Fluxo::Fluxo(double vazao, double pressao, double volume)
    : vazao(vazao), pressao(pressao), volumeTotal(volume) {}

double Fluxo::getVazao() const { return vazao; }
void Fluxo::setVazao(double v) { vazao = v; }
double Fluxo::getPressao() const { return pressao; }
void Fluxo::setPressao(double p) { pressao = p; }
double Fluxo::getVolumeTotal() const { return volumeTotal; }
void Fluxo::setVolumeTotal(double v) { volumeTotal = v; }
void Fluxo::incrementarVolume(double tempoHoras) { volumeTotal += vazao * tempoHoras; }
