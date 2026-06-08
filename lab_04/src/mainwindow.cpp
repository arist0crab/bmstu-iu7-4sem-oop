#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _elevatorA(this), _elevatorB(this), _currentFloorA(START_FLOOR), _currentFloorB(START_FLOOR)
{
    ui->setupUi(this);

    _shaftA = { ui->liftA_1floor, ui->liftA_2floor, ui->liftA_3floor, ui->liftA_4floor, ui->liftA_5floor };
    _shaftB = { ui->liftB_1floor, ui->liftB_2floor, ui->liftB_3floor, ui->liftB_4floor, ui->liftB_5floor };

    onFloorChangedA(_currentFloorA);
    onFloorChangedB(_currentFloorB);

    setupConnections();
}

MainWindow::~MainWindow() 
{ 
    delete ui; 
}

void MainWindow::setupConnections()
{
    // ЛИФТ А: Сигналы наружу 
    connect(&_elevatorA, &Elevator::floorChanged, this, &MainWindow::onFloorChangedA);
    connect(&_elevatorA, &Elevator::elevatorStateChanged, this, &MainWindow::onStateChangedA);
    connect(&_elevatorA, &Elevator::doorsStateChangedSignal, this, &MainWindow::onDoorsStateChangedA);

    // ЛИФТ Б: Сигналы наружу 
    connect(&_elevatorB, &Elevator::floorChanged, this, &MainWindow::onFloorChangedB);
    connect(&_elevatorB, &Elevator::elevatorStateChanged, this, &MainWindow::onStateChangedB);
    connect(&_elevatorB, &Elevator::doorsStateChangedSignal, this, &MainWindow::onDoorsStateChangedB);

    // Кнопки внутри кабины А
    QList<QPushButton*> cabinAButtons = {
        ui->cabinAButton_1_floor, ui->cabinAButton_2_floor, 
        ui->cabinAButton_3_floor, ui->cabinAButton_4_floor, ui->cabinAButton_5_floor
    };

    for (int i = 0; i < cabinAButtons.size(); ++i) {
        int floor = i + 1;
        connect(cabinAButtons[i], &QPushButton::clicked, this, [this, floor]() {
            ui->processField->append(QString("Из кабины А нажата кнопка этажа %1").arg(floor));
            _elevatorA.sendCallToController(floor); 
        });
    }

    // Кнопки внутри кабины Б
    QList<QPushButton*> cabinBButtons = {
        ui->cabinBButton_1_floor, ui->cabinBButton_2_floor, 
        ui->cabinBButton_3_floor, ui->cabinBButton_4_floor, ui->cabinBButton_5_floor
    };
    for (int i = 0; i < cabinBButtons.size(); ++i) {
        int floor = i + 1;
        connect(cabinBButtons[i], &QPushButton::clicked, this, [this, floor]() {
            ui->processField->append(QString("Из кабины Б нажата кнопка этажа %1").arg(floor));
            _elevatorB.sendCallToController(floor); 
        });
    }

    // Кнопки на этажах
    connect(ui->floorButton_1_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(1); });
    connect(ui->floorButton_2_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(2); });
    connect(ui->floorButton_2_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(2); });
    connect(ui->floorButton_3_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(3); });
    connect(ui->floorButton_3_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(3); });
    connect(ui->floorButton_4_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(4); });
    connect(ui->floorButton_4_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(4); });
    connect(ui->floorButton_5_down, &QPushButton::clicked, this, [this]() { onFloorCallRequested(5); });
}

void MainWindow::onFloorCallRequested(int floor)
{
    ui->processField->append(QString("Вызов с этажа %1").arg(floor));

    if (_elevatorA.getState() == ElevatorState::IDLE)
        _elevatorA.sendCallToController(floor);
    else if (_elevatorB.getState() == ElevatorState::IDLE)
        _elevatorB.sendCallToController(floor);
    else
        _elevatorA.sendCallToController(floor); 
}

// ОБРАБОТКА СОБЫТИЙ ЛИФТА А 
void MainWindow::onFloorChangedA(int floor)
{
    _currentFloorA = floor;
    ui->processField->append(QString("Лифт А приехал на %1 этаж").arg(floor));

    for (int i = 0; i < _shaftA.size(); ++i) 
    {
        if (i == (floor - 1))
            _shaftA[i]->setText("[  CABIN A  ] [  ||  ]"); 
        else
            _shaftA[i]->setText("===========================");
    }
}

void MainWindow::onStateChangedA(ElevatorState state)
{
    if (state == ElevatorState::BUSY)
        ui->liftAStatusBar->setText("ЗАНЯТ");
    else
        ui->liftAStatusBar->setText("ОЖИДАНИЕ");
}

void MainWindow::onDoorsStateChangedA(DoorsState state)
{
    QString logText;
    QString doorVisual;

    switch(state) {
        case DoorsState::OPENING: logText = "Лифт А: Двери открываются..."; doorVisual = "[ <  > ]"; break;
        case DoorsState::OPEN:    logText = "Лифт А: Двери ОТКРЫТЫ.";      doorVisual = "[      ]"; break;
        case DoorsState::CLOSING: logText = "Лифт А: Двери закрываются..."; doorVisual = "[ >  < ]"; break;
        case DoorsState::CLOSE:   logText = "Лифт А: Двери ЗАКРЫТЫ.";      doorVisual = "[  ||  ]"; break;
    }

    ui->processField->append(logText);

    int idx = _currentFloorA - 1;
    if (idx >= 0 && idx < _shaftA.size())
        _shaftA[idx]->setText(QString("[  CABIN A  ] %1").arg(doorVisual));
}

// ОБРАБОТКА СОБЫТИЙ ЛИФТА Б 
void MainWindow::onFloorChangedB(int floor)
{
    _currentFloorB = floor;
    ui->processField->append(QString("Лифт Б приехал на %1 этаж").arg(floor));

    for (int i = 0; i < _shaftB.size(); ++i) {
        if (i == (floor - 1))
            _shaftB[i]->setText("[  CABIN B  ] [  ||  ]");
        else
            _shaftB[i]->setText("===========================");
    }
}

void MainWindow::onStateChangedB(ElevatorState state)
{
    if (state == ElevatorState::BUSY)
        ui->liftBStatusBar->setText("ЗАНЯТ");
    else
        ui->liftBStatusBar->setText("ОЖИДАНИЕ");
}

void MainWindow::onDoorsStateChangedB(DoorsState state)
{
    QString logText;
    QString doorVisual;

    switch(state) 
    {
        case DoorsState::OPENING: logText = "Лифт Б: Двери открываются..."; doorVisual = "[ <  > ]"; break;
        case DoorsState::OPEN:    logText = "Лифт Б: Двери ОТКРЫТЫ.";      doorVisual = "[      ]"; break;
        case DoorsState::CLOSING: logText = "Лифт Б: Двери закрываются..."; doorVisual = "[ >  < ]"; break;
        case DoorsState::CLOSE:   logText = "Лифт Б: Двери ЗАКРЫТЫ.";      doorVisual = "[  ||  ]"; break;
    }

    ui->processField->append(logText);

    int idx = _currentFloorB - 1;
    if (idx >= 0 && idx < _shaftB.size())
        _shaftB[idx]->setText(QString("[  CABIN B  ] %1").arg(doorVisual));
}