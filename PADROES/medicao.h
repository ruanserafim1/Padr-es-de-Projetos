#pragma once
class Medicao {
public:
    Medicao();
    void atualizarMedicao(double volumeTotal);
    double getConsumoM3() const;
    int getCentenasLitros() const;
    int getDezenasLitros() const;
    int getLitros() const;
    int getDecimosLitros() const;
    static double calcularConsumo(double leituraAnterior, double leituraAtual);
private:
    double consumoM3;
    int centenasLitros;
    int dezenasLitros;
    int litros;
    int decimosLitros;
};
