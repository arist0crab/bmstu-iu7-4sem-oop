#include "mainwindow.h"
#include "config.h"
#include "ui_mainwindow.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <cmath>
#include <qdebug.h>

#include "controller.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&elevator_.controller_, &ElevatorController::onFloor, this,
            [this](int floor) { onFloorPassed(floor, 0); });
    connect(&elevator2_.controller_, &ElevatorController::onFloor, this,
            [this](int floor) { onFloorPassed(floor, 1); });
    connect(&elevator_.controller_, &ElevatorController::floorButtonPressed, this,
            &MainWindow::onFloorButtonPressed);
    connect(&elevator2_.controller_, &ElevatorController::floorButtonPressed, this,
            &MainWindow::onFloorButtonPressed);

    generateUI();
    showMaximized();

    qInfo() << "Оба лифта на этаже №" << FIRST_FLOOR << ", двери закрыты";
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateUI()
{
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #f0f2f5;
        }
        QGroupBox {
            font: bold 14px "Segoe UI";
            border: 2px solid #cbd5e0;
            border-radius: 12px;
            margin-top: 12px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 15px;
            padding: 0 8px 0 8px;
            color: #2d3748;
        }
        QPushButton {
            font: bold 24px "Segoe UI";
            background-color: #e2e8f0;
            color: #1a202c;
            border: none;
            border-radius: 10px;
            padding: 12px;
        }
        QPushButton:hover {
            background-color: #cbd5e0;
        }
        QPushButton:pressed {
            background-color: #a0aec0;
        }
        QLabel {
            font: 14px "Segoe UI";
            background-color: white;
            padding: 10px;
            border-radius: 8px;
            border: 1px solid #e2e8f0;
        }
    )");

    auto finalLayout = new QVBoxLayout();
    finalLayout->setSpacing(15);
    finalLayout->setContentsMargins(20, 20, 20, 20);

    auto statusLayout = new QHBoxLayout();
    statusLayout->setSpacing(15);
    
    labelElevator1Floor_ = new QLabel(QStringLiteral("🚠 Лифт 1: этаж %1").arg(FIRST_FLOOR), this);
    labelElevator2Floor_ = new QLabel(QStringLiteral("🚡 Лифт 2: этаж %1").arg(FIRST_FLOOR), this);
    
    labelElevator1Floor_->setStyleSheet("QLabel { color: #1e3a8a; font-weight: bold; border-left: 4px solid #3b82f6; }");
    labelElevator2Floor_->setStyleSheet("QLabel { color: #14532d; font-weight: bold; border-left: 4px solid #22c55e; }");
    
    statusLayout->addWidget(labelElevator1Floor_);
    statusLayout->addWidget(labelElevator2Floor_);
    finalLayout->addLayout(statusLayout);

    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(25);

    auto elevatorGroup = new QGroupBox(QStringLiteral("🔘 ВЫЗОВ ЭТАЖА"), this);
    auto elevatorLayout = new QVBoxLayout();
    elevatorLayout->setSpacing(12);
    elevatorLayout->setContentsMargins(15, 20, 15, 15);

    for (auto i = LAST_FLOOR; i >= FIRST_FLOOR; --i)
    {
        auto button = new QPushButton(QString::number(i), this);
        button->setMinimumHeight(60);
        button->setMaximumHeight(80);
        button->setProperty("originalStyle", button->styleSheet());
        
        elevatorLayout->addWidget(button);
        connect(button, &QPushButton::pressed, this, [this, i]() { onButtonPressed(i); });
        elevatorButtons[i] = button;
    }
    elevatorLayout->addStretch();
    elevatorGroup->setLayout(elevatorLayout);
    elevatorGroup->setMinimumWidth(250);
    elevatorGroup->setMaximumWidth(400);

    mainLayout->addWidget(elevatorGroup);
    
    auto infoWidget = new QWidget(this);
    auto infoLayout = new QVBoxLayout(infoWidget);
    infoLayout->setSpacing(10);
    
    QLabel* infoTitle = new QLabel("📋 Цветовая индикация", this);
    infoTitle->setStyleSheet("font: bold 16px 'Segoe UI'; color: #1e293b; margin-bottom: 5px;");
    
    QLabel* infoText = new QLabel(
        "🔵 Синий - Лифт 1\n"
        "🟢 Зеленый - Лифт 2\n"
        "🟠 Оранжевый - Вызов с этажа",
        this
    );
    infoText->setWordWrap(true);
    infoText->setStyleSheet("QLabel { font: 13px 'Segoe UI'; background-color: #f8fafc; border: 1px solid #e2e8f0; padding: 12px; }");
    infoText->setMinimumWidth(200);
    infoText->setMaximumWidth(280);
    
    infoLayout->addWidget(infoTitle);
    infoLayout->addWidget(infoText);
    infoLayout->addStretch();
    
    mainLayout->addWidget(infoWidget);
    finalLayout->addLayout(mainLayout);

    auto centralWidget = new QWidget(this);
    centralWidget->setLayout(finalLayout);
    this->setCentralWidget(centralWidget);
    
    this->setWindowTitle("🏢 Система управления лифтами");
}

Elevator* MainWindow::pickElevatorFor(int floor)
{
    const int d1 = std::abs(elevator_.controller_.currentFloor() - floor);
    const int d2 = std::abs(elevator2_.controller_.currentFloor() - floor);

    if (d1 < d2)
    {
        return &elevator_;
    }
    if (d2 < d1)
    {
        return &elevator2_;
    }

    const bool idle1 = elevator_.controller_.isIdle();
    const bool idle2 = elevator2_.controller_.isIdle();
    if (idle1 != idle2)
    {
        return idle1 ? &elevator_ : &elevator2_;
    }

    const auto q1 = elevator_.controller_.queueSize();
    const auto q2 = elevator2_.controller_.queueSize();
    if (q1 != q2)
    {
        return q1 <= q2 ? &elevator_ : &elevator2_;
    }

    return &elevator_;
}

void MainWindow::onButtonPressed(int floor)
{
    pickElevatorFor(floor)->newRequest(floor);
}

void MainWindow::onFloorPassed(int floor, int elevatorIndex)
{
    QLabel* statusLabel = elevatorIndex == 0 ? labelElevator1Floor_ : labelElevator2Floor_;
    if (statusLabel != nullptr)
    {
        statusLabel->setText(QStringLiteral("Лифт %1: этаж %2").arg(elevatorIndex + 1).arg(floor));
    }

    if (elevatorButtons.contains(floor))
    {
        QPushButton* btn = elevatorButtons[floor];
        QString color = elevatorIndex == 0 ? "blue" : "#228B22";
        btn->setStyleSheet(QString("font: bold 24px 'Segoe UI'; background-color: %1; color: #1a202c; border: none; border-radius: 10px; padding: 12px;").arg(color));

        QTimer::singleShot(1000, this, [btn]() { 
            btn->setStyleSheet("font: bold 24px 'Segoe UI'; background-color: #e2e8f0; color: #1a202c; border: none; border-radius: 10px; padding: 12px;");
        });
    }
}

void MainWindow::onFloorButtonPressed(int floor)
{
    if (elevatorButtons.contains(floor))
    {
        QPushButton* btn = elevatorButtons[floor];
        btn->setStyleSheet("font: bold 24px 'Segoe UI'; background-color: #FFA07A; color: #1a202c; border: none; border-radius: 10px; padding: 12px;");
    }
}