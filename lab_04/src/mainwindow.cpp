#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _elevatorA(this), _elevatorB(this)
{
    ui->setupUi(this);

    _shaftA = { ui->liftA_1floor, ui->liftA_2floor, ui->liftA_3floor, ui->liftA_4floor, ui->liftA_5floor };
    _shaftB = { ui->liftB_1floor, ui->liftB_2floor, ui->liftB_3floor, ui->liftB_4floor, ui->liftB_5floor };

    onFloorChangedA(1);
    onFloorChangedB(1);

    setupConnections();
}

MainWindow::~MainWindow() 
{ 
    delete ui; 
}

void MainWindow::setupConnections()
{
    // === ЛИФТ А: Сигналы наружу ===
    connect(&_elevatorA, &Elevator::floorChanged, this, &MainWindow::onFloorChangedA);
    connect(&_elevatorA, &Elevator::elevatorStateChanged, this, &MainWindow::onStateChangedA);

    // === ЛИФТ Б: Сигналы наружу ===
    connect(&_elevatorB, &Elevator::floorChanged, this, &MainWindow::onFloorChangedB);
    connect(&_elevatorB, &Elevator::elevatorStateChanged, this, &MainWindow::onStateChangedB);


    QList<QPushButton*> cabinAButtons = {
        ui->cabinAButton_1_floor, ui->cabinAButton_2_floor, 
        ui->cabinAButton_3_floor, ui->cabinAButton_4_floor, ui->cabinAButton_5_floor
    };

    for (int i = 0; i < cabinAButtons.size(); ++i) {
        int floor = i + 1;
        connect(cabinAButtons[i], &QPushButton::clicked, this, [this, floor]() {
            _elevatorA.sendCallToController(floor); 
        });
    }

    QList<QPushButton*> cabinBButtons = {
        ui->cabinBButton_1_floor, ui->cabinBButton_2_floor, 
        ui->cabinBButton_3_floor, ui->cabinBButton_4_floor, ui->cabinBButton_5_floor
    };
    for (int i = 0; i < cabinBButtons.size(); ++i) {
        int floor = i + 1;
        connect(cabinBButtons[i], &QPushButton::clicked, this, [this, floor]() {
            _elevatorB.sendCallToController(floor); 
        });
    }


    // === Внешние кнопки на этажах (▲ и ▼) ===
    connect(ui->floorButton_1_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(1); });
    connect(ui->floorButton_2_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(2); });
    connect(ui->floorButton_2_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(2); });
    connect(ui->floorButton_3_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(3); });
    connect(ui->floorButton_3_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(3); });
    connect(ui->floorButton_4_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(4); });
    connect(ui->floorButton_4_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(4); });
    connect(ui->floorButton_5_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(5); });

    // Кнопки дверей 
    connect(ui->cabinAButton_open,  &QPushButton::clicked, this, [this]() { ui->liftALog->setText("Двери открываются вручную"); });
    connect(ui->cabinAButton_close, &QPushButton::clicked, this, [this]() { ui->liftALog->setText("Двери закрываются вручную"); });
    connect(ui->cabinBButton_open,  &QPushButton::clicked, this, [this]() { ui->liftBLog->setText("Двери открываются вручную"); });
    connect(ui->cabinBButton_close, &QPushButton::clicked, this, [this]() { ui->liftBLog->setText("Двери закрываются вручную"); });
}

void MainWindow::onFloorCallRequested(int floor)
{
    ui->processField->append(QString("Вызов с этажа %1").arg(floor));

    if (_elevatorA.getState() == ElevatorState::IDLE) {
        _elevatorA.sendCallToController(floor);
    } else if (_elevatorB.getState() == ElevatorState::IDLE) {
        _elevatorB.sendCallToController(floor);
    } else {
        _elevatorA.sendCallToController(floor); 
    }
}

// === ОБРАБОТКА СОБЫТИЙ ЛИФТА А ===
void MainWindow::onFloorChangedA(int floor)
{
    ui->liftALog->setText(QString("Этаж: %1").arg(floor));
    ui->processField->append(QString("Лифт А приехал на %1 этаж").arg(floor));

    for (int i = 0; i < _shaftA.size(); ++i) {
        if (i == (floor - 1)) {
            _shaftA[i]->setText("[  CABIN A  ]");
        } else {
            _shaftA[i]->setText("===========================");
        }
    }
}

void MainWindow::onStateChangedA(ElevatorState state)
{
    if (state == ElevatorState::BUSY) {
        ui->liftAStatusBar->setText("ЗАНЯТ");
    } else {
        ui->liftAStatusBar->setText("ОЖИДАНИЕ");
    }
}

// === ОБРАБОТКА СОБЫТИЙ ЛИФТА Б ===
void MainWindow::onFloorChangedB(int floor)
{
    ui->liftBLog->setText(QString("Этаж: %1").arg(floor));
    ui->processField->append(QString("Лифт Б приехал на %1 этаж").arg(floor));

    for (int i = 0; i < _shaftB.size(); ++i) {
        if (i == (floor - 1)) {
            _shaftB[i]->setText("[  CABIN B  ]");
        } else {
            _shaftB[i]->setText("===========================");
        }
    }
}

void MainWindow::onStateChangedB(ElevatorState state)
{
    if (state == ElevatorState::BUSY) {
        ui->liftBStatusBar->setText("ЗАНЯТ");
    } else {
        ui->liftBStatusBar->setText("ОЖИДАНИЕ");
    }
}