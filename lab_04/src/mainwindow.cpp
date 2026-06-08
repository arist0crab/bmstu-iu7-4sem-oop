#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), _elevatorA(this), _elevatorB(this)
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
    // Сигналы лифтов
    connect(&_elevatorA, &Elevator::floorChanged, this, &MainWindow::onFloorChangedA);
    connect(&_elevatorA, &Elevator::doorsStateChangedSignal, this, &MainWindow::onDoorsStateChangedA);

    connect(&_elevatorB, &Elevator::floorChanged, this, &MainWindow::onFloorChangedB);
    connect(&_elevatorB, &Elevator::doorsStateChangedSignal, this, &MainWindow::onDoorsStateChangedB);

    // Кнопки кабин
    auto initCabinButtons = [this](QList<QPushButton*> btns, Elevator& elev, const QString& name) {
        for (int i = 0; i < btns.size(); ++i) {
            int floor = i + 1;
            connect(btns[i], &QPushButton::clicked, this, [this, &elev, name, floor]() {
                ui->processField->append(QString("Из кабины %1 нажата кнопка этажа %2").arg(name).arg(floor));
                elev.sendCallToController(floor); 
            });
        }
    };

    initCabinButtons({ui->cabinAButton_1_floor, ui->cabinAButton_2_floor, ui->cabinAButton_3_floor, ui->cabinAButton_4_floor, ui->cabinAButton_5_floor}, _elevatorA, "А");
    initCabinButtons({ui->cabinBButton_1_floor, ui->cabinBButton_2_floor, ui->cabinBButton_3_floor, ui->cabinBButton_4_floor, ui->cabinBButton_5_floor}, _elevatorB, "Б");

    // Кнопки этажей
    connect(ui->floorButton_1_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(1); });
    connect(ui->floorButton_2_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(2); });
    connect(ui->floorButton_3_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(3); });
    connect(ui->floorButton_4_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(4); });
    connect(ui->floorButton_5_up,   &QPushButton::clicked, this, [this]() { onFloorCallRequested(5); });
}

void MainWindow::onFloorCallRequested(int floor)
{
    ui->processField->append(QString("Вызов с этажа %1").arg(floor));
    getBestElevator(floor).sendCallToController(floor);
}

Elevator& MainWindow::getBestElevator(int targetFloor)
{
    bool aFree = (_elevatorA.getState() == ElevatorState::IDLE);
    bool bFree = (_elevatorB.getState() == ElevatorState::IDLE);

    if (aFree && bFree)
        return (qAbs(_currentFloorA - targetFloor) <= qAbs(_currentFloorB - targetFloor)) ? _elevatorA : _elevatorB;
    if (aFree) 
        return _elevatorA;
    if (bFree) 
        return _elevatorB;

    return (_elevatorA.queueSize() <= _elevatorB.queueSize()) ? _elevatorA : _elevatorB;
}

// ОБРАБОТКА ЛИФТА А
void MainWindow::onFloorChangedA(int floor)
{
    _currentFloorA = floor;
    ui->processField->append(QString("Лифт А приехал на %1 этаж").arg(floor));
    for (int i = 0; i < _shaftA.size(); ++i) 
        _shaftA[i]->setText(i == (floor - 1) ? "[  CABIN A  ] [  ||  ]" : "===========================");
}

void MainWindow::onDoorsStateChangedA(DoorsState state)
{
    QString logText, doorVisual;
    switch(state) {
        case DoorsState::OPENING: logText = "Лифт А: Двери открываются..."; doorVisual = "[ <  > ]"; break;
        case DoorsState::OPEN:    logText = "Лифт А: Двери ОТКРЫТЫ.";      doorVisual = "[      ]"; break;
        case DoorsState::CLOSING: logText = "Лифт А: Двери закрываются..."; doorVisual = "[ >  < ]"; break;
        case DoorsState::CLOSE:   logText = "Лифт А: Двери ЗАКРЫТЫ.";      doorVisual = "[  ||  ]"; break;
    }
    ui->processField->append(logText);
    int idx = _currentFloorA - 1;
    if (idx >= 0 && idx < _shaftA.size()) _shaftA[idx]->setText(QString("[  CABIN A  ] %1").arg(doorVisual));
}

// ОБРАБОТКА ЛИФТА Б
void MainWindow::onFloorChangedB(int floor)
{
    _currentFloorB = floor;
    ui->processField->append(QString("Лифт Б приехал на %1 этаж").arg(floor));
    for (int i = 0; i < _shaftB.size(); ++i) 
        _shaftB[i]->setText(i == (floor - 1) ? "[  CABIN B  ] [  ||  ]" : "===========================");
}

void MainWindow::onDoorsStateChangedB(DoorsState state)
{
    QString logText, doorVisual;
    switch(state) {
        case DoorsState::OPENING: logText = "Лифт Б: Двери открываются..."; doorVisual = "[ <  > ]"; break;
        case DoorsState::OPEN:    logText = "Лифт Б: Двери ОТКРЫТЫ.";      doorVisual = "[      ]"; break;
        case DoorsState::CLOSING: logText = "Лифт Б: Двери закрываются..."; doorVisual = "[ >  < ]"; break;
        case DoorsState::CLOSE:   logText = "Лифт Б: Двери ЗАКРЫТЫ.";      doorVisual = "[  ||  ]"; break;
    }
    ui->processField->append(logText);
    int idx = _currentFloorB - 1;
    if (idx >= 0 && idx < _shaftB.size()) _shaftB[idx]->setText(QString("[  CABIN B  ] %1").arg(doorVisual));
}