#include "HidrometroApp.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QGraphicsTextItem>
#include <QDebug>
#include <cmath>

HidrometroApp::HidrometroApp(QWidget* parent)
    : QMainWindow(parent), executando(false) {

    hidrometro = std::make_unique<Hidrometro>();

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    // --- Canvas principal (QGraphicsView) ---
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setFixedSize(600, 450);
    QPixmap bg("src/hidrometro1.png");
    bgItem = scene->addPixmap(bg.scaled(600, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // --- Dígitos ---
    int startX = 248;
    for (int i = 0; i < 6; i++) {
        QGraphicsTextItem* txt = scene->addText("0", QFont("Segoe UI", 20, QFont::Bold));
        txt->setDefaultTextColor(Qt::black);
        txt->setPos(startX + i * 22, 190);
        digitos.append(txt);
    }

    // --- Ponteiros ---
    litrosPonteiro = scene->addLine(384, 280, 384, 240, QPen(Qt::red, 3));
    decimosPonteiro = scene->addLine(300, 322, 300, 282, QPen(Qt::blue, 3));

    mainLayout->addWidget(view);

    // --- Controles ---
    QGroupBox* controlGroup = new QGroupBox("Controles de Simulação");
    QGridLayout* controlLayout = new QGridLayout(controlGroup);

    controlLayout->addWidget(new QLabel("Vazão (m³/h):"), 0, 0);
    vazaoSlider = new QSlider(Qt::Horizontal);
    vazaoSlider->setRange(1, 50); // equivale a 0.1 ~ 5.0
    vazaoSlider->setValue(15);
    controlLayout->addWidget(vazaoSlider, 0, 1);
    vazaoLabel = new QLabel("1.50 m³/h");
    controlLayout->addWidget(vazaoLabel, 0, 2);

    controlLayout->addWidget(new QLabel("Leitura anterior (m³):"), 1, 0);
    leituraSpin = new QSpinBox();
    leituraSpin->setRange(0, 10000);
    leituraSpin->setValue(0);
    controlLayout->addWidget(leituraSpin, 1, 1);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    startButton = new QPushButton("Iniciar");
    stopButton = new QPushButton("Parar");
    resetButton = new QPushButton("Reiniciar");
    stopButton->setEnabled(false);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addWidget(resetButton);

    controlLayout->addLayout(buttonLayout, 2, 0, 1, 3);
    mainLayout->addWidget(controlGroup);

    // --- Informações ---
    QGroupBox* infoGroup = new QGroupBox("Informações de Consumo");
    QGridLayout* infoLayout = new QGridLayout(infoGroup);

    infoLayout->addWidget(new QLabel("Consumo total (m³):"), 0, 0);
    totalLabel = new QLabel("0.000");
    infoLayout->addWidget(totalLabel, 0, 1);

    infoLayout->addWidget(new QLabel("Consumo desde última leitura (m³):"), 1, 0);
    consumoLabel = new QLabel("0.000");
    infoLayout->addWidget(consumoLabel, 1, 1);

    infoLayout->addWidget(new QLabel("Vazão atual (m³/h):"), 2, 0);
    vazaoAtualLabel = new QLabel("0.000");
    infoLayout->addWidget(vazaoAtualLabel, 2, 1);

    mainLayout->addWidget(infoGroup);

    // --- Conexões ---
    connect(vazaoSlider, &QSlider::valueChanged, this, &HidrometroApp::atualizarVazao);
    connect(leituraSpin, &QSpinBox::editingFinished, this, &HidrometroApp::atualizarLeituraAnterior);
    connect(startButton, &QPushButton::clicked, this, &HidrometroApp::iniciarSimulacao);
    connect(stopButton, &QPushButton::clicked, this, &HidrometroApp::pararSimulacao);
    connect(resetButton, &QPushButton::clicked, this, &HidrometroApp::reiniciarSimulacao);

    // --- Timer ---
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &HidrometroApp::atualizarUI);

    resize(900, 700);
    setWindowTitle("💧 Simulador de Hidrômetro Realista");

    desenharHidrometro();
}

HidrometroApp::~HidrometroApp() {}

void HidrometroApp::atualizarVazao(int value) {
    double vazao = value / 10.0; // slider 1..50 => 0.1..5.0
    hidrometro->setVazaoEntrada(vazao);
    vazaoLabel->setText(QString::asprintf("%.2f m³/h", vazao));
    vazaoAtualLabel->setText(QString::asprintf("%.3f", vazao));
}
void HidrometroApp::atualizarLeituraAnterior() {
    hidrometro->setLeituraAnterior(leituraSpin->value());
}
void HidrometroApp::iniciarSimulacao() {
    if (!executando) {
        executando = true;
        startButton->setEnabled(false);
        stopButton->setEnabled(true);
        atualizarVazao(vazaoSlider->value());
        atualizarLeituraAnterior();
        timer->start(100);
    }
}
void HidrometroApp::pararSimulacao() {
    executando = false;
    startButton->setEnabled(true);
    stopButton->setEnabled(false);
    timer->stop();
}
void HidrometroApp::reiniciarSimulacao() {
    pararSimulacao();
    hidrometro = std::make_unique<Hidrometro>();
    desenharHidrometro();
    totalLabel->setText("0.000");
    consumoLabel->setText("0.000");
    vazaoAtualLabel->setText("0.000");
}
void HidrometroApp::atualizarUI() {
    if (!executando) return;
    hidrometro->atualizarVolume(0.1 / 3600.0);
    hidrometro->medir();
    desenharHidrometro();
    totalLabel->setText(QString::asprintf("%.3f", hidrometro->getVolumeTotal()));
    consumoLabel->setText(QString::asprintf("%.3f", hidrometro->getConsumo()));
}
void HidrometroApp::desenharHidrometro() {
    const Medicao& medicao = hidrometro->getMedicao();
    QString valor = QString("%1").arg((int)medicao.getConsumoM3(), 4, 10, QChar('0'));
    for (int i = 0; i < 4; i++) digitos[i]->setPlainText(QString(valor[i]));
    digitos[4]->setPlainText(QString::number(medicao.getCentenasLitros()));
    digitos[5]->setPlainText(QString::number(medicao.getDezenasLitros()));
    atualizarPonteiros(medicao.getLitros(), medicao.getDecimosLitros());
}
void HidrometroApp::atualizarPonteiros(int litros, int decimos) {
    double ang1 = (litros * 36.0 - 90.0) * M_PI / 180.0;
    double x1 = 384 + 40 * std::cos(ang1);
    double y1 = 280 + 40 * std::sin(ang1);
    litrosPonteiro->setLine(384, 280, x1, y1);

    double ang2 = (decimos * 36.0 - 90.0) * M_PI / 180.0;
    double x2 = 300 + 40 * std::cos(ang2);
    double y2 = 322 + 40 * std::sin(ang2);
    decimosPonteiro->setLine(300, 322, x2, y2);
}
