// Medicao.cpp
#include "Medicao.h"
#include <cmath>

Medicao::Medicao()
    : consumoM3(0.0), centenasLitros(0), dezenasLitros(0), litros(0), decimosLitros(0) {}

void Medicao::atualizarMedicao(double volumeTotal) {
    consumoM3 = std::floor(volumeTotal);
    double parteDecimal = volumeTotal - consumoM3;
    double litrosTotal = parteDecimal * 1000.0;
    centenasLitros = static_cast<int>(litrosTotal / 100) % 10;
    dezenasLitros  = static_cast<int>(litrosTotal / 10) % 10;
    litros         = static_cast<int>(litrosTotal) % 10;
    decimosLitros  = static_cast<int>(litrosTotal * 10) % 10;
}
double Medicao::getConsumoM3() const { return consumoM3; }
int Medicao::getCentenasLitros() const { return centenasLitros; }
int Medicao::getDezenasLitros() const { return dezenasLitros; }
int Medicao::getLitros() const { return litros; }
int Medicao::getDecimosLitros() const { return decimosLitros; }
double Medicao::calcularConsumo(double leituraAnterior, double leituraAtual) {
    return leituraAtual - leituraAnterior;
}
