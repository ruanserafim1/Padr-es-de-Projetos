#include "Hidrometro.h"

Hidrometro::Hidrometro() : leituraAnterior(0.0) {}

void Hidrometro::medir() {
    medicao.atualizarMedicao(entrada.getVolumeTotal());
}
void Hidrometro::setVazaoEntrada(double vazao) { entrada.setVazao(vazao); }
void Hidrometro::atualizarVolume(double tempoHoras) { entrada.incrementarVolume(tempoHoras); }
double Hidrometro::getVolumeTotal() const { return entrada.getVolumeTotal(); }
double Hidrometro::getConsumo() const { return Medicao::calcularConsumo(leituraAnterior, entrada.getVolumeTotal()); }
void Hidrometro::setLeituraAnterior(double leitura) { leituraAnterior = leitura; }
const Medicao& Hidrometro::getMedicao() const { return medicao; }
