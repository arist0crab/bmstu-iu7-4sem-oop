/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_7;
    QLineEdit *liftA_5floor;
    QLineEdit *liftA_4floor;
    QLineEdit *liftA_3floor;
    QLineEdit *liftA_2floor;
    QLineEdit *liftA_1floor;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_6;
    QLineEdit *liftB_5floor;
    QLineEdit *liftB_4floor;
    QLineEdit *liftB_3floor;
    QLineEdit *liftB_2floor;
    QLineEdit *liftB_1floor;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *floorButton_4_up;
    QPushButton *floorButton_4_down;
    QLabel *label_3;
    QPushButton *floorButton_3_up;
    QPushButton *floorButton_3_down;
    QLabel *label_4;
    QPushButton *floorButton_2_up;
    QPushButton *floorButton_2_down;
    QLabel *label_5;
    QPushButton *floorButton_1_up;
    QPushButton *floorButton_5_down;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cabinAButton_1_floor;
    QPushButton *cabinAButton_2_floor;
    QPushButton *cabinAButton_3_floor;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cabinAButton_4_floor;
    QPushButton *cabinAButton_5_floor;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cabinAButton_open;
    QPushButton *cabinAButton_close;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *liftALog;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *cabinBButton_1_floor;
    QPushButton *cabinBButton_2_floor;
    QPushButton *cabinBButton_3_floor;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cabinBButton_4_floor;
    QPushButton *cabinBButton_5_floor;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *cabinBButton_open;
    QPushButton *cabinBButton_close;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *liftBLog;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_5;
    QLabel *label_6;
    QLineEdit *liftAStatusBar;
    QLabel *label_7;
    QLineEdit *liftBStatusBar;
    QTextEdit *processField;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1266, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #0a0f0a;\n"
"    border: 1px solid #1a3b1a;\n"
"}\n"
"\n"
"QMainWindow > QWidget {\n"
"    background-color: #0a0f0a;\n"
"}\n"
"\n"
"QFrame {\n"
"    background-color: #0c120c;\n"
"    border: 1px solid #1f4f1f;\n"
"    border-radius: 12px;\n"
"    padding: 8px;\n"
"    margin: 4px;\n"
"}\n"
"\n"
"QGroupBox {\n"
"    background-color: #0c120c;\n"
"    border: 2px solid #1f6f1f;\n"
"    border-radius: 12px;\n"
"    margin-top: 14px;\n"
"    font-family: \"Courier New\", \"Consolas\", monospace;\n"
"    font-weight: bold;\n"
"    color: #2eff2e;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 12px;\n"
"    padding: 0 8px 0 8px;\n"
"    background-color: #0a0f0a;\n"
"    color: #4aff4a;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QTextEdit {\n"
"    background-color: #030603;\n"
"    color: #2eff2e;\n"
"    font-family: \"Courier New\", \"Consolas\", monospace;\n"
"    font-size: 12px;\n"
"    font-weight: 500;\n"
"    border: 2px solid #1f6"
                        "f1f;\n"
"    border-radius: 10px;\n"
"    padding: 8px;\n"
"    selection-background-color: #1f4f1f;\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border: 2px solid #3eff3e;\n"
"    background-color: #050a05;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #0a120a;\n"
"    color: #2eff2e;\n"
"    font-family: \"Courier New\", \"Consolas\", monospace;\n"
"    font-weight: bold;\n"
"    font-size: 13px;\n"
"    border: 2px solid #1f6f1f;\n"
"    border-radius: 10px;\n"
"    padding: 8px 16px;\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #1a2a1a;\n"
"    border: 2px solid #3eff3e;\n"
"    color: #6aff6a;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #0a2a0a;\n"
"    border: 2px solid #1faf1f;\n"
"    color: #1fcf1f;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    color: #1a4f1a;\n"
"    border-color: #1a4f1a;\n"
"    background-color: #060a06;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #030603;\n"
"    color: #2eff2e;\n"
"    font-family: \"Couri"
                        "er New\", \"Consolas\", monospace;\n"
