#pragma once

#include <QObject>
#include <QTimer>

class ElevatorDoor : public QObject
{
    Q_OBJECT

    enum DoorState
    {
        Opened,
        Opening,
        Closed,
        Closing,
    };

    public:
        ElevatorDoor();

    signals:
        void doorClosed();

    public slots:
        void handleDoorOpened();
        void handleDoorClosed();

        void handleCloseDoor();
        void handleOpenDoor();

    private:
        DoorState state_;

        QTimer doorOpeningTimer_;
        QTimer doorClosingTimer_;
        QTimer doorWaitingTimer_;
};
