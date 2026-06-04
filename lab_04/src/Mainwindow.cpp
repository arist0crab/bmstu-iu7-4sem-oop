#include "Mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Button.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    elA = new Elevator(1, this);
    elB = new Elevator(2, this);
    controller = new Controller(elA, elB, this);
    uiTimer = new QTimer(this);
    connect(uiTimer, &QTimer::timeout, this, &MainWindow::updateUI);
    uiTimer->start(100);
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateUI()
{
    ui->liftAStatusBar->setText("Floor: " + QString::number(elA->getCabin()->getFloor()));
    ui->liftBStatusBar->setText("Floor: " + QString::number(elB->getCabin()->getFloor()));
    ui->liftALog->setText(elA->getCabin()->getDoors()->getState() == DoorState::OPEN ? "OPEN" : "CLOSED");
    ui->liftBLog->setText(elB->getCabin()->getDoors()->getState() == DoorState::OPEN ? "OPEN" : "CLOSED");
}

void MainWindow::setupConnections()
{
    connect(elA, &Elevator::floorPassed, controller, &Controller::onFloorPassed);
    connect(elB, &Elevator::floorPassed, controller, &Controller::onFloorPassed);
    connect(elA, &Elevator::doorStateChanged, controller, &Controller::onDoorStateChanged);
    connect(elB, &Elevator::doorStateChanged, controller, &Controller::onDoorStateChanged);

    auto linkBtn = [this](QPushButton* btn, int f, int d)
    {
        Button* logicBtn = new Button(f, d, this);
        connect(btn, &QPushButton::clicked, logicBtn, [logicBtn]() { QMetaObject::invokeMethod(logicBtn, "onClicked"); });
        connect(logicBtn, &Button::callRequested, controller, &Controller::onCallReceived);
    };

    linkBtn(ui->floorButton_5_down, 5, -1);
    linkBtn(ui->floorButton_4_up, 4, 1);
    linkBtn(ui->floorButton_4_down, 4, -1);
    linkBtn(ui->floorButton_3_up, 3, 1);
    linkBtn(ui->floorButton_3_down, 3, -1);
    linkBtn(ui->floorButton_2_up, 2, 1);
    linkBtn(ui->floorButton_2_down, 2, -1);
    linkBtn(ui->floorButton_1_up, 1, 1);

    auto linkCabin = [this](QPushButton* btn, int f)
    {
        Button* logicBtn = new Button(f, 0, this);
        connect(btn, &QPushButton::clicked, logicBtn, [logicBtn]() { QMetaObject::invokeMethod(logicBtn, "onClicked"); });
        connect(logicBtn, &Button::callRequested, controller, &Controller::onCallReceived);
    };

    linkCabin(ui->cabinAButton_1_floor, 1);
    linkCabin(ui->cabinAButton_2_floor, 2);
    linkCabin(ui->cabinAButton_3_floor, 3);
    linkCabin(ui->cabinAButton_4_floor, 4);
    linkCabin(ui->cabinAButton_5_floor, 5);

    linkCabin(ui->cabinBButton_1_floor, 1);
    linkCabin(ui->cabinBButton_2_floor, 2);
    linkCabin(ui->cabinBButton_3_floor, 3);
    linkCabin(ui->cabinBButton_4_floor, 4);
    linkCabin(ui->cabinBButton_5_floor, 5);

    connect(ui->cabinAButton_open, &QPushButton::clicked, elA->getCabin()->getDoors(), &Doors::onOpenRequest);
    connect(ui->cabinAButton_close, &QPushButton::clicked, elA->getCabin()->getDoors(), &Doors::onCloseRequest);
    connect(ui->cabinBButton_open, &QPushButton::clicked, elB->getCabin()->getDoors(), &Doors::onOpenRequest);
    connect(ui->cabinBButton_close, &QPushButton::clicked, elB->getCabin()->getDoors(), &Doors::onCloseRequest);
}