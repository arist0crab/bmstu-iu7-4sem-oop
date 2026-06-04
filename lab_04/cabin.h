#pragma once

#include <QObject>
#include <QTimer>
#include <doors.h>


class ElevatorCabin : public QObject
{
    Q_OBJECT

    public:
        enum CabinState
        {
            Unlocked,
            Moving,
            Stopped,
            Locked,
        };

      explicit ElevatorCabin(QObject* parent = nullptr);

    signals:
      void requestLockCabin();
      void cabinUnlocked();
      void requestOpenDoor();

    public slots:
      void handleUnlockCabin();
      void handleLockCabin();
      void handleMoveCabin();
      void handleStopCabin();

    private:
      CabinState state_;
      ElevatorDoor door_;

    public:
      QTimer floorTimerPass_;
};