"    font-size: 12px;\n"
"    border: 2px solid #1f6f1f;\n"
"    border-radius: 10px;\n"
"    padding: 6px 10px;\n"
"    selection-background-color: #1f4f1f;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 2px solid #3eff3e;\n"
"    background-color: #050a05;\n"
"}\n"
"\n"
"QLabel {\n"
"    color: #2eff2e;\n"
"    font-family: \"Courier New\", \"Consolas\", monospace;\n"
"    font-size: 15px;\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"QLabel[class=\"title\"] {\n"
"    font-size: 20px;\n"
"    font-weight: bold;\n"
"    color: #4aff4a;\n"
"    border-bottom: 2px solid #1f6f1f;\n"
"    padding-bottom: 6px;\n"
"}\n"
"\n"
"QLabel[class=\"subtitle\"] {\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    color: #3aff3a;\n"
"    padding: 4px 0;\n"
"}\n"
"\n"
"QLabel[class=\"output\"] {\n"
"    background-color: #030603;\n"
"    border: 1px solid #1f4f1f;\n"
"    border-radius: 8px;\n"
"    padding: 6px;\n"
"    font-family: monospace;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_7 = new QGridLayout(groupBox_2);
        gridLayout_7->setObjectName("gridLayout_7");
        liftA_5floor = new QLineEdit(groupBox_2);
        liftA_5floor->setObjectName("liftA_5floor");

        gridLayout_7->addWidget(liftA_5floor, 0, 0, 1, 1);

        liftA_4floor = new QLineEdit(groupBox_2);
        liftA_4floor->setObjectName("liftA_4floor");

        gridLayout_7->addWidget(liftA_4floor, 1, 0, 1, 1);

        liftA_3floor = new QLineEdit(groupBox_2);
        liftA_3floor->setObjectName("liftA_3floor");

        gridLayout_7->addWidget(liftA_3floor, 2, 0, 1, 1);

        liftA_2floor = new QLineEdit(groupBox_2);
        liftA_2floor->setObjectName("liftA_2floor");

        gridLayout_7->addWidget(liftA_2floor, 3, 0, 1, 1);

        liftA_1floor = new QLineEdit(groupBox_2);
        liftA_1floor->setObjectName("liftA_1floor");

        gridLayout_7->addWidget(liftA_1floor, 4, 0, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        gridLayout_6 = new QGridLayout(groupBox_3);
        gridLayout_6->setObjectName("gridLayout_6");
        liftB_5floor = new QLineEdit(groupBox_3);
        liftB_5floor->setObjectName("liftB_5floor");

        gridLayout_6->addWidget(liftB_5floor, 0, 0, 1, 1);

        liftB_4floor = new QLineEdit(groupBox_3);
        liftB_4floor->setObjectName("liftB_4floor");

        gridLayout_6->addWidget(liftB_4floor, 1, 0, 1, 1);

        liftB_3floor = new QLineEdit(groupBox_3);
        liftB_3floor->setObjectName("liftB_3floor");

        gridLayout_6->addWidget(liftB_3floor, 2, 0, 1, 1);

        liftB_2floor = new QLineEdit(groupBox_3);
        liftB_2floor->setObjectName("liftB_2floor");

        gridLayout_6->addWidget(liftB_2floor, 3, 0, 1, 1);

        liftB_1floor = new QLineEdit(groupBox_3);
        liftB_1floor->setObjectName("liftB_1floor");

        gridLayout_6->addWidget(liftB_1floor, 4, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 0, 1, 1, 1);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName("gridLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        floorButton_4_up = new QPushButton(groupBox);
        floorButton_4_up->setObjectName("floorButton_4_up");

        gridLayout_2->addWidget(floorButton_4_up, 1, 1, 1, 1);

        floorButton_4_down = new QPushButton(groupBox);
        floorButton_4_down->setObjectName("floorButton_4_down");

        gridLayout_2->addWidget(floorButton_4_down, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        floorButton_3_up = new QPushButton(groupBox);
        floorButton_3_up->setObjectName("floorButton_3_up");

        gridLayout_2->addWidget(floorButton_3_up, 2, 1, 1, 1);

        floorButton_3_down = new QPushButton(groupBox);
        floorButton_3_down->setObjectName("floorButton_3_down");

        gridLayout_2->addWidget(floorButton_3_down, 2, 2, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        floorButton_2_up = new QPushButton(groupBox);
        floorButton_2_up->setObjectName("floorButton_2_up");

        gridLayout_2->addWidget(floorButton_2_up, 3, 1, 1, 1);

        floorButton_2_down = new QPushButton(groupBox);
        floorButton_2_down->setObjectName("floorButton_2_down");

        gridLayout_2->addWidget(floorButton_2_down, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        floorButton_1_up = new QPushButton(groupBox);
        floorButton_1_up->setObjectName("floorButton_1_up");

        gridLayout_2->addWidget(floorButton_1_up, 4, 1, 1, 2);

        floorButton_5_down = new QPushButton(groupBox);
        floorButton_5_down->setObjectName("floorButton_5_down");

        gridLayout_2->addWidget(floorButton_5_down, 0, 1, 1, 2);


        gridLayout->addWidget(groupBox, 0, 2, 1, 1);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName("groupBox_5");
        gridLayout_3 = new QGridLayout(groupBox_5);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        cabinAButton_1_floor = new QPushButton(groupBox_5);
        cabinAButton_1_floor->setObjectName("cabinAButton_1_floor");

        horizontalLayout_3->addWidget(cabinAButton_1_floor);

        cabinAButton_2_floor = new QPushButton(groupBox_5);
        cabinAButton_2_floor->setObjectName("cabinAButton_2_floor");

        horizontalLayout_3->addWidget(cabinAButton_2_floor);

        cabinAButton_3_floor = new QPushButton(groupBox_5);
        cabinAButton_3_floor->setObjectName("cabinAButton_3_floor");

        horizontalLayout_3->addWidget(cabinAButton_3_floor);


        gridLayout_3->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cabinAButton_4_floor = new QPushButton(groupBox_5);
        cabinAButton_4_floor->setObjectName("cabinAButton_4_floor");

        horizontalLayout->addWidget(cabinAButton_4_floor);

        cabinAButton_5_floor = new QPushButton(groupBox_5);
        cabinAButton_5_floor->setObjectName("cabinAButton_5_floor");

        horizontalLayout->addWidget(cabinAButton_5_floor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        cabinAButton_open = new QPushButton(groupBox_5);
        cabinAButton_open->setObjectName("cabinAButton_open");

        horizontalLayout_2->addWidget(cabinAButton_open);

        cabinAButton_close = new QPushButton(groupBox_5);
        cabinAButton_close->setObjectName("cabinAButton_close");

        horizontalLayout_2->addWidget(cabinAButton_close);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout_3->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        liftALog = new QLineEdit(groupBox_5);
        liftALog->setObjectName("liftALog");

        gridLayout_3->addWidget(liftALog, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox_5, 1, 0, 1, 1);

        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName("groupBox_7");
        gridLayout_4 = new QGridLayout(groupBox_7);
        gridLayout_4->setObjectName("gridLayout_4");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        cabinBButton_1_floor = new QPushButton(groupBox_7);
        cabinBButton_1_floor->setObjectName("cabinBButton_1_floor");

        horizontalLayout_4->addWidget(cabinBButton_1_floor);

        cabinBButton_2_floor = new QPushButton(groupBox_7);
        cabinBButton_2_floor->setObjectName("cabinBButton_2_floor");

        horizontalLayout_4->addWidget(cabinBButton_2_floor);

        cabinBButton_3_floor = new QPushButton(groupBox_7);
        cabinBButton_3_floor->setObjectName("cabinBButton_3_floor");

        horizontalLayout_4->addWidget(cabinBButton_3_floor);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(3);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        cabinBButton_4_floor = new QPushButton(groupBox_7);
        cabinBButton_4_floor->setObjectName("cabinBButton_4_floor");

        horizontalLayout_5->addWidget(cabinBButton_4_floor);

        cabinBButton_5_floor = new QPushButton(groupBox_7);
        cabinBButton_5_floor->setObjectName("cabinBButton_5_floor");

        horizontalLayout_5->addWidget(cabinBButton_5_floor);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        gridLayout_4->addLayout(horizontalLayout_5, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        cabinBButton_open = new QPushButton(groupBox_7);
        cabinBButton_open->setObjectName("cabinBButton_open");

        horizontalLayout_6->addWidget(cabinBButton_open);

        cabinBButton_close = new QPushButton(groupBox_7);
        cabinBButton_close->setObjectName("cabinBButton_close");

        horizontalLayout_6->addWidget(cabinBButton_close);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        gridLayout_4->addLayout(horizontalLayout_6, 2, 0, 1, 1);

        liftBLog = new QLineEdit(groupBox_7);
        liftBLog->setObjectName("liftBLog");

        gridLayout_4->addWidget(liftBLog, 3, 0, 1, 1);


        gridLayout->addWidget(groupBox_7, 1, 1, 1, 1);

        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName("groupBox_6");
        gridLayout_5 = new QGridLayout(groupBox_6);
        gridLayout_5->setObjectName("gridLayout_5");
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName("label_6");

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        liftAStatusBar = new QLineEdit(groupBox_6);
        liftAStatusBar->setObjectName("liftAStatusBar");

        gridLayout_5->addWidget(liftAStatusBar, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_6);
        label_7->setObjectName("label_7");

        gridLayout_5->addWidget(label_7, 1, 0, 1, 1);

        liftBStatusBar = new QLineEdit(groupBox_6);
        liftBStatusBar->setObjectName("liftBStatusBar");

        gridLayout_5->addWidget(liftBStatusBar, 1, 1, 1, 1);

        processField = new QTextEdit(groupBox_6);
        processField->setObjectName("processField");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(processField->sizePolicy().hasHeightForWidth());
        processField->setSizePolicy(sizePolicy);
        processField->setMinimumSize(QSize(30, 20));

        gridLayout_5->addWidget(processField, 2, 0, 1, 2);


        gridLayout->addWidget(groupBox_6, 1, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1266, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\204\321\202 \320\220", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\204\321\202 \320\221", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\275\320\276\320\277\320\272\320\270 \320\275\320\260 \321\215\321\202\320\260\320\266\320\260\321\205", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\266 5:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\266 4:", nullptr));
        floorButton_4_up->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        floorButton_4_down->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\266 3:", nullptr));
        floorButton_3_up->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        floorButton_3_down->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\266 2:", nullptr));
        floorButton_2_up->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        floorButton_2_down->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\255\321\202\320\260\320\266 1:", nullptr));
        floorButton_1_up->setText(QCoreApplication::translate("MainWindow", "\342\226\262", nullptr));
        floorButton_5_down->setText(QCoreApplication::translate("MainWindow", "\342\226\274", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \320\273\320\270\321\204\321\202\320\260 \320\220", nullptr));
        cabinAButton_1_floor->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        cabinAButton_2_floor->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        cabinAButton_3_floor->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        cabinAButton_4_floor->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        cabinAButton_5_floor->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        cabinAButton_open->setText(QCoreApplication::translate("MainWindow", "< >", nullptr));
        cabinAButton_close->setText(QCoreApplication::translate("MainWindow", "> <", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \320\273\320\270\321\204\321\202\320\260 \320\221", nullptr));
        cabinBButton_1_floor->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        cabinBButton_2_floor->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        cabinBButton_3_floor->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        cabinBButton_4_floor->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        cabinBButton_5_floor->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        cabinBButton_open->setText(QCoreApplication::translate("MainWindow", "< >", nullptr));
        cabinBButton_close->setText(QCoreApplication::translate("MainWindow", "> <", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201 \321\201\320\270\321\201\321\202\320\265\320\274\321\213", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\204\321\202 \320\220:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\320\233\320\270\321\204\321\202 \320\221:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
