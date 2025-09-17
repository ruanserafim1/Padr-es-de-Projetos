#pragma once
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QTimer>
#include <QThread>
#include <memory>
#include "Hidrometro.h"

class HidrometroApp : public QMainWindow {
    Q_OBJECT
public:
    HidrometroApp(QWidget* parent = nullptr);
    ~HidrometroApp();
private slots:
    void atualizarUI();
    void iniciarSimulacao();
    void pararSimulacao();
    void reiniciarSimulacao();
    void atualizarVazao(int value);
    void atualizarLeituraAnterior();
private:
    void desenharHidrometro();
    void atualizarPonteiros(int litros, int decimos);

    std::unique_ptr<Hidrometro> hidrometro;
    bool executando;
    QTimer* timer;

    QGraphicsScene* scene;
    QGraphicsView* view;
    QGraphicsPixmapItem* bgItem;
    QVector<QGraphicsTextItem*> digitos;
    QGraphicsLineItem* litrosPonteiro;
    QGraphicsLineItem* decimosPonteiro;

    QSlider* vazaoSlider;
    QLabel* vazaoLabel;
    QSpinBox* leituraSpin;
    QLabel* totalLabel;
    QLabel* consumoLabel;
    QLabel* vazaoAtualLabel;
    QPushButton* startButton;
    QPushButton* stopButton;
    QPushButton* resetButton;
};
